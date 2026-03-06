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

  ErrorSystem::Get().silenceWarnings = true;

  Keybind toggleWireframe = Keybind(Keycode::F1);

  Entity player = Entity();

  Camera cam = Camera();
  cam.MakeChildOf(&player);

  MeshRenderer cube = MeshRenderer("assets/models/cube.fbx");
  cube.transform.position = Vec3(0, -2, 0);
  cube.transform.scale = Vec3(10, 1, 10);
  cube.texture =
      Texture("assets/textures/demo/ground.png", slam::gfx::TF_LINEAR);

  MeshRenderer slime = MeshRenderer("assets/models/cube.fbx");
  slime.texture =
      Texture("assets/textures/demo/damn.png", TextureFilter::TF_NEAREST);
  slime.transform.scale = Vec3(0.5f);
  slime.transform.position.z = -5;
  slime.MakeChildOf(&cam);

  MeshRenderer slime2 = MeshRenderer("assets/models/cube.fbx");
  slime2.texture =
      Texture("assets/textures/demo/frank.png", TextureFilter::TF_NEAREST);
  slime2.transform.position.z = -5;
  slime2.transform.scale = Vec3(2);

  slime2.MakeChildOf(&slime);

  MeshRenderer gun = MeshRenderer("assets/models/BasicGun.fbx");
  gun.texture = Texture("assets/textures/texture.png");
  gun.transform.position.x += .5;
  gun.transform.position.y -= 0.2;
  gun.transform.position.z -= .5;
  gun.transform.scale = Vec3(1.0f);
  gun.MakeChildOf(&cam);

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);
  InputAxis rotX = InputAxis(Keycode::U_ARROW, Keycode::D_ARROW);

  Line line = Line(&cam, Vec3(0, 1, 0), Vec3(4, 0.5, -3));

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
    slime.transform.rotation.x += 1.0f * Engine::Get().deltaTime;
    slime.transform.rotation.y += 1.0f * Engine::Get().deltaTime;
    slime.transform.rotation.z += 1.0f * Engine::Get().deltaTime;

    cam.Update();
    cube.Update();
    slime.Update();
    slime2.Update();
    gun.Update();

    line.Update();

    glClearColor(0.05f, 0.1f, 0.05f, 1.0f);

    window.SwapAndClear();

    Engine::Get().EndFrame();
  }

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