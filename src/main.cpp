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

  Camera cam = Camera();
  cam.transform.position.y = 1;
  cam.MakeChildOf(&player);

  Entity ground = Entity();
  ground.transform.position = Vec3(0, -2, 0);
  ground.transform.scale = Vec3(100, 1, 100);

  MeshRenderer groundMesh = MeshRenderer("assets/models/cube.fbx");
  groundMesh.MakeChildOf(&ground);
  groundMesh.material.diffuse =
      Texture("assets/textures/demo/ground.png", TextureFilter::NEAREST);

  MeshRenderer cube = MeshRenderer("assets/models/cube.fbx");
  cube.transform.position = Vec3(4, 0, -3);

  MeshRenderer tree = MeshRenderer("assets/models/TreePodium.fbx");
  tree.material.diffuse = Texture("assets/textures/TreePodium.png", LINEAR);
  tree.transform.position.y = -1.5f;

  MeshRenderer skybox = MeshRenderer("assets/models/cube.fbx");
  skybox.transform.scale = Vec3(100);
  skybox.material.color = ToRGB(RGB255(21, 27, 31));
  skybox.material.faceCulling = FaceCullingStyle::FRONT;
  skybox.material.fog = false;
  skybox.material.unlit = true;

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);
  InputAxis rotX = InputAxis(Keycode::U_ARROW, Keycode::D_ARROW);

  Line line = Line(Vec3(0, 1, 0), Vec3(4, 0.5, -3));

  f32 r = 123;
  f32 g = 21;
  f32 b = 200;

  // Entity random = Entity();
  // random.transform.position.y = 10;

  Keybind spawn = Keybind(Keycode::SPACE);

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

    cube.material.color = RGB(r, g, b);

    // ground.transform.rotation.x += 1.0f * Time::DeltaTime();

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