#ifndef SLAM_ENGINE_HPP
#define SLAM_ENGINE_HPP

#include "../third_party/glad/glad.h"
#include "common.hpp"
#include "dpy/window.hpp"
#include "err/err_sys.hpp"
#include "evt/evt_sys.hpp"
// #include "gfx/renderer.hpp"
#include <SDL3/SDL.h>

namespace slam {

struct Engine : public Singleton<Engine> {
  static void Init(u32 fps = 60);
  static void Shutdown();
  static void BeginFrame();
  static void EndFrame();
  static bool IsProcessFrame();
  static void SetTargetFps(u32 fps);
  static u32 GetFps();
  static void SetWindow(dpy::Window *window);
  static dpy::Window *GetWindow();
  static void SetDrawEntityIcons(bool value);
  static bool GetDrawEntityIcons();
  static f32 GetDeltaTime();
  static void SetTimeScale(f32 value);
  static f32 GetTimeScale();
  static void SetDrawnEntities(u32 value);
  static u32 GetDrawnEntities();

private:
  dpy::Window *window;
  f32 deltaTime;
  f32 timeScale = 1.0f;
  bool drawEntityIcons;
  bool isProcessFrame = true;
  f32 targetFps;
  u32 fps;
  u32 frames;
  f32 frameTime;
  f32 processedDeltaTime;
  f32 first;
  f32 last;
  u32 drawnEntities;
};

} // namespace slam

#endif