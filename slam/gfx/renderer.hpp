#ifndef SLAM_RENDERER_HPP
#define SLAM_RENDERER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "../util/file.hpp"
#include "shader.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {

struct Renderer : public Singleton<Renderer> {
  void Init(dpy::Window *window);
  void Shutdown();
  void ToggleWireframe();
  void AddShader(const str &name, const str &fragPath, const str &vertPath);
  Shader *GetShader(const str &name);

  str shaderPath = "assets/shaders/";
  math::Vec3 *cameraPosition = nullptr;
  math::Vec3 *cameraRotation = nullptr;
  math::Mat4 *cameraView = nullptr;
  math::Mat4 *cameraProjection = nullptr;

private:
  List<Shader> shaders;
  SDL_GLContext gl;
  bool wireframe;
};
} // namespace slam::gfx

#endif