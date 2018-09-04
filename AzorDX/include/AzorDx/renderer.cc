#include <AzorDx/renderer.h>
#include <d3dx9.h>
#include <cstdio>
#include <map>

D3DXMATRIX transform;

namespace azordx {
extern UINT window_width;
extern UINT window_height;
extern HWND main_window_handle;
extern std::map<std::string, LPDIRECT3DTEXTURE9> texture_storage;
extern std::map<std::string, D3DXVECTOR2> texture_dimensions;
extern std::map<std::string, ID3DXFont*> font_storage;

IDirect3DDevice9 *d3d9_device = nullptr;
LPD3DXSPRITE sprite_batch = nullptr;

}  // namespace azordx

void azordx::Renderer::initialize() {
  //////////////////////
  // Initialize D3D:
  /////////////////////
  HRESULT result = 0;

  // Step 1: Create the IDirect3D9 object.
  IDirect3D9 *d3d9 = nullptr;
  d3d9 = Direct3DCreate9(D3D_SDK_VERSION);

  if (!d3d9) {
    MessageBox(nullptr, "Direct3DCreate9()", nullptr, 0);
    return;
  }

  // print adapter info
  D3DADAPTER_IDENTIFIER9 adapter_info;
  d3d9->GetAdapterIdentifier(D3DADAPTER_DEFAULT, 0, &adapter_info);
  std::string manufacturer;

  for (size_t i = 0; i < 512; i++) {
    if (adapter_info.Description[i] != ' ') {
      manufacturer += adapter_info.Description[i];
      continue;
    }
    break;
  }

  printf("Your GPU info:\n");
  printf("\tModel: %s\n", adapter_info.Description);
  printf("\tManufacturer: %s\n\n", manufacturer.c_str());

  // Step 2: Check for hardware vertex processing.
  D3DCAPS9 deviceCapabilities;
  d3d9->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &deviceCapabilities);

  UINT vertexProcessing = 0;

  if (deviceCapabilities.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT) {
    vertexProcessing = D3DCREATE_HARDWARE_VERTEXPROCESSING;
  } else {
    vertexProcessing = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
  }

  // Step 3: Fill out the D3DPRESENT_PARAMETERS structure.
  D3DPRESENT_PARAMETERS d3dpp;
  d3dpp.BackBufferWidth = window_width;
  d3dpp.BackBufferHeight = window_height;
  d3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;
  d3dpp.BackBufferCount = 1;
  d3dpp.MultiSampleType = D3DMULTISAMPLE_NONE;
  d3dpp.MultiSampleQuality = 0;
  d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
  d3dpp.hDeviceWindow = main_window_handle;
  d3dpp.Windowed = true;
  d3dpp.EnableAutoDepthStencil = true;
  d3dpp.AutoDepthStencilFormat = D3DFMT_D24S8;
  d3dpp.Flags = 0;
  d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;
  d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;

  // Step 4: Create the device.

  result =
      d3d9->CreateDevice(D3DADAPTER_DEFAULT,  // primary adapter
                         D3DDEVTYPE_HAL,      // device type
                         main_window_handle,  // window associated with device
                         vertexProcessing,    // vertex processing
                         &d3dpp,              // present parameters
                         &d3d9_device);       // return created device

  if (FAILED(result)) {
    // try again using a 16-bit depth buffer
    d3dpp.AutoDepthStencilFormat = D3DFMT_D16;

    result = d3d9->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
                                main_window_handle, vertexProcessing, &d3dpp,
                                &d3d9_device);

    if (FAILED(result)) {
      d3d9->Release();  // done with d3d9 object
      ::MessageBox(0, "CreateDevice() - FAILED", 0, 0);
      return;
    }
  }

  d3d9->Release();  // done with d3d9 object

  // create projection matrix
  D3DXMATRIX projection;
  D3DXMatrixOrthoLH(&projection, window_width, window_height, -1.0f, 1.0f);
  d3d9_device->SetTransform(D3DTS_PROJECTION, &projection);

  // create ID3DXSprite
  D3DXCreateSprite(d3d9_device, &sprite_batch);
}

void azordx::Renderer::draw(const std::string &name, const D3DXVECTOR2 position,
                            float scale, const float rotate,
                            const D3DCOLOR color) {
  if (texture_storage.count(name)) {
    const auto &sprite_center = texture_dimensions[name] * scale * 0.5f;
    const auto &actual_pos = position - sprite_center;
    D3DXMatrixAffineTransformation2D(&transform, scale, &sprite_center,
                                     D3DXToRadian(rotate), &actual_pos);

    sprite_batch->SetTransform(&transform);
    sprite_batch->Draw(texture_storage[name], nullptr, nullptr, nullptr, color);
  }
}

void azordx::Renderer::draw(const std::string &name, const D3DXVECTOR2 position,
                            const float scale, const D3DXVECTOR2 origin,
                            const float rotate, const D3DCOLOR color) {
  if (texture_storage.count(name)) {
    const auto &actual_pos = position - origin;
    D3DXMatrixAffineTransformation2D(&transform, scale, &origin,
                                     D3DXToRadian(rotate), &actual_pos);

    sprite_batch->SetTransform(&transform);
    sprite_batch->Draw(texture_storage[name], nullptr, nullptr, nullptr, color);
  }
}

void azordx::Renderer::draw(const std::string &name, const RECT rectangle,
                            const D3DXVECTOR2 position, const float scale,
                            const float rotate, const D3DCOLOR color) {
  if (texture_storage.count(name)) {
    const auto &left = rectangle.left;
    const auto &top = rectangle.top;
    const auto &right = rectangle.right;
    const auto &bottom = rectangle.bottom;

    const auto &sprite_center =
        D3DXVECTOR2((right - left) * 0.5f * scale, (bottom - top) * 0.5f * scale);
    const auto &actual_pos = position - sprite_center;

    D3DXMatrixAffineTransformation2D(&transform, scale, &sprite_center,
                                     D3DXToRadian(rotate), &actual_pos);

    sprite_batch->SetTransform(&transform);
    sprite_batch->Draw(texture_storage[name], &rectangle, nullptr, nullptr,
                       color);
  }
}

void azordx::Renderer::draw(const std::string &name, const RECT rectangle,
                            const D3DXVECTOR2 position, const float scale,
                            const D3DXVECTOR2 origin, const float rotate,
                            const D3DCOLOR color) {
  if (texture_storage.count(name)) {
    const auto &actual_pos = position - origin;
    D3DXMatrixAffineTransformation2D(&transform, scale, &origin,
                                     D3DXToRadian(rotate), &actual_pos);

    sprite_batch->SetTransform(&transform);
    sprite_batch->Draw(texture_storage[name], &rectangle, nullptr, nullptr,
                       color);
  }
}

void azordx::Renderer::draw_text(const std::string& font_alias, const std::string& text, RECT rectangle, D3DCOLOR color, bool centered){
  const auto& font = font_storage[font_alias];
  const auto format = centered ? (DT_CENTER | DT_VCENTER) : (DT_LEFT | DT_VCENTER);

  D3DXMatrixIdentity(&transform);
  sprite_batch->SetTransform(&transform);
  font->DrawText(sprite_batch, text.c_str(), -1, &rectangle, format, color);
}

void azordx::Renderer::clean_up() {
  if (sprite_batch) sprite_batch->Release();
}