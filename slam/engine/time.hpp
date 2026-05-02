#ifndef SLAM_TIME_HPP
#define SLAM_TIME_HPP

#include "common.hpp"

namespace slam {
struct Time {
  static f32 DeltaTime();
  static f32 UnscaledDeltaTime();
  static void SetTimeScale(f32 scale);
  static f32 GetTimeScale();
  static u64 MsToNs(u32 value);
};
} // namespace slam

#endif