#ifndef SLAM_RENDERER_HPP
#define SLAM_RENDERER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "../scn/transform.hpp"
#include "../util/file.hpp"
#include "shader.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {

// TODO: make all functions static.
struct Renderer : public Singleton<Renderer> {
  static void Init(dpy::Window *window);
  static void Shutdown();
  static void ToggleWireframe();
  static void AddShader(CRef<str> name, CRef<str> fragPath, CRef<str> vertPath);
  static Shader *GetShader(CRef<str> name);
  static SDL_GLContext *GetGLContext();
  static void SetShaderPath(CRef<str> path = "assets/shaders/");
  static str &GetShaderPath();
  static void SetCameraTransform(scn::Transform *target);
  static scn::Transform *GetCameraTransformPtr();
  static void SetCameraCullingAngle(f32 *angle);
  static f32 GetCameraCullingAngle();
  static f32 *GetCameraCullingAnglePtr();
  static void SetCameraCullingDistance(f32 *value);
  static f32 GetCameraCullingDistance();
  static f32 *GetCameraCullingDistancePtr();
  static void SetCameraView(math::Mat4 *value);
  static math::Mat4 *GetCameraViewPtr();
  static void SetCameraProjection(math::Mat4 *value);
  static math::Mat4 *GetCameraProjectionPtr();
  static void SetSkyColor(RGB color);
  static RGB GetSkyColor();
  static RGB *GetSkyColorPtr();
  static void SetFogColor(RGB color);
  static RGB GetFogColor();
  static RGB *GetFogColorPtr();

private:
  scn::Transform *cameraTransform = nullptr;
  f32 *cameraCullingAngle = nullptr;
  f32 *cameraCullingDistance = nullptr;
  math::Mat4 *cameraView = nullptr;
  math::Mat4 *cameraProjection = nullptr;
  RGB skyColor = RGB(0.1f);
  RGB fogColor = RGB(0.1f);
  str shaderPath;
  List<Shader> shaders;
  SDL_GLContext gl;
  bool wireframe;
};
} // namespace slam::gfx

#endif