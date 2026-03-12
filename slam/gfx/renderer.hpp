#ifndef SLAM_RENDERER_HPP
#define SLAM_RENDERER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "../scn/transform.hpp"
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
  static SDL_GLContext *GetGLContext();

  str shaderPath = "assets/shaders/";
  Ptr<scn::Transform> cameraTransform = nullptr;
  Ptr<f32> cameraCullingAngle = nullptr;
  Ptr<f32> cameraCullingDistance = nullptr;
  math::Mat4 *cameraView = nullptr;
  math::Mat4 *cameraProjection = nullptr;

private:
  List<Shader> shaders;
  SDL_GLContext gl;
  bool wireframe;
};
} // namespace slam::gfx

#endif