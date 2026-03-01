#ifndef VEC2_HPP
#define VEC2_HPP

#include "../common.hpp"
#include <iostream>
#include <math.h>
#include <stdbool.h>

namespace slam::math {

union Vec2 {
  struct {
    float x;
    float y;
  };
  float data[2];
  Vec2();
  Vec2(float x_, float y_);
  void Zero();
  float Length() const;
  Vec2 Normalized();

  sString ToString() const;

  Vec2 operator+(const Vec2 &other) const;
  Vec2 operator-(const Vec2 &other) const;
  void operator+=(const Vec2 &other);
  void operator-=(const Vec2 &other);
  bool operator==(const Vec2 &other) const;
};

} // namespace slam::math

#endif
