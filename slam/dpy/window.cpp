#include "window.hpp"
#include "../engine.hpp"
#include <SDL3/SDL_messagebox.h>

using namespace slam;
using namespace slam::dpy;
using namespace slam::evt;
using namespace slam::err;
using namespace slam::math;

Window::Window(const sString &name, sUint w, sUint h, bool resizable,
               bool fullscreen) {
  if (Engine::Get().IsInitialized() == false) {
    THROW_ERROR(
        FATAL.Derived("", "Engine is not initialized! Please initialize with "
                          "`slam::Engine::Get().Init()"));
    return;
  }

  SDL_WindowFlags flags = SDL_WINDOW_OPENGL;

  if (resizable)
    flags |= SDL_WINDOW_RESIZABLE;
  if (fullscreen)
    flags |= SDL_WINDOW_FULLSCREEN;

  sdlWindow = SDL_CreateWindow(name.c_str(), w, h, flags);
  if (sdlWindow == nullptr) {
    THROW_ERROR(FATAL.Derived("", "SDL failed to create window! SDL error: " +
                                      sString(SDL_GetError())));
    return;
  }

  running = true;

  EventSystem::Get().on_error += dpy::ErrorWindow;

  Engine::Get().window = this;
}

bool Window::IsRunning() const { return running; }

void Window::Destroy() {
  DESTROY();

  SDL_DestroyWindow(sdlWindow);

  Engine::Get().window = nullptr;
}

void Window::PopupWindow(const sString &title, const sString &message,
                         bool isErrorWindow) {
  if (isErrorWindow) {
    switch (ErrorSystem::Get().lastError->GetSeverity()) {
    case err::ES_MSG:
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, title.c_str(),
                               message.c_str(), NULL);
      break;
    case err::ES_WARNING:
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_WARNING, title.c_str(),
                               message.c_str(), NULL);
      break;
    default:
      SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, title.c_str(),
                               message.c_str(), NULL);
      break;
    }
    return;
  }
}

SDL_Window *Window::GetSDLWindow() const { return sdlWindow; }

void Window::Update() {
  IS_DESTROYED();

  SDL_Event sdlEvent;

  while (SDL_PollEvent(&sdlEvent)) {
    if (sdlEvent.type == SDL_EVENT_QUIT) {
      this->Stop();
    }
  }

  Vec2i dimensions = this->GetDimensions();

  float windowAspect = (float)dimensions.x / dimensions.y;
  float gameAspect = (float)1920 / 1080;

  this->pillarboxed = false;
  this->letterboxed = false;

  if (windowAspect > gameAspect) {
    this->viewportSize.x = (int)(dimensions.y * gameAspect);
    this->viewportSize.y = dimensions.y;

    this->viewportPosition.x = (dimensions.x - this->viewportSize.x) / 2;
    this->viewportPosition.y = 0;
    this->pillarboxed = true;
  } else {
    this->viewportSize.x = dimensions.x;
    this->viewportSize.y = (int)(dimensions.x / gameAspect);

    this->viewportPosition.x = 0;
    this->viewportPosition.y = (dimensions.y - this->viewportSize.y) / 2;
    this->letterboxed = true;
  }

  glClear(GL_COLOR_BUFFER_BIT |
          GL_DEPTH_BUFFER_BIT); // MOVE TO RENDERER/gfx (?)
  THROW_ERROR_GL(FATAL.Derived("GL_CLEAR_FAIL"));

  glViewport(this->viewportPosition.x, this->viewportPosition.y,
             this->viewportSize.x, this->viewportSize.y);
  THROW_ERROR_GL(FATAL.Derived("GL_VIEWPORT_FAIL"));
}

void Window::SwapAndClear() {
  IS_DESTROYED();

  if (SDL_GL_SwapWindow(this->sdlWindow) == false) {
    THROW_ERROR(FATAL.Derived("", "SDL failed to swap buffers. SDL error: " +
                                      sString(SDL_GetError())));
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Vec2i Window::GetDimensions() {
  IS_DESTROYED(Vec2i());

  Vec2i dimensions;

  if (SDL_GetWindowSize(this->sdlWindow, &dimensions.x, &dimensions.y) ==
      false) {
    THROW_ERROR(ERROR.Derived("", "SDL failed to get window size! SDL error: " +
                                      sString(SDL_GetError())));
    dimensions.x = 0;
    dimensions.y = 0;
  }

  return dimensions;
}

void Window::Stop() {
  IS_DESTROYED();

  running = false;
}

Vec2i Window::GetViewportPosition() const {
  IS_DESTROYED(Vec2i());

  return viewportPosition;
}

Vec2i Window::GetViewportSize() const {
  IS_DESTROYED(Vec2i());

  return viewportSize;
}

float Window::GetViewportAspect() const {
  IS_DESTROYED(0.0f);

  return (float)this->viewportSize.x / (float)this->viewportSize.y;
}

void dpy::ErrorWindow() {
  if (ErrorSystem::Get().lastError == nullptr)
    return;

  if ((ErrorSystem::Get().lastError->GetSeverity() &
       ErrorSystem::Get().enablePopupOnErrors) == false)
    return;

  Engine::Get().window->PopupWindow(ErrorSystem::Get().lastError->GetName(),
                                    ErrorSystem::Get().lastError->GetDesc(),
                                    true);
}