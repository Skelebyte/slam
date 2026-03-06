#include "mathf.hpp"
#include <iostream>
#include <math.h>

using namespace slam;
using namespace slam::math;

float Mathf::ToRadians(float value) {
  float result = value * M_PI / 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::ToDegrees(float value) {
  float result = value / M_PI * 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float Mathf::Lerp(float a, float b, float t) { return a + t * (b - a); }

float Mathf::Clamp(float target, float min, float max) {
  if (target > max)
    return max;
  if (target < min)
    return min;

  return target;
}

float Mathf::Wrap(float target, float min, float max) {
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

Vec3 Mathf::RotateX(const Vec3 &target, float angleDeg) {
  return glm::rotateX(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateY(const Vec3 &target, float angleDeg) {
  return glm::rotateY(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateZ(const Vec3 &target, float angleDeg) {
  return glm::rotateZ(target, Mathf::ToRadians(angleDeg));
}

// Vec2 Fmath::v3_to_v2(Vec3 value) { return Vec2(value.x, value.y); }

// Vec3 Fmath::v2_to_v3(Vec2 value, float z_value) {
//   return vec3(value.x, value.y, z_value);
// }