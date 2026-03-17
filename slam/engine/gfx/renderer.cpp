#include "renderer.hpp"
#include <SDL3/SDL_video.h>

using namespace slam;
using namespace slam::dpy;
using namespace slam::gfx;
using namespace slam::err;
using namespace slam::util;
using namespace slam::scn;
using namespace slam::math;

void Renderer::Init(dpy::Window *window) {
  if (Get().IsInitialized() == true) {
    THROW_ERROR(WARNING.Derived("", "Renderer is already initialized!"));
    return;
  }

  Get().gl = SDL_GL_CreateContext(window->GetSDLWindow());
  if (Get().gl == nullptr) {
    THROW_ERROR(
        FATAL.Derived("", "Create to create OpenGL context. SDL error: " +
                              str(SDL_GetError())));
    return;
  }

  SDL_GL_MakeCurrent(window->GetSDLWindow(), Get().gl);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    THROW_ERROR(FATAL.Derived("", "Failed to initialize glad! remind me to "
                                  "come back here add a get_error func"));
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  Get().shaders = List<Shader>();

  SetShaderPath();

  AddShader("default", "fragment.glsl", "vertex.glsl");
  AddShader("line", "line_frag.glsl", "line_vert.glsl");
  AddShader("ui", "ui_frag.glsl", "ui_vert.glsl");
  AddShader("billboard", "billboard_frag.glsl", "billboard_vert.glsl");

  GetShader("default")->AddUniform("model");
  GetShader("default")->AddUniform("view");
  GetShader("default")->AddUniform("projection");
  GetShader("default")->AddUniform("diffuse_texture");
  GetShader("default")->AddUniform("light_color");
  GetShader("default")->AddUniform("color");
  GetShader("default")->AddUniform("light_position");
  GetShader("default")->AddUniform("ambient_color");
  GetShader("default")->AddUniform("sky_color");
  GetShader("default")->AddUniform("camera_position");
  GetShader("default")->AddUniform("density");
  GetShader("default")->AddUniform("gradient");
  GetShader("default")->AddUniform("affected_by_fog");
  GetShader("default")->AddUniform("unlit");
  // GetShader("default")->AddUniform("");

  GetShader("line")->AddUniform("view");
  GetShader("line")->AddUniform("projection");
  GetShader("line")->AddUniform("model");
  GetShader("line")->AddUniform("color");

  GetShader("billboard")->AddUniform("view");
  GetShader("billboard")->AddUniform("projection");
  GetShader("billboard")->AddUniform("model");
  GetShader("billboard")->AddUniform("diffuse_texture");

  Get().initialized = true;
}

void Renderer::Shutdown() {
  SDL_GL_DestroyContext(Get().gl);

  // clean up shaders
  for (u32 i = 0; i < Get().shaders.Size(); i++) {
    Get().shaders[i].Destroy();
  }
  Get().shaders.Clear();

  Get().initialized = false;
}

void Renderer::ToggleWireframe() {
  Get().wireframe = !Get().wireframe;

  if (Get().wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void Renderer::AddShader(CRef<str> name, CRef<str> fragPath,
                         CRef<str> vertPath) {
  bool silence = ErrorSystem::Get().silenceWarnings;

  ErrorSystem::Get().silenceWarnings = true;
  Shader *temp = GetShader(name);
  ErrorSystem::Get().silenceWarnings = silence;
  if (temp != nullptr) {
    THROW_ERROR(WARNING.Derived("", "A shader with the name `" + name +
                                        "` already exists!"));
    return;
  }

  Get().shaders.Add(
      Shader(name, GetShaderPath() + fragPath, GetShaderPath() + vertPath));
}

Shader *Renderer::GetShader(CRef<str> name) {
  for (u32 i = 0; i < Get().shaders.Size(); i++) {
    if (name == Get().shaders[i].GetName()) {
      return &Get().shaders[i];
    }
  }

  THROW_ERROR(WARNING.Derived("", "Could not find shader with the name `" +
                                      name + "`!"));
  return nullptr;
}

SDL_GLContext *Renderer::GetGLContext() { return &Get().gl; }

void Renderer::SetShaderPath(CRef<str> path) {

  // if last character in string is not '/' then append '/' to the end. this is
  // because when loading the shader, it will prepend shaderPath to the file
  // given. Example: path: "assets/shaders", shaderPath = "assets/shaders/"
  if (path[path.length() - 1] != '/') {
    Get().shaderPath = path + "/";
    return;
  }

  Get().shaderPath = path;
}

str &Renderer::GetShaderPath() { return Get().shaderPath; }

void Renderer::SetCameraTransform(Transform *target) {
  Get().cameraTransform = target;
}

Transform *Renderer::GetCameraTransformPtr() { return Get().cameraTransform; }

void Renderer::SetCameraCullingAngle(f32 *angle) {
  Get().cameraCullingAngle = angle;
}

f32 Renderer::GetCameraCullingAngle() { return *Get().cameraCullingAngle; }

f32 *Renderer::GetCameraCullingAnglePtr() { return Get().cameraCullingAngle; }

void Renderer::SetCameraCullingDistance(f32 *value) {
  Get().cameraCullingDistance = value;
}

f32 Renderer::GetCameraCullingDistance() {
  return *Get().cameraCullingDistance;
}

f32 *Renderer::GetCameraCullingDistancePtr() {
  return Get().cameraCullingDistance;
}

void Renderer::SetCameraView(Mat4 *value) { Get().cameraView = value; }

Mat4 *Renderer::GetCameraViewPtr() { return Get().cameraView; }

void Renderer::SetCameraProjection(Mat4 *value) {
  Get().cameraProjection = value;
}

Mat4 *Renderer::GetCameraProjectionPtr() { return Get().cameraProjection; }