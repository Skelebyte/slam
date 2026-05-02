#include "engine.hpp"
#include "common.hpp"
#include "input/input.hpp"
#include "time.hpp"
#include <SDL3/SDL_timer.h>

using namespace slam;
using namespace slam::evt;
using namespace slam::err;
using namespace slam::input;

void Engine::Init(u16 fps) {
  if (Get().initialized) {
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

  Get().last = SDL_GetTicks() / 1000.0f;

  SetTargetFps(fps);

  Get().initialized = true;
}

void Engine::Shutdown() { EventSystem::Get().OnQuit.Invoke(); }

void Engine::BeginFrame() {

  Input::INTERNALResetMousePositionCache();

  Get().isProcessFrame = false;
  Get().first = SDL_GetTicks() / 1000.0f;

  Get().deltaTime = Get().first - Get().last;

  Get().last = Get().first;

  Get().processedDeltaTime += Get().deltaTime;
  Get().frameTime += Get().deltaTime;

  while (Get().processedDeltaTime >= Get().targetFps) {
    Get().processedDeltaTime -= Get().targetFps;
    Get().isProcessFrame = true;

    if (Get().frameTime >= 1.0f) {
      Get().frameTime = 0.0f;
      Get().fps = Get().frames;
      Get().frames = 0;
    }
  }

  if (Get().isProcessFrame) {
    Get().frames++;
  }
}

void Engine::EndFrame() {
  if (!Get().isProcessFrame) {
  }

  SetDrawnEntities(0);
}

bool Engine::IsProcessFrame() { return Get().isProcessFrame; }

void Engine::SetTargetFps(u16 fps) {

  LOG("fps: " << fps);

  if (fps > 999) {
    Get().targetFps = 1.0f / 999.0f;
  } else {
    Get().targetFps = 1.0f / (f32)fps;
  }
  LOG("tfps: " << Get().targetFps);
}

u32 Engine::GetFps() { return Get().fps; }

void Engine::SetWindow(dpy::Window *window) { Get().window = window; }

dpy::Window *Engine::GetWindow() { return Get().window; }

void Engine::SetDrawEntityIcons(bool value) { Get().drawEntityIcons = true; }

bool Engine::GetDrawEntityIcons() { return Get().drawEntityIcons; }

f32 Engine::GetDeltaTime() { return Get().deltaTime; }

void Engine::SetTimeScale(f32 value) { Get().timeScale = value; }
f32 Engine::GetTimeScale() { return Get().timeScale; }

void Engine::SetDrawnEntities(u32 value) { Get().drawnEntities = value; }

u32 Engine::GetDrawnEntities() { return Get().drawnEntities; }

str Engine::GetVersion() { return "0.1.0-alpha"; }
