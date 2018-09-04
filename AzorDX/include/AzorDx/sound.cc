#include <AzorDx/sound.h>
#include <irrklang/irrKlang.h>
#include <map>

using namespace irrklang;

std::map<std::string, ISound*> sound_storage;

namespace azordx {
ISoundEngine* engine = nullptr;
extern std::map<std::string, ISoundSource*> sound_source_storage;
}  // namespace azordx

void azordx::Sound::initialize() { engine = createIrrKlangDevice(); }

void azordx::Sound::clean_up() {
    for (const auto& sound : sound_storage) {
    if (sound.second) {
      sound.second->drop();
    }
  }

  if (engine) {
    engine->removeAllSoundSources();
    engine->drop();
  }
}

void azordx::Sound::play(const std::string& name, bool looped) {
  ISound* sound = nullptr;
  if (engine) {
    if (!sound_storage.count(name)) {
      sound = engine->play2D(sound_source_storage[name], looped, false, true);
      sound_storage.insert(std::pair<std::string, ISound*>(name, sound));
    } else {
      engine->play2D(sound_source_storage[name], looped);
    }

  } else {
    printf("\nYou did not initialize sound yet!!!\n");
  }
}

void azordx::Sound::set_volume(const std::string& name, float value) {
  sound_storage[name]->setVolume(value);
}

void azordx::Sound::pause(const std::string& name, bool paused) {
  sound_storage[name]->setIsPaused(paused);
}

void azordx::Sound::stop(const std::string& name) {
  sound_storage[name]->stop();
}

void azordx::Sound::stop_all_sound() { engine->stopAllSounds(); }