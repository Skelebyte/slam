#ifndef SLAM_UI_CONTEXT_HPP
#define SLAM_UI_CONTEXT_HPP

#include "../../third_party/imgui/imgui.h"
#include "../../third_party/imgui/imgui_impl_opengl3.h"
#include "../../third_party/imgui/imgui_impl_sdl3.h"
#include "../common.hpp"
#include "../engine.hpp"
#include "../gfx/renderer.hpp"
#include "../list.hpp"
#include "element.hpp"

namespace slam::ui {
struct UIContext : public Singleton<UIContext> {
  static void Init(CRef<str> defaultFont = "assets/fonts/RobotoMono.ttf");
  static void Shutdown();
  static ImGuiIO *GetIO();
  static void Update();
  static void AddElement(Element *element);

private:
  List<Element *> elements;
  ImGuiIO *io;
};
} // namespace slam::ui

#endif