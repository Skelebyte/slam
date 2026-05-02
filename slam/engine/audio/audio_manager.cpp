#define MINIAUDIO_IMPLEMENTATION
#include "audio_manager.hpp"
#include "audio_listener.hpp"

using namespace slam;
using namespace slam::audio;
using namespace slam::err;

void AudioManager::Init() {
  if (Get().initialized == true)
    return;

  Get().result = ma_engine_init(NULL, &Get().engine);

  if (Get().result != MA_SUCCESS) {
    THROW_ERROR(
        FATAL.Derived("", "Failed to initialize miniaudio! miniaudio error: " +
                              String::From(Get().result)));
    return;
  }

  Get().initialized = true;
}

void AudioManager::Shutdown() {
  if (Get().initialized == false)
    return;

  ma_engine_uninit(&Get().engine);

  Get().initialized = false;
}

ma_engine *AudioManager::GetEngine() {
  if (Get().initialized == false)
    return nullptr;

  return &Get().engine;
}

void AudioManager::SetListener(AudioListener *listener) {
  if (Get().initialized == false)
    return;

  Get().listener = listener;
}

AudioListener *AudioManager::GetListener() {
  if (Get().initialized == false)
    return nullptr;

  if (Get().listener == nullptr) {
    THROW_ERROR(FATAL.Derived(
        "", "There must be an AudioListener! Have you created one?"));
    return nullptr;
  }

  return Get().listener;
}

void AudioManager::SetAllowPitchModifier(bool value) {
  if (Get().initialized == false) {
    return;
  }

  Get().canTimescaleModPitch = value;
}

bool AudioManager::GetAllowPitchModifier() {
  if (Get().initialized == false) {
    return false;
  }

  return Get().canTimescaleModPitch;
}