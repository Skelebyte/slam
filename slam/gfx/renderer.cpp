#include "renderer.hpp"

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
                              sString(SDL_GetError())));
    return;
  }

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    THROW_ERROR(FATAL.Derived("", "Failed to initialize glad! remind me to "
                                  "come back here add a get error func"));
  }

  // sString fragContent = File::Read(fragShaderPath);
  // sString vertContent = File::Read(vertShaderPath);

  // if (fragContent.empty()) {
  //   THROW_ERROR(FATAL.Derived("", "Failed to read fragment shader " +
  //                                     fragShaderPath + "."));
  // }

  // if (vertContent.empty()) {
  //   THROW_ERROR(FATAL.Derived("", "Failed to read vertex shader " +
  //                                     vertShaderPath + "."));
  // }

  // const char *ccFrag = fragContent.c_str();
  // const char *ccVert = vertContent.c_str();

  // sUint frag = glCreateShader(GL_FRAGMENT_SHADER);

  initialized = true;
}

void Renderer::Shutdown() {
  SDL_GL_DestroyContext(gl);
  initialized = false;
}
