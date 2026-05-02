#ifndef SLAM_AUDIO_MANAGER_HPP
#define SLAM_AUDIO_MANAGER_HPP

#include "../../third_party/miniaudio.h"
#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "audio_listener.hpp"

namespace slam::audio {
struct AudioManager : public Singleton<AudioManager> {
  static void Init();
  static void Shutdown();
  static ma_engine *GetEngine();
  static void SetListener(AudioListener *listener);
  static AudioListener *GetListener();
  /**
   * @brief Allow timescale to modify pitch.
   *
   * @param value
   */
  static void SetAllowPitchModifier(bool value);
  /**
   * @brief Gets if timescale is allowed to modify pitch.
   *
   * @return true
   * @return false
   */
  static bool GetAllowPitchModifier();

private:
  ma_engine engine;
  ma_result result;
  AudioListener *listener;
  bool canTimescaleModPitch = true;
};
} // namespace slam::audio

#endif