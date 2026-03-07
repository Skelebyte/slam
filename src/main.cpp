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
#include "../slam/scn/component.hpp"
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

sI32 main() {
  Engine::Get().Init(144);
  Window window = Window("Hi mum!");
  window.appendFpsToTitle = true;
  Renderer::Get().Init(&window);

  //   ErrorSystem::Get().silenceWarnings = true;

  Keybind toggleWireframe = Keybind(Keycode::F1);

  Entity player = Entity();

  Camera cam = Camera();
  cam.transform.position.y = 1;
  cam.MakeChildOf(&player);

  MeshRenderer ground = MeshRenderer("assets/models/cube.fbx");
  ground.transform.position = Vec3(0, -2, 0);
  ground.transform.scale = Vec3(10, 1, 10);
  ground.material.diffuse =
      Texture("assets/textures/demo/ground.png", slam::gfx::TF_LINEAR);

  MeshRenderer cube = MeshRenderer("assets/models/cube.fbx");
  cube.transform.position = Vec3(4, 0, -3);

  MeshRenderer tree = MeshRenderer("assets/models/TreePodium.fbx");
  tree.material.diffuse = Texture("assets/textures/TreePodium.png", TF_NEAREST);
  tree.transform.position.y = -1.0f;

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);
  InputAxis rotX = InputAxis(Keycode::U_ARROW, Keycode::D_ARROW);

  Line line = Line(&cam, Vec3(0, 1, 0), Vec3(4, 0.5, -3));

  sF32 r = 123;
  sF32 g = 21;
  sF32 b = 200;

  while (window.IsRunning()) {
    Engine::Get().BeginFrame();

    window.Update();
    // window.SetTitle(std::to_string(Engine::Get().GetFps()));

    if (Input::Get().GetKeyOnce(&toggleWireframe)) {
      Renderer::Get().ToggleWireframe();
    }

    Vec3 velocity = Vec3();
    velocity +=
        player.transform.Right() * ((sF32)Input::Get().GetAxis(horizontal));
    velocity +=
        player.transform.Forward() * -((sF32)Input::Get().GetAxis(vertical));

    player.transform.position +=
        Mathf::Normalized(velocity) * Time::DeltaTime();

    player.transform.rotation.y +=
        Mathf::ToDegrees((sF32)Input::Get().GetAxis(rotY)) * Time::DeltaTime();

    cam.transform.rotation.x +=
        Mathf::ToDegrees((sF32)Input::Get().GetAxis(rotX)) * Time::DeltaTime();
    cam.transform.rotation.x = Mathf::Clamp(cam.transform.rotation.x, -89, 89);
    r = Mathf::Wrap(r + 0.5f * Time::DeltaTime(), 0.0f, 1.0f);
    g = Mathf::Wrap(g + 0.25f * Time::DeltaTime(), 0.0f, 1.0f);
    b = Mathf::Wrap(b + 0.175f * Time::DeltaTime(), 0.0f, 1.0f);

    cube.material.color = RGB(r, g, b);

    player.Update();
    cam.Update();
    cube.Update();
    tree.Update();
    ground.Update();

    glClearColor(0.05f, 0.1f, 0.05f, 1.0f);

    window.SwapAndClear();

    Engine::Get().EndFrame();
  }

  player.Destroy();
  cam.Destroy();
  cube.Destroy();

  /*
    FIXME:
    calling Renderer::Get().Shutdown() down after window.Destroy causes
    segfault (???)
  */

  Renderer::Get().Shutdown();
  window.Destroy();
  Engine::Get().Shutdown();
}