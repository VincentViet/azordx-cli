#include <AzorDx/client.h>
#include <windows.h>
#include <string>

unsigned int azordx::Client::width = 0;
unsigned int azordx::Client::height = 0;
unsigned int azordx::Client::x_position = 0;
unsigned int azordx::Client::y_position = 0;

namespace azordx{
extern HWND main_window_handle;
std::string client_title;
}

void azordx::Client::set_client_title(const char* title){
    client_title = title;
    SetWindowText(main_window_handle, title);
}

const char* azordx::Client::get_client_title(){
    return client_title.c_str();
}