#include "element.hpp"
#include "ui_context.hpp"

using namespace slam;
using namespace slam::ui;

Element::Element() { UIContext::AddElement(this); }