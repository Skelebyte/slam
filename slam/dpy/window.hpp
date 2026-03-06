#ifndef SLAM_WINDOW_HPP
#define SLAM_WINDOW_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../evt/evt_sys.hpp"
#include "../math/mathf.hpp"
#include <SDL3/SDL.h>
#include <string>

namespace slam::dpy {

struct Window : public Destroyable {
  Window(const sString &title = "SLAM", sU32 w = 800, sU32 h = 600,
         bool resizable = true, bool fullscreen = false);
  bool IsRunning() const;
  void Destroy() override;
  void PopupWindow(const sString &title, const sString &message,
                   bool isErrorWindow = false);
  SDL_Window *GetSDLWindow() const;
  void Update();
  void SwapAndClear();
  math::Vec2 GetDimensions();
  void Stop();
  math::Vec2 GetViewportPosition() const;
  math::Vec2 GetViewportSize() const;
  sF32 GetViewportAspect() const;
  void SetTitle(const sString &title);

  bool appendFpsToTitle;

private:
  bool running;
  SDL_Window *sdlWindow;
  bool pillarboxed;
  bool letterboxed;
  math::Vec2 viewportPosition;
  math::Vec2 viewportSize;
  sString title;
};

static void ErrorWindow();

} // namespace slam::dpy

#endif