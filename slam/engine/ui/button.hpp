#ifndef SLAM_BUTTON_HPP
#define SLAM_BUTTON_HPP

#include "ui_context.hpp"

namespace slam::ui {

struct Button : public Element {
  Button(const str &text);
  void Update() override;
  bool IsPressed() const;

  str content;

private:
  bool pressed = false;
};

} // namespace slam::ui

#endif