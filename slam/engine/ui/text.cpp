#include "text.hpp"

using namespace slam;
using namespace slam::ui;

Text::Text(const str &text) : Element() { content = text; }

void Text::Update() { ImGui::Text("%s", content.c_str()); }