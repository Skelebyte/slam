#ifndef SLAM_ELEMENT_HPP
#define SLAM_ELEMENT_HPP

#include "../common.hpp"
#include "../engine.hpp"
#include "../math/mathf.hpp"

namespace slam::ui {

struct Element {
  Element();
  virtual void Update() = 0;
  math::Vec2 position;
};

} // namespace slam::ui

#endif