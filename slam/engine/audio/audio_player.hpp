#ifndef SLAM_AUDIO_PLAYER_HPP
#define SLAM_AUDIO_PLAYER_HPP

#include "../../third_party/miniaudio.h"
#include "../common.hpp"
#include "../scn/entity.hpp"

namespace slam::audio {

struct AudioPlayer : public scn::Entity {
  AudioPlayer(const str &path, bool global = true);
  void Destroy() override;
  void Update() override;

protected:
  bool playing = false;
  bool looping = false;
  bool global = true;
  str path;
  u64 frame;
  ma_result result;
  ma_sound sound;
};

} // namespace slam::audio

#endif