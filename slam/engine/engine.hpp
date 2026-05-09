#ifndef SLAM_ENGINE_HPP
#define SLAM_ENGINE_HPP

#include "common.hpp"
#include "dpy/window.hpp"
#include "err/err_sys.hpp"
#include "evt/evt_sys.hpp"
// #include "gfx/renderer.hpp"
#include <SDL3/SDL.h>

namespace slam {

struct Engine : public Singleton<Engine> {
  static void Init(uint16 = 60);
  static void Shutdown();
  static void BeginFrame();
  static void EndFrame();
  static bool IsProcessFrame();
  static void SetTargetFps(uint16 fps);
  static uint32 GetFps();
  static void SetWindow(dpy::Window *window);
  static dpy::Window *GetWindow();
  static void SetDrawEntityIcons(bool value);
  static bool GetDrawEntityIcons();
  static float32 GetDeltaTime();
  static void SetTimeScale(float32 value);
  static float32 GetTimeScale();
  static void SetDrawnEntities(uint32 value);
  static uint32 GetDrawnEntities();
  static str GetVersion();

private:
  dpy::Window *window;
  float32 deltaTime;
  float32 timeScale = 1.0f;
  bool drawEntityIcons;
  bool isProcessFrame = true;
  float32 targetFps;
  uint32 fps;
  uint32 frames;
  float32 frameTime;
  float32 processedDeltaTime;
  float32 first;
  float32 last;
  uint32 drawnEntities;
};

} // namespace slam

#endif