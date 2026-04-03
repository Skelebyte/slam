#include "audio_player.hpp"
#include "audio_manager.hpp"
#include <cstddef>

using namespace slam;
using namespace slam::audio;
using namespace slam::math;
using namespace slam::err;
using namespace slam::util;

AudioPlayer::AudioPlayer(const str &path, bool global) {
  if (File::Exists(path) == false) {
    THROW_ERROR(ERROR.Derived("", "File \"" + path + "\" does not exist!"));
    return;
  }

  if (AudioManager::IsInitialized() == false) {
    THROW_ERROR(FATAL.Derived("", "AudioManager is not initialized! Have you "
                                  "called AudioManager::Init()?"));
    return;
  }

  this->path = path;
  this->global = global;

  result = ma_sound_init_from_file(AudioManager::GetEngine(), path.c_str(), 0,
                                   NULL, NULL, &sound);

  if (result != MA_SUCCESS) {
    THROW_ERROR(ERROR.Derived(
        "", "Failed to initalize miniaudio sound from path \"" + path +
                "\". miniaudio error: " + String::From(result)));
    return;
  }

  ma_sound_set_spatialization_enabled(&sound, global);

  init = true;
}

void AudioPlayer::Destroy() {
  DESTROY();

  ma_sound_uninit(&sound);
}

void AudioPlayer::Update() {
  IS_DESTROYED();

  transform.Process();

  if (global) {

    ma_sound_set_position(&sound, transform.GetInheritedPosition().x,
                          transform.GetInheritedPosition().y,
                          transform.GetInheritedPosition().z);
  }

  if (IsPlaying()) {
    frame = ma_sound_get_time_in_milliseconds(&sound);
  }

  if (looping && !IsPlaying()) {
    Play(true);
  }

  ma_sound_set_volume(&sound, volume);
  if (AudioManager::GetAllowPitchModifier()) {
    ma_sound_set_pitch(&sound, pitch * Time::GetTimeScale());
  } else {
    ma_sound_set_pitch(&sound, pitch);
  }
}

void AudioPlayer::Play(bool fromBeginning) {
  IS_DESTROYED();
  if (init == false) {
    THROW_ERROR(WARNING.Derived("", "Not initialized!"));
    return;
  }

  if (frame != 0 && fromBeginning) {
    ma_sound_set_start_time_in_milliseconds(&sound, frame);
  }

  result = ma_sound_start(&sound);

  if (result != MA_SUCCESS) {
    THROW_ERROR(ERROR.Derived("", "Failed to play sound! miniaudio error: " +
                                      String::From((int)result)));
    return;
  }
}

void AudioPlayer::Stop() {
  IS_DESTROYED();
  if (init == false)
    return;

  result = ma_sound_stop(&sound);
  if (result != MA_SUCCESS) {
    THROW_ERROR(ERROR.Derived("", "Failed to stop sound! miniaudio error: " +
                                      String::From((int)result)));
    return;
  }
}

void AudioPlayer::SetLooping(bool value) {
  IS_DESTROYED();

  looping = value;
}

void AudioPlayer::SetGlobal(bool value) {
  IS_DESTROYED();

  global = value;
}

bool AudioPlayer::IsPlaying() const {
  IS_DESTROYED(false);
  if (init == false)
    return false;

  if (ma_sound_is_playing(&sound) == MA_TRUE) {
    return true;
  } else {
    return false;
  }
}