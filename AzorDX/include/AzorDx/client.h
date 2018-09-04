#ifndef AZORDX_CLIENT_H
#define AZORDX_CLIENT_H

namespace azordx {

class Client {
 public:
  Client() = delete;
  ~Client() = delete;

 public:
    static unsigned int width;
    static unsigned int height;
    static unsigned int x_position;
    static unsigned int y_position;
    static void set_client_title(const char* title);
    static const char* get_client_title();
};

}  // namespace azordx

#endif  // AZORDX_CLIENT_H