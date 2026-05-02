#ifndef SLAM_TEXT_HPP
#define SLAM_TEXT_HPP

#include "element.hpp"

namespace slam::ui {
struct Text : public Element {
  Text(const str &text = "");
  void Update() override;

  str content;
};
} // namespace slam::ui

#endif