#ifndef SLAM_COLOR_HPP
#define SLAM_COLOR_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"

namespace slam::gfx {

// RGB as `sU32`, ranging from `0` to `255`
union RGB255 {
  struct {
    sU32 r;
    sU32 g;
    sU32 b;
  };
  sU32 data[3];

  RGB255(sU32 rgb = 255);
  RGB255(sU32 r, sU32 g, sU32 b);
};

// RGB as `sF32`, ranging from `0.0f` to `1.0f`.
union RGB {
  struct {
    sF32 r;
    sF32 g;
    sF32 b;
  };
  sF32 data[3];
  RGB(sF32 rgb = 1.0f);
  RGB(sF32 r, sF32 g, sF32 b);
};

RGB ToRGB(const RGB255 &color);
RGB255 ToRGB255(const RGB &color);

} // namespace slam::gfx

#endif