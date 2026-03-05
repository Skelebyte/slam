#include "quat.hpp"
#include "mathf.hpp"
#include <algorithm>

using namespace slam;
using namespace slam::math;

Quat::Quat(bool identity) {

  x = 0;
  y = 0;
  z = 0;
  w = 0;
  if (identity) {
    w = 1;
  }
}

Quat::Quat(float x, float y, float z, float w) {
  this->x = x;
  this->y = y;
  this->z = z;
  this->w = w;
}

Quat::Quat(Vec3 xyz, float w) {
  x = xyz.x;
  y = xyz.y;
  z = xyz.z;
  this->w = w;
}

Quat Quat::operator*(const Quat &other) const {
  Quat value = Quat();

  value.x = w * other.x + x * other.w + y * other.z - z * other.y;
  value.y = w * other.y - x * other.z + y * other.w + z * other.x;
  value.z = w * other.z + x * other.y - y * other.x + z * other.w;
  value.w = w * other.w - x * other.x - y * other.y - z * other.z;

  return value;
}

Quat Quat::operator*(const Vec3 &other) const {
  Quat inverse = Quat(-x, -y, -z, w);
  return *this * Quat(other, 0.0) * inverse;
}

Vec3 Quat::ToEuler() const {
  Vec3 value = Vec3();

  value.x = atan2(2 * (w * x + y * z), 1 - 2 * (pow(x, 2) + pow(y, 2)));
  value.y = asin(std::clamp((float)(2.0f * (w * y - z * x)), -1.0f, 1.0f));
  value.z = atan2(2 * (w * z + x * y), 1 - 2 * (pow(z, 2) + pow(y, 2)));

  value.x = Mathf::ToDegrees(value.x);
  value.y = Mathf::ToDegrees(value.y);
  value.z = Mathf::ToDegrees(value.z);

  return value;
}

Quat Quat::FromEuler(const Vec3 &angles) {
  Quat value = Quat();
  Vec3 rads = Vec3(Mathf::ToRadians(angles.x), Mathf::ToRadians(angles.y),
                   Mathf::ToRadians(angles.z));

  float cosX = cos(rads.x / 2);
  float sinX = sin(rads.x / 2);

  float cosY = cos(rads.y / 2);
  float sinY = sin(rads.y / 2);

  float cosZ = cos(rads.z / 2);
  float sinZ = sin(rads.z / 2);

  value.x = sinX * cosY * cosZ + cosX * sinY * sinZ;
  value.y = cosX * sinY * cosZ - sinX * cosY * sinZ;
  value.z = cosX * cosY * sinZ + sinX * sinY * cosZ;
  value.w = cosX * cosY * cosZ - sinX * sinY * sinZ;

  return value;
}