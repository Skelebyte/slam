#include "mathf.hpp"
#include <iostream>
#include <math.h>

using namespace slam;
using namespace slam::math;

f32 Mathf::ToRadians(f32 value) {
  f32 result = value * M_PI / 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

f32 Mathf::ToDegrees(f32 value) {
  f32 result = value / M_PI * 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

f32 Mathf::Lerp(f32 a, f32 b, f32 t) { return a + t * (b - a); }

f32 Mathf::Clamp(f32 target, f32 min, f32 max) {
  if (target > max)
    return max;
  if (target < min)
    return min;

  return target;
}

f32 Mathf::Wrap(f32 target, f32 min, f32 max) {
  if (target > max)
    return target - max;
  if (target < min)
    return target + abs(min);

  return target;
}

str Mathf::ToString(const Vec3 &target) {
  return std::to_string(target.x) + "," + std::to_string(target.y) + "," +
         std::to_string(target.z);
}

str Mathf::ToString(const Quat &target) {
  return std::to_string(target.x) + "," + std::to_string(target.y) + "," +
         std::to_string(target.z) + "," + std::to_string(target.w);
}

f32 Mathf::Distance(const Vec3 &a, const Vec3 &b) {
  return glm::distance(a, b);
}

Vec3 Mathf::Normalized(const Vec3 &target) {
  if (glm::length(target) == 0) {
    return Vec3(0);
  }

  return glm::normalize(target);
}

Vec3 Mathf::RotateX(const Vec3 &target, f32 angleDeg) {
  return glm::rotateX(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateY(const Vec3 &target, f32 angleDeg) {
  return glm::rotateY(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateZ(const Vec3 &target, f32 angleDeg) {
  return glm::rotateZ(target, Mathf::ToRadians(angleDeg));
}

// Vec2 Fmath::v3_to_v2(Vec3 value) { return Vec2(value.x, value.y); }

// Vec3 Fmath::v2_to_v3(Vec2 value, f32 z_value) {
//   return vec3(value.x, value.y, z_value);
// }