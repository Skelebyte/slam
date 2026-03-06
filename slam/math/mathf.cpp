#include "mathf.hpp"
#include <iostream>
#include <math.h>

using namespace slam;
using namespace slam::math;

sF32 Mathf::ToRadians(sF32 value) {
  sF32 result = value * M_PI / 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

sF32 Mathf::ToDegrees(sF32 value) {
  sF32 result = value / M_PI * 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

sF32 Mathf::Lerp(sF32 a, sF32 b, sF32 t) { return a + t * (b - a); }

sF32 Mathf::Clamp(sF32 target, sF32 min, sF32 max) {
  if (target > max)
    return max;
  if (target < min)
    return min;

  return target;
}

sF32 Mathf::Wrap(sF32 target, sF32 min, sF32 max) {
  if (target > max)
    return target - max;
  if (target < min)
    return target + abs(min);

  return target;
}

sString Mathf::ToString(const Vec3 &target) {
  return std::to_string(target.x) + "," + std::to_string(target.y) + "," +
         std::to_string(target.z);
}

Vec3 Mathf::Normalized(const Vec3 &target) {
  if (glm::length(target) == 0) {
    return Vec3(0);
  }

  return glm::normalize(target);
}

Vec3 Mathf::RotateX(const Vec3 &target, sF32 angleDeg) {
  return glm::rotateX(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateY(const Vec3 &target, sF32 angleDeg) {
  return glm::rotateY(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateZ(const Vec3 &target, sF32 angleDeg) {
  return glm::rotateZ(target, Mathf::ToRadians(angleDeg));
}

// Vec2 Fmath::v3_to_v2(Vec3 value) { return Vec2(value.x, value.y); }

// Vec3 Fmath::v2_to_v3(Vec2 value, sF32 z_value) {
//   return vec3(value.x, value.y, z_value);
// }