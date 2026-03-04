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
                              sString(SDL_GetError())));
    return;
  }

  SDL_GL_MakeCurrent(window->GetSDLWindow(), gl);

  if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress)) {
    THROW_ERROR(FATAL.Derived("", "Failed to initialize glad! remind me to "
                                  "come back here add a get_error func"));
  }

  glEnable(GL_DEPTH_TEST);

  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

  initialized = true;
}

void Renderer::Shutdown() {
  SDL_GL_DestroyContext(gl);
  initialized = false;
}
