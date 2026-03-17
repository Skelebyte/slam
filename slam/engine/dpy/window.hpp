#ifndef SLAM_WINDOW_HPP
#define SLAM_WINDOW_HPP

#include "../../third_party/imgui/imgui.h"
#include "../../third_party/imgui/imgui_impl_opengl3.h"
#include "../../third_party/imgui/imgui_impl_sdl3.h"
#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../evt/evt_sys.hpp"
#include "../math/mathf.hpp"
#include <SDL3/SDL.h>
#include <string>

namespace slam::dpy {

struct Window : public Destroyable {
  Window(const str &title = "SLAM", u32 w = 800, u32 h = 600,
         bool resizable = true, bool fullscreen = false);
  bool IsRunning() const;
  void Destroy() override;
  void PopupWindow(const str &title, const str &message,
                   bool isErrorWindow = false);
  SDL_Window *GetSDLWindow() const;
  void Update();
  void SwapAndClear();
  math::Vec2 GetDimensions();
  void Stop();
  math::Vec2 GetViewportPosition() const;
  math::Vec2 GetViewportSize() const;
  f32 GetViewportAspect() const;
  void SetTitle(const str &title);
  void ToggleFullscreen();

  bool appendFpsToTitle;

private:
  bool running;
  SDL_Window *sdlWindow;
  bool pillarboxed;
  bool letterboxed;
  math::Vec2 viewportPosition;
  math::Vec2 viewportSize;
  str title;
  bool fullscreen;
};

static void ErrorWindow();

} // namespace slam::dpy

#endif