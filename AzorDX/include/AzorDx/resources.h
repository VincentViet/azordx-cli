#ifndef AZORDX_RESOURCES_H
#define AZORDX_RESOURCES_H

#include <d3dx9math.h>
#include <string>

#define AZOR_FW_DONTCARE 0
#define AZOR_FW_THIN 100
#define AZOR_FW_EXTRALIGHT 200
#define AZOR_FW_ULTRALIGHT 200
#define AZOR_FW_LIGHT 300
#define AZOR_FW_NORMAL 400
#define AZOR_FW_REGULAR 400
#define AZOR_FW_MEDIUM 500
#define AZOR_FW_SEMIBOLD 600
#define AZOR_FW_DEMIBOLD 600
#define AZOR_FW_BOLD 700
#define AZOR_FW_EXTRABOLD 800
#define AZOR_FW_ULTRABOLD 800
#define AZOR_FW_HEAVY 900
#define AZOR_FW_BLACK 900

namespace azordx {

class Resources {
 public:
  Resources() = delete;
  ~Resources() = delete;

 public:
  static void initialize();
  static void clean_up();
  static D3DXVECTOR2 get_texture_size(const std::string& name);
  static void load_texture_from_file(const std::string& file_path,
                                     const std::string& name);
  static void load_sound_from_file(const std::string& file_path,
                                   const std::string& name,
                                   float default_volume = 0.5f);

  static void load_font(const std::string& font_name, const std::string& alias,
                        int font_size, int font_weight, bool italic = false);
};

}  // namespace azordx

#endif  // AZORDX_RESOURCES_H