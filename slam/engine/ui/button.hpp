#ifndef SLAM_BUTTON_HPP
#define SLAM_BUTTON_HPP

#include "../evt/evt.hpp"
#include "ui_context.hpp"

namespace slam::ui {

struct Button : public Element {
  Button(const str &text);
  void Update() override;
  bool IsPressed() const;

  str content;

  evt::Event OnPressed;

private:
  bool pressed = false;
};

} // namespace slam::ui

#endif