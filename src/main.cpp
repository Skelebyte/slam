#include "../slam/dpy/window.hpp"
#include "../slam/engine.hpp"
#include "../slam/entities/camera.hpp"
#include "../slam/entities/line.hpp"
#include "../slam/entities/mesh_renderer.hpp"
#include "../slam/err/err_sys.hpp"
#include "../slam/evt/evt_sys.hpp"
#include "../slam/gfx/ebo.hpp"
#include "../slam/gfx/renderer.hpp"
#include "../slam/gfx/shader.hpp"
#include "../slam/gfx/texture.hpp"
#include "../slam/gfx/vao.hpp"
#include "../slam/gfx/vbo.hpp"
#include "../slam/input/input.hpp"
#include "../slam/math/mathf.hpp"
#include "../slam/res/mesh.hpp"
#include "../slam/scn/entity.hpp"
#include "../slam/time.hpp"

using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam::input;
using namespace slam::entities;
using namespace slam;

i32 main() {
  Engine::Get().Init(144);
  Window window = Window("Hi mum!");
  window.appendFpsToTitle = true;
  Renderer::Get().Init(&window);

  //   ErrorSystem::Get().silenceWarnings = true;
  ErrorSystem::Get().enablePopupOnErrors =
      ErrorSeverity::ES_ERROR | ErrorSeverity::ES_FATAL;

  Keybind toggleWireframe = Keybind(Keycode::F1);
  Keybind toggleIcons = Keybind(Keycode::F2);

  Entity player = Entity();
  // player.transform.position.y = -5;

  Camera cam = Camera();
  cam.transform.position.y = 1;
  cam.MakeChildOf(&player);

  MeshRenderer cube = MeshRenderer("assets/models/TreePodium.fbx");
  cube.material.diffuse = Texture("assets/textures/TreePodium.png", NEAREST);
  cube.transform.position = Vec3(0, 0, 0);
  cube.material.fog = false;

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);
  InputAxis rotX = InputAxis(Keycode::U_ARROW, Keycode::D_ARROW);

  f32 r = 123;
  f32 g = 21;
  f32 b = 200;

  // Entity random = Entity();
  // random.transform.position.y = 10;

  Keybind spawn = Keybind(Keycode::SPACE);

  Keybind zoom = Keybind(Keycode::RMB);

  f32 defaultZoom = 75.0f;
  f32 fullZoom = 5.0f;

  MeshRenderer lightCube = MeshRenderer("assets/models/cube.fbx");
  lightCube.material.unlit = true;
  lightCube.transform.position = Vec3(1, 1, -1);
  lightCube.transform.scale = Vec3(0.5);

  // player.drawDebugIcon = true;

  while (window.IsRunning()) {
    Engine::Get().BeginFrame();
    Engine::Get().drawEntityIcons = true;

    window.Update();
    // window.SetTitle(std::to_string(Engine::Get().GetFps()));

    if (Input::Get().GetKeyOnce(&toggleWireframe)) {
      Renderer::Get().ToggleWireframe();
    }
    if (Input::Get().GetKeyOnce(&toggleIcons)) {
      Engine::Get().drawEntityIcons = !Engine::Get().drawEntityIcons;
    }

    if (Input::Get().GetKey(&zoom)) {
      cam.fov = Mathf::Lerp(cam.fov, fullZoom, 5.0f * Time::DeltaTime());
    } else {
      cam.fov = Mathf::Lerp(cam.fov, defaultZoom, 5.0f * Time::DeltaTime());
    }

    Vec3 velocity = Vec3();
    velocity +=
        player.transform.Right() * ((f32)Input::Get().GetAxis(horizontal));
    velocity +=
        player.transform.Forward() * -((f32)Input::Get().GetAxis(vertical));

    player.transform.position +=
        Mathf::Normalized(velocity) * 5.0f * Time::DeltaTime();

    player.transform.rotation.y +=
        Mathf::ToDegrees((f32)Input::Get().GetAxis(rotY)) * Time::DeltaTime();

    cam.transform.rotation.x +=
        Mathf::ToDegrees((f32)Input::Get().GetAxis(rotX)) * Time::DeltaTime();
    cam.transform.rotation.x = Mathf::Clamp(cam.transform.rotation.x, -89, 89);
    r = Mathf::Wrap(r + 0.5f * Time::DeltaTime(), 0.0f, 1.0f);
    g = Mathf::Wrap(g + 0.25f * Time::DeltaTime(), 0.0f, 1.0f);
    b = Mathf::Wrap(b + 0.175f * Time::DeltaTime(), 0.0f, 1.0f);

    // cube.material.color = RGB(r, g, b);

    cube.transform.rotation.x += 45.0f * Time::DeltaTime();
    cube.transform.rotation.y += 45.0f * Time::DeltaTime();
    cube.transform.rotation.z += 45.0f * Time::DeltaTime();

    if (Input::Get().GetKeyOnce(&spawn)) {

      MeshRenderer *instance = new MeshRenderer("assets/models/cube.fbx");
      instance->transform.position = cam.transform.GetInheritedPosition() +
                                     cam.transform.InheritedForward() * 2.0f;
      instance->material.diffuse = Texture("assets/textures/demo/s.png");
      instance->material.unlit = true;
    }
    EntityManager::Get().UpdateAll();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    window.SwapAndClear();

    Engine::Get().EndFrame();
    // window.Stop();
  }

  EntityManager::Get().DestroyAll();

  /*
    FIXME:
    calling Renderer::Get().Shutdown() down after window.Destroy causes
    segfault (???)
  */

  Renderer::Get().Shutdown();
  window.Destroy();
  Engine::Get().Shutdown();
}