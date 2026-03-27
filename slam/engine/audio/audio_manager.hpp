#ifndef SLAM_AUDIO_MANAGER_HPP
#define SLAM_AUDIO_MANAGER_HPP

#include "../../third_party/miniaudio.h"
#include "../common.hpp"
#include "../err/err_sys.hpp"

namespace slam::audio {
struct AudioManager : public Singleton<AudioManager> {
  static void Init();
  static void Shutdown();
  static ma_engine *GetEngine();

private:
  ma_engine engine;
  ma_result result;
};
} // namespace slam::audio

#endif