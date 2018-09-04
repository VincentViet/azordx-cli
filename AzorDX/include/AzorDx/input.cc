#define DIRECTINPUT_VERSION 0x0800

#include <AzorDx/input.h>
#include <dinput.h>

LPDIRECTINPUT8 dinput = nullptr;
LPDIRECTINPUTDEVICE8 mouse = nullptr;
LPDIRECTINPUTDEVICE8 keyboard = nullptr;
LPDIRECTINPUTDEVICE8 joystick = nullptr;

DIMOUSESTATE mouse_state;
char keys[256];

namespace azordx {

extern HWND main_window_handle;
extern HINSTANCE app_instance;
D3DXVECTOR2 input_mouse_position{};

void poll_mouse() {
  if (mouse) {
    const auto result = mouse->GetDeviceState(sizeof(mouse_state),
                                              static_cast<void*>(&mouse_state));
    if (FAILED(result)) {
      ZeroMemory(&mouse_state, sizeof(mouse_state));
      mouse->Acquire();
    }
  }
}

void poll_keyboard() {
  if (keyboard) {
    const auto result =
        keyboard->GetDeviceState(sizeof(keys), static_cast<void*>(&keys));
    if (FAILED(result)) {
      ZeroMemory(keys, sizeof(keys));
      keyboard->Acquire();
    }
  }
}
}  // namespace azordx

void azordx::Input::initialize() {
  // create DirectInput object

  ZeroMemory(keys, sizeof(keys));
  ZeroMemory(&mouse_state, sizeof(mouse_state));

  auto result = DirectInput8Create(app_instance, DIRECTINPUT_VERSION,
                                   IID_IDirectInput8, (void**)&dinput, nullptr);

  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't create DirectInput8", "ERROR", MB_OK);
    return;
  }

  // initialize mouse
  result = dinput->CreateDevice(GUID_SysMouse, &mouse, nullptr);
  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't create mousedevice handler", "ERROR", MB_OK);
    return;
  }

  result = mouse->SetDataFormat(&c_dfDIMouse);
  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't set mouse's dataformat", "ERROR", MB_OK);
    return;
  }

  result = mouse->SetCooperativeLevel(main_window_handle,
                                      DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't set mouse's cooperative level", "ERROR", MB_OK);
    return;
  }

  result = mouse->Acquire();

  // initialize keyboard
  result = dinput->CreateDevice(GUID_SysKeyboard, &keyboard, nullptr);
  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't create keyboard device handler", "ERROR",
               MB_OK);
    return;
  }

  result = keyboard->SetDataFormat(&c_dfDIKeyboard);
  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't set keyboard's dataformat", "ERROR", MB_OK);
    return;
  }

  result = keyboard->SetCooperativeLevel(main_window_handle,
                                         DISCL_NONEXCLUSIVE | DISCL_FOREGROUND);
  if (FAILED(result)) {
    MessageBox(nullptr, "Cant't set keyboard's cooperative level", "ERROR",
               MB_OK);
    return;
  }

  result = keyboard->Acquire();
}

bool azordx::Input::is_key_pressed(int keycode) {
  return (keys[keycode] & 0x80);
}

bool azordx::Input::is_mouse_bt_pressed(int btn_code) {
  return (mouse_state.rgbButtons[btn_code] & 0x80);
}

D3DXVECTOR2 azordx::Input::mouse_pos() {
  return input_mouse_position;
}

float azordx::Input::mouse_x() { return mouse_state.lX; }
float azordx::Input::mouse_y() { return mouse_state.lY; }
float azordx::Input::mouse_z() { return mouse_state.lZ; }

void azordx::Input::clean_up() {
  if (mouse) {
    mouse->Unacquire();
    mouse->Release();
    mouse = nullptr;
  }

  if (keyboard) {
    keyboard->Unacquire();
    keyboard->Release();
    keyboard = nullptr;
  }

  if (dinput) {
    dinput->Release();
    dinput = nullptr;
  }
}