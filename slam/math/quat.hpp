#ifndef SLAM_QUAT_HPP
#define SLAM_QUAT_HPP

#include "mathf.hpp"
#include "vec3.hpp"
#include <cmath>

namespace slam::math {

union Quat {
  struct {
    float x, y, z, w;
  };
  float data[3];
  Quat(bool identity = true);
  Quat(float x, float y, float z, float w = 1.0f);
  Quat(Vec3 xyz, float w = 1.0f);
  Quat operator*(const Quat &other) const;
  Quat operator*(const Vec3 &other) const;
  Vec3 ToEuler() const;
  static Quat FromEuler(const Vec3 &angles);
};

} // namespace slam::math

#endif