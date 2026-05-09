#include "color.hpp"
#include <cmath>

using namespace slam;
using namespace slam::gfx;
using namespace slam::math;

RGB255::RGB255(uint32 rgb) {
  uint32 value = Mathf::Wrap(rgb, 0, 255);
  r = value;
  g = value;
  b = value;
}

RGB255::RGB255(uint32 r, uint32 g, uint32 b) {
  this->r = Mathf::Wrap(r, 0, 255);
  this->g = Mathf::Wrap(g, 0, 255);
  this->b = Mathf::Wrap(b, 0, 255);
}

RGB::RGB(float32 rgb) {
  float32 value = Mathf::Wrap(rgb, 0.0f, 1.0f);
  r = rgb;
  g = rgb;
  b = rgb;
}

RGB::RGB(float32 r, float32 g, float32 b) {
  this->r = Mathf::Wrap(r, 0.0f, 1.0f);
  this->g = Mathf::Wrap(g, 0.0f, 1.0f);
  this->b = Mathf::Wrap(b, 0.0f, 1.0f);
}

HSV::HSV(float32 hue, float32 sat, float32 val) {
  this->hue = Mathf::Clamp(hue, 0.0f, 360.0f);
  saturation = Mathf::Clamp(sat, 0.0f, 1.0f);
  value = Mathf::Clamp(val, 0.0f, 1.0f);
}

namespace slam::gfx {
RGB ToRGB(const RGB255 &color) {
  return RGB(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}
RGB ToRGB(const HSV &color) {

  float32 h = color.hue / 60;
  float32 i = std::floor(h);
  float32 f = h - i;
  float32 p = color.value * (1 - color.saturation);
  float32 q = color.value * (1 - color.saturation * f);
  float32 t = color.value * (1 - color.saturation * (1 - f));

  int32 sector = (int32)i;
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