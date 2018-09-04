#ifndef AZORDX_SOUND_H
#define AZORDX_SOUND_H

#include <string>

namespace azordx {

class Sound {
 public:
  Sound() = delete;
  ~Sound() = delete;

 public:
 static void initialize();
 static void clean_up();
 static void play(const std::string& name, bool looped = false);
 static void set_volume(const std::string& name, float value);
 static void pause(const std::string& name, bool paused = true);
 static void stop(const std::string& name);
 static void stop_all_sound();
};

}  // namespace azordx

#endif  // AZORDX_SOUND_H