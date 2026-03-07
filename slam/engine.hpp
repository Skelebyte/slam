#ifndef SLAM_ENGINE_HPP
#define SLAM_ENGINE_HPP

#include "common.hpp"
#include "dpy/window.hpp"
#include "err/err_sys.hpp"
#include "evt/evt_sys.hpp"
#include "ext/glad/glad.h"
// #include "gfx/renderer.hpp"
#include <SDL3/SDL.h>

namespace slam {

struct Engine : public Singleton<Engine> {
  void Init(sU32 fps = 60);
  void Shutdown();
  void BeginFrame();
  void EndFrame();
  bool IsDrawFrame() const;
  void SetTargetFps(sU32 fps);
  sU32 GetFps() const;

  dpy::Window *window = nullptr;
  sF32 deltaTime;
  sF32 timeScale = 1.0f;
  bool drawEntityIcons;

private:
  bool isDrawFrame = true;
  sF32 targetFps;
  sU32 fps;
  sU32 frames;
  sF32 frameTime;
  sF32 processedDeltaTime;
  sF32 first;
  sF32 last;
};

} // namespace slam

#endif