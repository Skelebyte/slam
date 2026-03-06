#include "engine.hpp"
#include <SDL3/SDL_timer.h>

using namespace slam;
using namespace slam::evt;
using namespace slam::err;

void Engine::Init(sU32 fps) {
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

  last = SDL_GetTicks() / 1000.0f;

  SetTargetFps(fps);
}

void Engine::Shutdown() { EventSystem::Get().on_quit.Invoke(); }

void Engine::BeginFrame() {
  isDrawFrame = false;
  first = SDL_GetTicks() / 1000.0f;

  deltaTime = first - last;

  last = first;

  processedDeltaTime += deltaTime;
  frameTime += deltaTime;

  while (processedDeltaTime >= targetFps) {
    processedDeltaTime -= targetFps;
    isDrawFrame = true;

    if (frameTime >= 1.0f) {
      frameTime = 0.0f;
      fps = frames;
      frames = 0;
    }
  }

  if (isDrawFrame) {
    frames++;
  }
}

void Engine::EndFrame() {}

bool Engine::IsDrawFrame() const { return isDrawFrame; }

void Engine::SetTargetFps(sU32 fps) {

  LOG("fps: " << fps);

  targetFps = 1.0f / (sF32)fps;
  LOG("tfps: " << targetFps);
}

sU32 Engine::GetFps() const { return fps; }