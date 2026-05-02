#ifndef SLAM_COLOR_HPP
#define SLAM_COLOR_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"

namespace slam::gfx {

// RGB as `u32`, ranging from `0` to `255`
union RGB255 {
  struct {
    u32 r;
    u32 g;
    u32 b;
  };
  u32 data[3];

  RGB255(u32 rgb = 255);
  RGB255(u32 r, u32 g, u32 b);
};

// RGB as `f32`, ranging from `0.0f` to `1.0f`.
union RGB {
  struct {
    f32 r;
    f32 g;
    f32 b;
  };
  f32 data[3];
  RGB(f32 rgb = 1.0f);
  RGB(f32 r, f32 g, f32 b);
};

struct HSV {
  HSV(f32 hue = 0.0f, f32 sat = 0.0f, f32 val = 0.0f);

  f32 hue;
  f32 saturation;
  f32 value;
};

RGB ToRGB(const RGB255 &color);
RGB ToRGB(const HSV &color);
RGB255 ToRGB255(const RGB &color);

} // namespace slam::gfx

#endif