#ifndef SLAM_AUDIO_LISTENER_HPP
#define SLAM_AUDIO_LISTENER_HPP

#include "../common.hpp"
#include "../scn/entity.hpp"

namespace slam::audio {
struct AudioListener : public scn::Entity {
  AudioListener(bool setAsMainListener = true);
  void Destroy() override;
  void Update() override;
};
} // namespace slam::audio

#endif