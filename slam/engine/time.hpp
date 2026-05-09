#ifndef SLAM_TIME_HPP
#define SLAM_TIME_HPP

#include "common.hpp"

namespace slam {
struct Time {
  static float32 DeltaTime();
  static float32 UnscaledDeltaTime();
  static void SetTimeScale(float32 scale);
  static float32 GetTimeScale();
  static uint64 MsToNs(uint32 value);
};
} // namespace slam

#endif