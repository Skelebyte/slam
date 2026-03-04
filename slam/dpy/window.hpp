#ifndef SLAM_WINDOW_HPP
#define SLAM_WINDOW_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../evt/evt_sys.hpp"
#include "../math/vec2i.hpp"
#include <SDL3/SDL.h>
#include <string>

namespace slam::dpy {

struct Window : public Destroyable {
  Window(const sString &title = "SLAM", sUint w = 800, sUint h = 600,
         bool resizable = true, bool fullscreen = false);
  bool IsRunning() const;
  void Destroy() override;
  void PopupWindow(const sString &title, const sString &message,
                   bool isErrorWindow = false);
  SDL_Window *GetSDLWindow() const;
  void Update();
  void SwapAndClear();
  math::Vec2i GetDimensions();
  void Stop();
  math::Vec2i GetViewportPosition() const;
  math::Vec2i GetViewportSize() const;
  float GetViewportAspect() const;

private:
  bool running;
  SDL_Window *sdlWindow;
  bool pillarboxed;
  bool letterboxed;
  math::Vec2i viewportPosition;
  math::Vec2i viewportSize;
};

static void ErrorWindow();

} // namespace slam::dpy

#endif