#include "vec2.hpp"

using namespace slam;
using namespace slam::math;

void Vec2::Zero() {
  x = 0.0f;
  y = 0.0f;
}

Vec2::Vec2() {
  x = 0.0f;
  y = 0.0f;
}

Vec2::Vec2(float x_, float y_) {
  x = x_;
  y = y_;
}

float Vec2::Length() const { return sqrt(x * x + y * y); }

Vec2 Vec2::Normalized() {
  if (Length() == 0.0f) {
    return Vec2(0.0f, 0.0f);
  }

  Vec2 result = Vec2(x / Length(), y / Length());
  return result;
}

sString Vec2::ToString() const {
  return "(" + std::to_string(x) + ", " + std::to_string(y) + ")";
}

Vec2 Vec2::operator+(const Vec2 &other) const {
  return Vec2(x + other.x, y + other.y);
}

Vec2 Vec2::operator-(const Vec2 &other) const {
  return Vec2(x - other.x, y - other.y);
}

void Vec2::operator+=(const Vec2 &other) {
  x += other.x;
  y += other.y;
}

void Vec2::operator-=(const Vec2 &other) {
  x -= other.x;
  y -= other.y;
}

bool Vec2::operator==(const Vec2 &other) const {
  return (x == other.x && y == other.y);
}

// float vec2_dot(Vec2 a, Vec2 b) { return a.x * b.x + a.y * b.y; }

// float vec2_length(Vec2 vec) { return sqrt(vec.x * vec.x + vec.y * vec.y);
// }

// float vec2_magnitude(Vec2 vec) { return sqrt(vec.x * vec.x + vec.y *
// vec.y);
// }

// Vec2 vec2_normalize(Vec2 vec) {
//   if (vec2_magnitude(vec) == 0.0f)
//     return zero();

//   Vec2 b = {
//       vec.x / vec2_magnitude(vec),
//       vec.y / vec2_magnitude(vec),
//   };

//   return b;
// }

// bool vec2_is_equal(Vec2 a, Vec2 b) { return (a.x == b.x && a.y == b.y); }

// Vec2 vec2_cross(Vec2 a, Vec2 b) {
//   Vec2 cross = {
//       a.y * b.x - a.x * b.y,
//       a.y * b.x - a.x * b.y,
//   };
//   return cross;
// }

// float vec2_distance(Vec2 a, Vec2 b) {
//   return sqrt(pow((b.x - a.x), 2) + pow((b.y, a.y), 2));
// }