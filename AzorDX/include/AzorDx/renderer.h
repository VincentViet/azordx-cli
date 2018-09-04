#ifndef AZORDX_RENDER_H
#define AZORDX_RENDER_H

#include <d3dx9math.h>
#include <string>
#include <windows.h>

namespace azordx {

class Renderer {
 private:
 public:
  Renderer() = delete;
  ~Renderer() = delete;

 public:
  static void initialize();

  static void draw(const std::string& name, D3DXVECTOR2 position, float scale,
                   float rotate, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

  static void draw(const std::string& name, D3DXVECTOR2 position, float scale,
                   D3DXVECTOR2 origin, float rotate,
                   D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

  static void draw(const std::string& name, RECT rectangle,
                   D3DXVECTOR2 position, float scale, float rotate,
                   D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

  static void draw(const std::string& name, RECT rectangle,
                   D3DXVECTOR2 position, float scale, D3DXVECTOR2 origin,
                   float rotate, D3DCOLOR color = D3DCOLOR_XRGB(255, 255, 255));

  static void draw_text(const std::string& font_alias, const std::string& text, RECT rectangle, D3DCOLOR color, bool centered = true);

  static void clean_up();
};

}  // namespace azordx

#endif  // AZORDX_RENDER_H