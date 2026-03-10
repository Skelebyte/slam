#include "renderer.hpp"
#include <SDL3/SDL_video.h>

using namespace slam;
using namespace slam::dpy;
using namespace slam::gfx;
using namespace slam::err;
using namespace slam::util;

void Renderer::Init(dpy::Window *window) {
  if (IsInitialized() == true) {
    THROW_ERROR(WARNING.Derived("", "Renderer is already initialized!"));
    return;
  }

  gl = SDL_GL_CreateContext(window->GetSDLWindow());
  if (gl == nullptr) {
    THROW_ERROR(
        FATAL.Derived("", "Create to create OpenGL context. SDL error: " +
                              str(SDL_GetError())));
    return;
  }

  SDL_GL_MakeCurrent(window->GetSDLWindow(), gl);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    THROW_ERROR(FATAL.Derived("", "Failed to initialize glad! remind me to "
                                  "come back here add a get_error func"));
  }

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  shaders = List<Shader>();

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

  GetShader("line")->AddUniform("view");
  GetShader("line")->AddUniform("projection");
  GetShader("line")->AddUniform("model");
  GetShader("line")->AddUniform("color");

  GetShader("billboard")->AddUniform("view");
  GetShader("billboard")->AddUniform("projection");
  GetShader("billboard")->AddUniform("model");
  GetShader("billboard")->AddUniform("diffuse_texture");

  initialized = true;
}

void Renderer::Shutdown() {
  SDL_GL_DestroyContext(gl);

  for (u32 i = 0; i < shaders.Size(); i++) {
    shaders[i].Destroy();
  }

  shaders.Clear();

  initialized = false;
}

void Renderer::ToggleWireframe() {
  wireframe = !wireframe;

  if (wireframe) {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  } else {
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  }
}

void Renderer::AddShader(const str &name, const str &fragPath,
                         const str &vertPath) {
  bool silence = ErrorSystem::Get().silenceWarnings;

  ErrorSystem::Get().silenceWarnings = true;
  Shader *temp = GetShader(name);
  ErrorSystem::Get().silenceWarnings = silence;
  if (temp != nullptr) {
    THROW_ERROR(WARNING.Derived("", "A shader with the name `" + name +
                                        "` already exists!"));
    return;
  }

  shaders.Add(Shader(name, shaderPath + fragPath, shaderPath + vertPath));
}

Shader *Renderer::GetShader(const str &name) {
  for (u32 i = 0; i < shaders.Size(); i++) {
    if (name == shaders[i].GetName()) {
      return &shaders[i];
    }
  }

  THROW_ERROR(WARNING.Derived("", "Could not find shader with the name `" +
                                      name + "`!"));
  return nullptr;
}