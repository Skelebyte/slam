#include "audio_manager.hpp"

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
                              ToStr(Get().result)));
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