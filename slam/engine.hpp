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
  void Init(u32 fps = 60);
  void Shutdown();
  void BeginFrame();
  void EndFrame();
  bool IsDrawFrame() const;
  void SetTargetFps(u32 fps);
  u32 GetFps() const;

  dpy::Window *window = nullptr;
  f32 deltaTime;
  f32 timeScale = 1.0f;
  bool drawEntityIcons;

private:
  bool isDrawFrame = true;
  f32 targetFps;
  u32 fps;
  u32 frames;
  f32 frameTime;
  f32 processedDeltaTime;
  f32 first;
  f32 last;
};

} // namespace slam

#endif