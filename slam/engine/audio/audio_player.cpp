#include "audio_player.hpp"
#include "audio_manager.hpp"
#include <cstddef>

using namespace slam;
using namespace slam::audio;
using namespace slam::err;

AudioPlayer::AudioPlayer(const str &path, bool global) {
  this->path = path;
  this->global = global;

  result = ma_sound_init_from_file(AudioManager::GetEngine(), path.c_str(), 0,
                                   NULL, NULL, &sound);

  if (result != MA_SUCCESS) {
    THROW_ERROR(
        ERROR.Derived("", "Failed to initalize miniaudio sound from path \"" +
                              path + "\". miniaudio error: " + ToStr(result)));
    return;
  }

  ma_sound_set_spatialization_enabled(&sound, global);
}
