#include "window.hpp"
#include "../engine.hpp"
#include <SDL3/SDL_messagebox.h>
#include <SDL3/SDL_video.h>

using namespace slam;
using namespace slam::dpy;
using namespace slam::evt;
using namespace slam::err;
using namespace slam::math;

Window::Window(const str &name, u32 w, u32 h, bool resizable, bool fullscreen) {
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
                                      str(SDL_GetError())));
    return;
  }

  running = true;

  EventSystem::Get().OnError += dpy::ErrorWindow;

  Engine::Get().window = this;

  this->title = name;
  this->fullscreen = fullscreen;
}

bool Window::IsRunning() const { return running; }

void Window::Destroy() {
  DESTROY();

  SDL_DestroyWindow(sdlWindow);

  Engine::Get().window = nullptr;
}

void Window::PopupWindow(const str &title, const str &message,
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
    ImGui_ImplSDL3_ProcessEvent(&sdlEvent);
    if (sdlEvent.type == SDL_EVENT_QUIT) {
      this->Stop();
    }
  }

  Vec2 dimensions = this->GetDimensions();

  f32 windowAspect = (f32)dimensions.x / dimensions.y;
  f32 gameAspect = (f32)1920 / 1080;

  this->pillarboxed = false;
  this->letterboxed = false;

  if (windowAspect > gameAspect) {
    this->viewportSize.x = (i32)(dimensions.y * gameAspect);
    this->viewportSize.y = dimensions.y;

    this->viewportPosition.x = (dimensions.x - this->viewportSize.x) / 2;
    this->viewportPosition.y = 0;
    this->pillarboxed = true;
  } else {
    this->viewportSize.x = dimensions.x;
    this->viewportSize.y = (i32)(dimensions.x / gameAspect);

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

  if (appendFpsToTitle) {
    SetTitle(title + " (" + std::to_string(Engine::Get().GetFps()) + " fps)");
  }

  ImGui_ImplOpenGL3_NewFrame();
  ImGui_ImplSDL3_NewFrame();
  ImGui::NewFrame();
}

void Window::SwapAndClear() {
  IS_DESTROYED();

  ImGui::Render();
  ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

  if (!Engine::Get().IsProcessFrame()) {
    return;
  }

  if (SDL_GL_SwapWindow(this->sdlWindow) == false) {
    THROW_ERROR(FATAL.Derived("", "SDL failed to swap buffers. SDL error: " +
                                      str(SDL_GetError())));
  }

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

Vec2 Window::GetDimensions() {
  IS_DESTROYED(Vec2());

  i32 x;
  i32 y;
  Vec2 dimensions;

  if (SDL_GetWindowSize(this->sdlWindow, &x, &y) == false) {
    THROW_ERROR(ERROR.Derived("", "SDL failed to get window size! SDL error: " +
                                      str(SDL_GetError())));
    dimensions.x = 0;
    dimensions.y = 0;
  } else {
    dimensions.x = x;
    dimensions.y = y;
  }

  return dimensions;
}

void Window::Stop() {
  IS_DESTROYED();

  running = false;
}

Vec2 Window::GetViewportPosition() const {
  IS_DESTROYED(Vec2());

  return viewportPosition;
}

Vec2 Window::GetViewportSize() const {
  IS_DESTROYED(Vec2());

  return viewportSize;
}

f32 Window::GetViewportAspect() const {
  IS_DESTROYED(0.0f);

  return (f32)this->viewportSize.x / (f32)this->viewportSize.y;
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

void Window::SetTitle(const str &title) {
  SDL_SetWindowTitle(sdlWindow, title.c_str());
}

void Window::ToggleFullscreen() {
  fullscreen = !fullscreen;

  SDL_SetWindowFullscreen(sdlWindow, fullscreen);
}