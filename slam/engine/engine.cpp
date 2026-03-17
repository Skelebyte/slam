#include "engine.hpp"
#include <SDL3/SDL_timer.h>

using namespace slam;
using namespace slam::evt;
using namespace slam::err;

void Engine::Init(u32 fps) {
  if (initialized) {
    THROW_ERROR(WARNING.Derived("", "Engine is already initialized!"));
    return;
  }

  if (SDL_Init(SDL_INIT_VIDEO) == false) {
    THROW_ERROR(FATAL.Derived("", "SDL failed to initialize! SDL error: " +
                                      str(SDL_GetError())));
    return;
  }

  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
  SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

  initialized = true;

  last = SDL_GetTicks() / 1000.0f;

  SetTargetFps(fps);
}

void Engine::Shutdown() { EventSystem::Get().OnQuit.Invoke(); }

void Engine::BeginFrame() {
  isProcessFrame = false;
  first = SDL_GetTicks() / 1000.0f;

  deltaTime = first - last;

  last = first;

  processedDeltaTime += deltaTime;
  frameTime += deltaTime;

  while (processedDeltaTime >= targetFps) {
    processedDeltaTime -= targetFps;
    isProcessFrame = true;

    if (frameTime >= 1.0f) {
      frameTime = 0.0f;
      fps = frames;
      frames = 0;
    }
  }

  if (isProcessFrame) {
    frames++;
  }
}

void Engine::EndFrame() {
  if (!isProcessFrame) {
    SDL_Delay(10);
  }
}

bool Engine::IsProcessFrame() { return Get().isProcessFrame; }

void Engine::SetTargetFps(u32 fps) {

  LOG("fps: " << fps);

  targetFps = 1.0f / (f32)fps;
  LOG("tfps: " << targetFps);
}

u32 Engine::GetFps() const { return fps; }