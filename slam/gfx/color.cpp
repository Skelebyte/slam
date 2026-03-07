#include "color.hpp"

using namespace slam;
using namespace slam::gfx;
using namespace slam::math;

RGB255::RGB255(sU32 rgb) {
  sU32 value = Mathf::Wrap(rgb, 0, 255);
  r = value;
  g = value;
  b = value;
}

RGB255::RGB255(sU32 r, sU32 g, sU32 b) {
  this->r = Mathf::Wrap(r, 0, 255);
  this->g = Mathf::Wrap(g, 0, 255);
  this->b = Mathf::Wrap(b, 0, 255);
}

RGB::RGB(sF32 rgb) {
  sF32 value = Mathf::Wrap(rgb, 0.0f, 1.0f);
  r = rgb;
  g = rgb;
  b = rgb;
}

RGB::RGB(sF32 r, sF32 g, sF32 b) {
  this->r = Mathf::Wrap(r, 0.0f, 1.0f);
  this->g = Mathf::Wrap(g, 0.0f, 1.0f);
  this->b = Mathf::Wrap(b, 0.0f, 1.0f);
}

namespace slam::gfx {
RGB ToRGB(const RGB255 &color) {
  return RGB(color.r / 255.0f, color.g / 255.0f, color.b / 255.0f);
}
RGB255 ToRGB255(const RGB &color) {
  return RGB255(color.r * 255, color.g * 255, color.b * 255);
}
} // namespace slam::gfx