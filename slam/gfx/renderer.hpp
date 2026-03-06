#ifndef SLAM_RENDERER_HPP
#define SLAM_RENDERER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../util/file.hpp"
#include "shader.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {

struct Renderer : public Singleton<Renderer> {
  Renderer() = default;
  void Init(dpy::Window *window);
  void Shutdown();
  void ToggleWireframe();
  void AddShader(const sString &name, const sString &fragPath,
                 const sString &vertPath);
  Shader *GetShader(const sString &name);

  sString shaderPath = "assets/shaders/";

private:
  List<Shader> shaders;
  SDL_GLContext gl;
  bool wireframe;
};
} // namespace slam::gfx

#endif