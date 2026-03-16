#include "../slam/dpy/window.hpp"
#include "../slam/engine.hpp"
#include "../slam/entities/camera.hpp"
#include "../slam/entities/line.hpp"
#include "../slam/entities/mesh_renderer.hpp"
#include "../slam/err/err_sys.hpp"
#include "../slam/evt/evt_sys.hpp"
#include "../slam/ext/imgui/imgui.h"
#include "../slam/ext/imgui/imgui_impl_opengl3.h"
#include "../slam/ext/imgui/imgui_impl_sdl3.h"
#include "../slam/gfx/ebo.hpp"
#include "../slam/gfx/renderer.hpp"
#include "../slam/gfx/shader.hpp"
#include "../slam/gfx/texture.hpp"
#include "../slam/gfx/vao.hpp"
#include "../slam/gfx/vbo.hpp"
#include "../slam/input/input.hpp"
#include "../slam/math/mathf.hpp"
#include "../slam/phys/physics.hpp"
#include "../slam/res/mesh.hpp"
#include "../slam/scn/entity.hpp"
#include "../slam/time.hpp"
#include <reactphysics3d/reactphysics3d.h>

using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam::input;
using namespace slam::entities;
using namespace slam::phys;
using namespace slam;

i32 main() {
  Engine::Get().Init(999);
  Window window = Window("Hi mum!", 800, 600, true, true);
  window.appendFpsToTitle = true;
  Renderer::Get().Init(&window);
  Physics::Init();

  Keybind toggleWireframe = Keybind(Keycode::F1);
  Keybind toggleIcons = Keybind(Keycode::F2);

  Entity player = Entity();
  player.transform.position.z = 5;

  Camera cam = Camera();
  cam.transform.position.y = 1;
  cam.MakeChildOf(&player);

  MeshRenderer cube = MeshRenderer("assets/models/cube.fbx");
  cube.transform.position = Vec3(0, -1, 0);
  cube.transform.scale = Vec3(100, 1, 100);
  cube.material.color = RGB(0, 0.1, 0);
  cube.allowViewCulling = false;

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);

  // Entity random = Entity();
  // random.transform.position.y = 10;

  Keybind spawn = Keybind(Keycode::SPACE);

  Keybind zoom = Keybind(Keycode::RMB);

  f32 defaultZoom = 75.0f;
  f32 fullZoom = 5.0f;

  Keybind toggleFullscreen = Keybind(Keycode::F11);

  MeshRenderer tree = MeshRenderer("assets/models/TreePodium.fbx");
  tree.material.diffuse = Texture("assets/textures/TreePodium.png");
  tree.transform.position = Vec3(24, -0.5, -20);

  MeshRenderer colorCube = MeshRenderer("assets/models/cube.fbx");
  colorCube.transform.position.y = 10;
  f32 r = 0.0f;
  f32 g = 0.0f;
  f32 b = 0.0f;

  IMGUI_CHECKVERSION();
  ImGui::CreateContext();
  ImGuiIO &io = ImGui::GetIO();

  ImGui::StyleColorsDark();

  ImGui_ImplSDL3_InitForOpenGL(window.GetSDLWindow(), Renderer::GetGLContext());
  ImGui_ImplOpenGL3_Init("#version 330");

  io.Fonts->AddFontFromFileTTF("assets/fonts/RobotoMono.ttf", 18);

  Rigidbody rb = Rigidbody();
  rb.transform.position = Vec3(0, 5, -5);
  rb.Sync();

  MeshRenderer physMesh = MeshRenderer("assets/models/sphere.fbx");
  physMesh.MakeChildOf(&rb);
  physMesh.material.color = RGB(1, 0, 0);

  while (window.IsRunning()) {
    Engine::Get().BeginFrame();
    Engine::Get().drawEntityIcons = true;

    window.Update();

    if (Input::GetKeyOnce(&toggleWireframe)) {
      Renderer::Get().ToggleWireframe();
    }
    if (Input::GetKeyOnce(&toggleIcons)) {
      Engine::Get().drawEntityIcons = !Engine::Get().drawEntityIcons;
    }
    if (Input::GetKeyOnce(&toggleFullscreen)) {
      window.ToggleFullscreen();
    }

    if (Input::GetKey(&zoom)) {
      cam.fov = Mathf::Lerp(cam.fov, fullZoom, 5.0f * Time::DeltaTime());
    } else {
      cam.fov = Mathf::Lerp(cam.fov, defaultZoom, 5.0f * Time::DeltaTime());
    }

    Vec3 velocity = Vec3();
    velocity += player.transform.Right() * ((f32)Input::GetAxis(horizontal));
    velocity += player.transform.Forward() * -((f32)Input::GetAxis(vertical));

    player.transform.position +=
        Mathf::Normalized(velocity) * 5.0f * Time::DeltaTime();

    r = Mathf::Wrap(r + Mathf::Random(100) / 100.0f * Time::DeltaTime(), 0.0f,
                    1.0f);
    g = Mathf::Wrap(g + Mathf::Random(100) / 100.0f * Time::DeltaTime(), 0.0f,
                    1.0f);
    b = Mathf::Wrap(b + Mathf::Random(100) / 100.0f * Time::DeltaTime(), 0.0f,
                    1.0f);

    colorCube.material.color = RGB(r, g, b);

    if (Input::GetKeyOnce(&spawn)) {
      // SpawnBalls(cam.transform.GetInheritedPosition());
    }

    // LOG(Mathf::ToString(rb.transform.position));
    EntityManager::Get().UpdateAll();
    Physics::Update();

    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    io.DisplaySize =
        ImVec2(window.GetViewportSize().x, window.GetViewportSize().y);
    ImGui::SetNextWindowPos(
        ImVec2(window.GetViewportPosition().x, window.GetViewportPosition().y));
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin("viewport", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
    ImGui::Text("FPS: %d", Engine::Get().GetFps());
    ImGui::Text("Delta Time: %f", Time::DeltaTime());
    ImGui::Text("Entities: %d", EntityManager::GetNumberOfEntities());
    ImGui::Text("Bodies: %d", Physics::GetNumberOfBodies());
    ImGui::DragFloat3("Player Position",
                      glm::value_ptr(player.transform.position));
    ImGui::DragFloat("Culling Angle", &cam.cullingAngle, 0.05f, -1.0f, 1.0f);
    ImGui::DragFloat("Culling Distance", &cam.cullingDistance, 0.5f, 0.0f,
                     100.0f);
    ImGui::Text("Press SPACE to spawn 10 spheres in the sky");
    if (ImGui::Button("Quit")) {
      window.Stop();
    }
    ImGui::End();

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
  ImGui_ImplOpenGL3_Shutdown();
  ImGui_ImplSDL3_Shutdown();
  ImGui::DestroyContext();
  Renderer::Get().Shutdown();
  window.Destroy();
  Engine::Get().Shutdown();
}