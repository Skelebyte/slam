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

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);
  InputAxis rotX = InputAxis(Keycode::U_ARROW, Keycode::D_ARROW);

  Line line = Line(&cam, Vec3(0, 1, 0), Vec3(4, 0.5, -3));

  sU32 r = 123;
  sU32 g = 21;
  sU32 b = 200;

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
        Mathf::Normalized(velocity) * Engine::Get().deltaTime;

    player.transform.rotation.y +=
        Mathf::ToDegrees((sF32)Input::Get().GetAxis(rotY)) *
        Engine::Get().deltaTime;

    cam.transform.rotation.x +=
        Mathf::ToDegrees((sF32)Input::Get().GetAxis(rotX)) *
        Engine::Get().deltaTime;
    cam.transform.rotation.x = Mathf::Clamp(cam.transform.rotation.x, -89, 89);
    r = Mathf::Wrap(r + 10, 0, 255);
    g = Mathf::Wrap(g + 5, 0, 255);
    b = Mathf::Wrap(b + 1, 0, 255);

    cube.material.color = ToRGB(RGB255(r, g, b));

    player.Update();
    cam.Update();
    cube.Update();
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