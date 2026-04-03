#ifndef SLAM_AUDIO_PLAYER_HPP
#define SLAM_AUDIO_PLAYER_HPP

#include "../../third_party/miniaudio.h"
#include "../common.hpp"
#include "../scn/entity.hpp"
#include "../time.hpp"
#include "../util/file.hpp"

namespace slam::audio {

struct AudioPlayer : public scn::Entity {
  AudioPlayer(const str &path, bool global = true);
  void Destroy() override;
  void Update() override;
  void Play(bool fromBeginning = true);
  void Stop();
  void SetLooping(bool value);
  void SetGlobal(bool value);
  bool IsPlaying() const;
  f32 pitch = 1.0f;
  f32 volume = 1.0f;

protected:
  bool looping = false;
  bool global = true;
  str path;
  u64 frame = 0;
  ma_result result;
  ma_sound sound;

private:
  bool init = false;
};

} // namespace slam::audio

#endif