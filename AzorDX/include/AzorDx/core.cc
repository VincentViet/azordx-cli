#include <AzorDx/client.h>
#include <Windows.h>
#include <d3dx9.h>
#include <dxerr9.h>
#include <jansson/jansson.h>
#include <cstdio>

#define CLASS_NAME "AzorGame"
#define IDT_TIMER_1 1001

extern void initialize();
extern void load_resources();
extern void update();
extern void draw();
extern void clean_up();
extern void on_left_mouse_btn_click();
extern void on_left_mouse_btn_dbclick();
extern void on_key_down(int key);

POINT mouse_pos;
LRESULT CALLBACK windProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace azordx {

HWND main_window_handle = nullptr;
HINSTANCE app_instance = nullptr;

UINT window_width = 0;
UINT window_height = 0;
const char* window_title = nullptr;

extern LPDIRECT3DDEVICE9 d3d9_device;
extern LPD3DXSPRITE sprite_batch;
extern D3DXVECTOR2 input_mouse_position;

unsigned int frame_count = 0;

extern void tick();
extern void poll_mouse();
extern void poll_keyboard();

bool game_initialize() {
  // read config file
  json_error_t err;
  const auto config = json_load_file("./.config", 0, &err);
  if (!config) {
    printf("\nerror message: %s\n", err.text);
    printf("error source: %s\n", err.source);
    printf("line: %d\n", err.line);
    printf("column: %d\n", err.column);
    printf("position: %d\n", err.position);
    return false;
  }

  window_width = json_integer_value(json_object_get(config, "windowWidth"));
  window_height = json_integer_value(json_object_get(config, "windowHeight"));
  window_title = json_string_value(json_object_get(config, "windowTitle"));
  const auto centered_window = json_object_get(config, "centeredWindow");

  WNDCLASS wc;
  wc.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
  wc.lpfnWndProc = windProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = app_instance;
  wc.hIcon = LoadIcon(0, IDI_APPLICATION);
  wc.hCursor = LoadCursor(0, IDC_ARROW);
  wc.hbrBackground = static_cast<HBRUSH>(GetStockObject(WHITE_BRUSH));
  wc.lpszMenuName = nullptr;
  wc.lpszClassName = CLASS_NAME;

  if (!RegisterClass(&wc)) {
    /* code */
    MessageBox(nullptr, "RegisterClass - Failed", nullptr, 0);
    return false;
  }

  // Center window
  unsigned int xPos = 0;
  unsigned int yPos = 0;
  if (centered_window->type == JSON_TRUE) {
    const auto screen_width = GetSystemMetrics(SM_CXSCREEN);
    const auto screen_height = GetSystemMetrics(SM_CYSCREEN);
    xPos = (screen_width - window_width) / 2;
    yPos = (screen_height - window_height) / 2;
  }

  main_window_handle = CreateWindow(CLASS_NAME, CLASS_NAME, WS_OVERLAPPEDWINDOW,
                                    xPos, yPos, window_width, window_height,
                                    nullptr, nullptr, app_instance, nullptr);

  if (!main_window_handle) {
    /* code */
    MessageBox(nullptr, "CreateWindow - Failed", nullptr, 0);
    return false;
  }

  ShowWindow(main_window_handle, SW_SHOW);
  UpdateWindow(main_window_handle);

  SetDoubleClickTime(400);
  SetWindowText(main_window_handle, window_title);
  SetTimer(main_window_handle, IDT_TIMER_1, 1000, (TIMERPROC) nullptr);

  return true;
}

int game_run() {
  MSG message;
  ZeroMemory(&message, sizeof(MSG));

  printf("\n");

  initialize();
  load_resources();

  if (!d3d9_device || !sprite_batch)
    printf("You did not initialize Renderer yet.\n");

  while (message.message != WM_QUIT) {
    if (PeekMessage(&message, nullptr, 0, 0, PM_REMOVE)) {
      TranslateMessage(&message);
      DispatchMessage(&message);
    } else {
      // game code here
      tick();
      poll_mouse();
      poll_keyboard();

      update();

      if (d3d9_device && sprite_batch) {
        d3d9_device->Clear(0, nullptr, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER,
                           D3DCOLOR_XRGB(51, 77, 77), 1.0f, 0);

        d3d9_device->BeginScene();
        const auto result = sprite_batch->Begin(
            D3DXSPRITE_ALPHABLEND | D3DXSPRITE_DO_NOT_ADDREF_TEXTURE);

        if (FAILED(result)) {
          printf("\nERROR: %s\n Desc: %s", DXGetErrorString9(result),
                 DXGetErrorDescription9(result));
          break;
        }
        draw();

        // render stats
        sprite_batch->End();
        d3d9_device->EndScene();
        d3d9_device->Present(nullptr, nullptr, nullptr, nullptr);

        frame_count++;
      }
    }
  }

  clean_up();

  if (d3d9_device) d3d9_device->Release();

  return message.wParam;
}
}  // namespace azordx

////////////////////////
// WIND PROC
///////////////////////
LRESULT CALLBACK windProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam) {
  switch (msg) {
    case WM_KEYDOWN:
      if (wParam == VK_ESCAPE) DestroyWindow(azordx::main_window_handle);

      on_key_down(wParam);
      return 0;

    case WM_DESTROY:
      KillTimer(azordx::main_window_handle, IDT_TIMER_1);
      PostQuitMessage(0);
      return 0;

    case WM_TIMER:
      char temp[50];
      sprintf(temp, "%s FPS: %d", azordx::window_title, azordx::frame_count);
      SetWindowText(azordx::main_window_handle, temp);
      azordx::frame_count = 0;
      return 0;

    case WM_SIZE:
      azordx::Client::width = LOWORD(lParam);
      azordx::Client::height = HIWORD(lParam);
      printf("\nClient has been resized to %dx%d\n", LOWORD(lParam),
             HIWORD(lParam));
      return 0;

    case WM_MOVE:
      azordx::Client::x_position = LOWORD(lParam);
      azordx::Client::y_position = HIWORD(lParam);
      printf("\nClient has been moved to %dx%d\n", LOWORD(lParam),
             HIWORD(lParam));
      return 0;

    case WM_LBUTTONDOWN:
      on_left_mouse_btn_click();
      return 0;

    case WM_LBUTTONDBLCLK:
      on_left_mouse_btn_dbclick();
      return 0;

    case WM_MOUSEMOVE:
      GetCursorPos(&mouse_pos);
      ScreenToClient(azordx::main_window_handle, &mouse_pos);
      azordx::input_mouse_position = D3DXVECTOR2(mouse_pos.x, mouse_pos.y);
      return 0;
  }

  return DefWindowProc(hwnd, msg, wParam, lParam);
}

//////////////////////////
// WINMAIN
/////////////////////////

int WINAPI WinMain(HINSTANCE instance, HINSTANCE prevInstance, PSTR cmdLine,
                   int showCmd) {
  azordx::app_instance = instance;

  printf("Welcome to AzorDx - A DirectX 9.0 Game 2D Framework.\n");
  printf("Press 'ESC' or 'Red Cross' button to exit.\n");

  if (!azordx::game_initialize()) {
    MessageBox(0, "Init - Failed", "Error", MB_OK);
    return -1;
  }

  return azordx::game_run();
}