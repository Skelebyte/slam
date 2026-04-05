#include "color.hpp"
#include <cmath>

using namespace slam;
using namespace slam::gfx;
using namespace slam::math;

RGB255::RGB255(u32 rgb) {
  u32 value = Mathf::Wrap(rgb, 0, 255);
  r = value;
  g = value;
  b = value;
}

RGB255::RGB255(u32 r, u32 g, u32 b) {
  this->r = Mathf::Wrap(r, 0, 255);
  this->g = Mathf::Wrap(g, 0, 255);
  this->b = Mathf::Wrap(b, 0, 255);
}

RGB::RGB(f32 rgb) {
  f32 value = Mathf::Wrap(rgb, 0.0f, 1.0f);
  r = rgb;
  g = rgb;
  b = rgb;
}

RGB::RGB(f32 r, f32 g, f32 b) {
  this->r = Mathf::Wrap(r, 0.0f, 1.0f);
  this->g = Mathf::Wrap(g, 0.0f, 1.0f);
  this->b = Mathf::Wrap(b, 0.0f, 1.0f);
}

HSV::HSV(f32 hue, f32 sat, f32 val) {
  this->hue = Mathf::Clamp(hue, 0.0f, 360.0f);
  saturation = Mathf::Clamp(sat, 0.0f, 1.0f);
  value = Mathf::Clamp(val, 0.0f, 1.0f);
}

namespace slam::gfx {
RGB ToRGB(const RGB255 &color) {
  return RGB(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}
RGB ToRGB(const HSV &color) {

  f32 h = color.hue / 60;
  f32 i = std::floor(h);
  f32 f = h - i;
  f32 p = color.value * (1 - color.saturation);
  f32 q = color.value * (1 - color.saturation * f);
  f32 t = color.value * (1 - color.saturation * (1 - f));

  i32 sector = (i32)i;
  if (sector == 0)
    return RGB(color.value, t, p);
  if (sector == 1)
    return RGB(q, color.value, p);
  if (sector == 2)
    return RGB(p, color.value, t);
  if (sector == 3)
    return RGB(p, q, color.value);
  if (sector == 4)
    return RGB(t, p, color.value);
  if (sector == 5)
    return RGB(color.value, p, q);

  return RGB();
}
RGB255 ToRGB255(const RGB &color) {
  return RGB255(color.r * 255, color.g * 255, color.b * 255);
}
} // namespace slam::gfx