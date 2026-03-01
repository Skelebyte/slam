#ifndef SLAM_VEC2I_H
#define SLAM_VEC2I_H

#include <math.h>
#include <stdbool.h>

namespace slam::math {

union Vec2i {
  struct {
    int x;
    int y;
  };
  int data[2];
  Vec2i();
  Vec2i(int x_, int y_);
  void Zero();
  float Length() const;
  void Normalize();

  Vec2i operator+(const Vec2i &other) const;
  Vec2i operator-(const Vec2i &other) const;
  void operator+=(const Vec2i &other);
  void operator-=(const Vec2i &other);
  bool operator==(const Vec2i &other) const;
};

} // namespace slam::math

#endif