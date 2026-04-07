#ifndef SLAM_SLAM_HPP
#define SLAM_SLAM_HPP

#include "engine/app.hpp"
#include "engine/audio/audio_listener.hpp"
#include "engine/audio/audio_manager.hpp"
#include "engine/audio/audio_player.hpp"
#include "engine/dpy/window.hpp"
#include "engine/engine.hpp"
#include "engine/entities/camera.hpp"
#include "engine/entities/line.hpp"
#include "engine/entities/mesh_renderer.hpp"
#include "engine/err/err_sys.hpp"
#include "engine/evt/evt_sys.hpp"
#include "engine/gfx/ebo.hpp"
#include "engine/gfx/renderer.hpp"
#include "engine/gfx/shader.hpp"
#include "engine/gfx/texture.hpp"
#include "engine/gfx/vao.hpp"
#include "engine/gfx/vbo.hpp"
#include "engine/input/input.hpp"
#include "engine/math/mathf.hpp"
#include "engine/res/mesh.hpp"
#include "engine/scn/entity.hpp"
#include "engine/time.hpp"
#include "engine/ui/button.hpp"
#include "engine/ui/element.hpp"
#include "engine/ui/text.hpp"
#include "engine/ui/ui_context.hpp"
#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_impl_opengl3.h"
#include "third_party/imgui/imgui_impl_sdl3.h"

#ifdef SLAM_USING_NAMESPACES
using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam::input;
using namespace slam::entities;
using namespace slam::ui;
using namespace slam::audio;
// using namespace slam::phys;
using namespace slam;
#endif

#ifdef SLAM_ENTRY_POINT

i32 main() {
  // Initialize everything
  slam::Engine::Init(999);
  str name = SLAM_ENTRY_POINT;
  if (name.empty()) {
    THROW_ERROR(ERROR.Derived(
        "",
        "You did not give SLAM_ENTRY_POINT a value! The window SLAM makes will "
        "default to \"SLAM\"\nExample: #define SLAM_ENTRY_POINT \"MyGame\""));
    name = "SLAM";
  }
  slam::dpy::Window window = slam::dpy::Window(name, 800, 600, true, false);
  window.appendFpsToTitle = true;
  slam::gfx::Renderer::Init(&window);
  slam::ui::UIContext::Init();
  slam::audio::AudioManager::Init();

  slam::App::Start();

  // Game loop. Can be stopped with Window::Stop()
  while (window.IsRunning()) {
    if (slam::gfx::Renderer::GetCameraTransformPtr() == nullptr) {
      THROW_ERROR(FATAL.Derived("", "There is no camera!"));
    }

    slam::Engine::BeginFrame();
    window.Update();

    slam::App::Update();

    slam::scn::EntityManager::UpdateAll();
    slam::ui::UIContext::Update();

    window.SwapAndClear();
    slam::Engine::EndFrame();
  }

  // Clean up
  slam::scn::EntityManager::DestroyAll();
  slam::ui::UIContext::Shutdown();
  slam::gfx::Renderer::Shutdown();
  window.Destroy();
  slam::Engine::Shutdown();
}

#endif

#endif