#ifndef SLAM_VEC3_HPP
#define SLAM_VEC3_HPP

#include "../common.hpp"
#include "../list.hpp"
#include "pi.hpp"
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace slam::math {

union Vec3 {
  struct {
    float x, y, z;
  };
  float data[3];
  Vec3();
  Vec3(float xyz_);
  Vec3(float x_, float y_, float z_);
  void Zero();
  void Rotate(float angle, Vec3 axis);
  float Length() const;
  Vec3 Normalized();
  static float Dot(const Vec3 &a, const Vec3 &b);
  static Vec3 Cross(const Vec3 &a, const Vec3 &b);
  sString ToString() const;
  static Vec3 FromString(sString string);

  Vec3 operator+(const Vec3 &other) const;
  Vec3 operator-(const Vec3 &other) const;
  Vec3 operator*(const Vec3 &other) const;
  Vec3 operator*(const float &other) const;
  void operator+=(const Vec3 &other);
  void operator-=(const Vec3 &other);
  bool operator==(const Vec3 &other) const;
};

} // namespace slam::math

#endif
