#include "button.hpp"

using namespace slam;
using namespace slam::ui;

Button::Button(const str &text) { content = text; }

void Button::Update() { pressed = ImGui::Button(content.c_str()); }

bool Button::IsPressed() const { return pressed; }