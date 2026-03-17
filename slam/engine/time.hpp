#ifndef SLAM_TIME_HPP
#define SLAM_TIME_HPP

#include "common.hpp"
#include "engine.hpp"

namespace slam {
struct Time {
  static f32 DeltaTime();
  static void SetTimeScale(f32 scale);
};
} // namespace slam

#endif