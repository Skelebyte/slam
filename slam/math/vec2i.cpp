#include "vec2i.hpp"

using namespace slam;
using namespace slam::math;

void Vec2i::Zero() {
  x = 0;
  y = 0;
}

Vec2i::Vec2i() {
  x = 0;
  y = 0;
}

Vec2i::Vec2i(int x_, int y_) {
  x = x_;
  y = y_;
}

float Vec2i::Length() const { return sqrt(x * x + y * y); }

void Vec2i::Normalize() {
  if (Length() == 0.0f) {
    Zero();
    return;
  }

  x /= Length();
  y /= Length();
}

Vec2i Vec2i::operator+(const Vec2i &other) const {
  return Vec2i(x + other.x, y + other.y);
}

Vec2i Vec2i::operator-(const Vec2i &other) const {
  return Vec2i(x - other.x, y - other.y);
}

void Vec2i::operator+=(const Vec2i &other) {
  x += other.x;
  y += other.y;
}

void Vec2i::operator-=(const Vec2i &other) {
  x -= other.x;
  y -= other.y;
}

bool Vec2i::operator==(const Vec2i &other) const {
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