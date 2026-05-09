#ifndef SLAM_COLOR_HPP
#define SLAM_COLOR_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"

namespace slam::gfx {

// RGB as `uint32`, ranging from `0` to `255`
union RGB255 {
  struct {
    uint32 r;
    uint32 g;
    uint32 b;
  };
  uint32 data[3];

  RGB255(uint32 rgb = 255);
  RGB255(uint32 r, uint32 g, uint32 b);
};

// RGB as `float32`, ranging from `0.0f` to `1.0f`.
union RGB {
  struct {
    float32 r;
    float32 g;
    float32 b;
  };
  float32 data[3];
  RGB(float32 rgb = 1.0f);
  RGB(float32 r, float32 g, float32 b);
};

struct HSV {
  HSV(float32 hue = 0.0f, float32 sat = 0.0f, float32 val = 0.0f);

  float32 hue;
  float32 saturation;
  float32 value;
};

RGB ToRGB(const RGB255 &color);
RGB ToRGB(const HSV &color);
RGB255 ToRGB255(const RGB &color);

} // namespace slam::gfx

#endif