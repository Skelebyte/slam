#ifndef SLAM_RENDERER_HPP
#define SLAM_RENDERER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../util/file.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {

struct Renderer : public Singleton<Renderer> {
  Renderer() = default;
  void Init(dpy::Window *window);
  void Shutdown();

private:
  SDL_GLContext gl;
};
} // namespace slam::gfx

#endif