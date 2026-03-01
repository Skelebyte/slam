#include "engine.hpp"

using namespace slam;
using namespace slam::evt;
using namespace slam::err;

void Engine::Init() {
  if (initialized) {
    THROW_ERROR(WARNING.Derived("", "Engine is already initialized!"));
    return;
  }

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    THROW_ERROR(FATAL.Derived("", "SDL failed to initialize! SDL error: " +
                                      sString(SDL_GetError())));
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 5);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  initialized = true;
}

void Engine::Shutdown() { EventSystem::Get().on_quit.Invoke(); }
