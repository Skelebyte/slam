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
  void Init();
  void Shutdown();

  dpy::Window *window = nullptr;
};

} // namespace slam

#endif