#include "vec3.hpp"

using namespace slam;
using namespace slam::math;

void Vec3::Zero() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

Vec3::Vec3() {
  x = 0.0f;
  y = 0.0f;
  z = 0.0f;
}

Vec3::Vec3(float x_, float y_, float z_) {
  x = x_;
  y = y_;
  z = z_;
}

Vec3::Vec3(float xyz_) {
  x = xyz_;
  y = xyz_;
  z = xyz_;
}

void Vec3::Rotate(float angle, Vec3 axis) {
  axis = axis.Normalized();
  Vec3 old = *this;

  if (axis.x != 0) {
    this->y = old.y * cos(angle) - old.z * sin(angle);
    this->z = old.y * sin(angle) + old.z * cos(angle);
    old = *this;
  }

  if (axis.y != 0) {
    this->x = old.x * cos(angle) + old.z * sin(angle);
    this->z = -old.x * sin(angle) + old.z * cos(angle);
    old = *this;
  }

  if (axis.z != 0) {
    this->x = old.x * cos(angle) - old.y * sin(angle);
    this->y = old.x * sin(angle) + old.y * cos(angle);
  }
}

float Vec3::Length() const { return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2)); }

Vec3 Vec3::Normalized() {
  if (Length() == 0.0f) {
    return Vec3(0.0f, 0.0f, 0.0f);
  }
  Vec3 result = Vec3(x / Length(), y / Length(), z / Length());
  return result;
}

float Vec3::Dot(const Vec3 &a, const Vec3 &b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vec3 Vec3::Cross(const Vec3 &a, const Vec3 &b) {
  return Vec3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z,
              a.x * b.y - a.y * b.x);
}

sString Vec3::ToString() const {
  return std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(z);
}

Vec3 Vec3::FromString(const sString &string) {
  Vec3 result;
  List<sString> strings;
  std::istringstream stream = std::istringstream(string);
  sString s;
  while (getline(stream, s, ',')) {
    strings.Add(s);
  }

  for (int i = 0; i < 3; i++) {
    result.data[i] = std::stof(strings[i]);
  }

  return result;
}

Vec3 Vec3::operator+(const Vec3 &other) const {
  return Vec3(x + other.x, y + other.y, z + other.z);
}

Vec3 Vec3::operator-(const Vec3 &other) const {
  return Vec3(x - other.x, y - other.y, z - other.z);
}

Vec3 Vec3::operator*(const Vec3 &other) const {
  return Vec3(x * other.x, y * other.y, z * other.z);
}

Vec3 Vec3::operator*(const float &other) const {
  return Vec3(x * other, y * other, z * other);
}

void Vec3::operator+=(const Vec3 &other) {
  x += other.x;
  y += other.y;
  z += other.z;
}

void Vec3::operator-=(const Vec3 &other) {
  x -= other.x;
  y -= other.y;
  z -= other.z;
}

bool Vec3::operator==(const Vec3 &other) const {
  return (x == other.x && y == other.y && z == other.z);
}