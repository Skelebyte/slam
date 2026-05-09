#include "mathf.hpp"
#include <iostream>
#include <math.h>

using namespace slam;
using namespace slam::math;

float32 Mathf::ToRadians(float32 value) {
  float32 result = value * M_PI / 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float32 Mathf::ToDegrees(float32 value) {
  float32 result = value / M_PI * 180;

  if (result != result) {
    std::cout << "Mathf::radians: value is NaN, returning 0" << std::endl;
    return 0;
  }

  return result;
}

float32 Mathf::Lerp(float32 a, float32 b, float32 t) { return a + t * (b - a); }

float32 Mathf::Clamp(float32 target, float32 min, float32 max) {
  if (target > max)
    return max;
  if (target < min)
    return min;

  return target;
}

float32 Mathf::Wrap(float32 target, float32 min, float32 max) {
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

float32 Mathf::Distance(const Vec3 &a, const Vec3 &b) {
  return glm::distance(a, b);
}

float32 Mathf::Dot(CRef<Vec3> a, CRef<Vec3> b) { return glm::dot(a, b); }

int32 Mathf::Abs(int32 value) { return abs(value); }

float32 Mathf::Abs(float32 value) { return abs(value); }

Vec3 Mathf::Normalized(const Vec3 &target) {
  if (glm::length(target) == 0) {
    return Vec3(0);
  }

  return glm::normalize(target);
}

Vec3 Mathf::RotateX(const Vec3 &target, float32 angleDeg) {
  return glm::rotateX(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateY(const Vec3 &target, float32 angleDeg) {
  return glm::rotateY(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::RotateZ(const Vec3 &target, float32 angleDeg) {
  return glm::rotateZ(target, Mathf::ToRadians(angleDeg));
}

Vec3 Mathf::ToEuler(const Quat &target) {

  Mat4 matrix = glm::mat4_cast(target);

  float y, p, r;
  glm::extractEulerAngleYXZ(matrix, y, p, r);

  return Vec3(y, p, r);
}

Quat Mathf::ToQuat(const Vec3 &target) { return Quat(glm::radians(target)); }

int32 Mathf::Random(int32 max) {
  srand(SDL_GetTicksNS());

  int32 value = rand() % max;

  return value;
}