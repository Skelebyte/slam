#define SLAM_USING_NAMESPACES
#include "../slam/slam.hpp"

i32 main() {
  Engine::Get().Init(999);
  Window window = Window("Hi mum!", 800, 600, true, true);
  window.appendFpsToTitle = true;
  Renderer::Init(&window);
  UIContext::Init();
  AudioManager::Init();

  Keybind toggleWireframe = Keybind(Keycode::F1);
  Keybind toggleIcons = Keybind(Keycode::F2);

  Entity player = Entity();
  player.transform.position.z = 0;

  Camera cam = Camera();

  cam.transform.position.y = 1;
  cam.MakeChildOf(&player);

  AudioListener listener = AudioListener();
  // listener.transform.position = cam.transform.GetInheritedPosition();
  listener.MakeChildOf(&cam);

  AudioPlayer audio = AudioPlayer("assets/sounds/song.wav", true);

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

  // Keybind zoom = Keybind(Keycode::RMB);

  f32 defaultZoom = 75.0f;
  f32 fullZoom = 5.0f;

  Keybind toggleFullscreen = Keybind(Keycode::F11);

  MeshRenderer tree = MeshRenderer("assets/models/TreePodium.fbx");
  tree.material.diffuse =
      Texture("assets/textures/TreePodium.png", TextureFilter::LINEAR);
  tree.transform.position = Vec3(24, -0.5, -20);

  MeshRenderer colorCube = MeshRenderer("assets/models/cube.fbx");
  colorCube.transform.position.y = 10;
  f32 r = 0.0f;
  f32 g = 0.0f;
  f32 b = 0.0f;

  MeshRenderer physMesh = MeshRenderer("assets/models/sphere.fbx");
  physMesh.material.color = RGB(1, 0, 0);
  MeshRenderer physMesh2 = MeshRenderer("assets/models/sphere.fbx");
  physMesh2.material.color = RGB(0, 1, 0);
  physMesh2.transform.position.y = 1.0f;
  audio.transform.position = physMesh.transform.GetInheritedPosition();
  audio.MakeChildOf(&physMesh);

  window.blackBars = false;

  f32 vel1 = 5.0f;
  f32 vel2 = 5.0f;

  f32 scale = Time::GetTimeScale();

  audio.Play();
  audio.SetLooping(true);

  while (window.IsRunning()) {
    Engine::BeginFrame();

    window.Update();

    if (Input::GetKeyOnce(&toggleWireframe)) {
      Renderer::ToggleWireframe();
    }

    if (Input::GetKeyOnce(&toggleFullscreen)) {
      window.ToggleFullscreen();
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

    physMesh.transform.position.x += vel1 * Time::DeltaTime(true);

    if (physMesh.transform.position.x > 5.0f ||
        physMesh.transform.position.x < -5.0f)
      vel1 = -vel1;

    physMesh2.transform.position.x += vel2 * Time::DeltaTime();

    if (physMesh2.transform.position.x > 5.0f ||
        physMesh2.transform.position.x < -5.0f)
      vel2 = -vel2;

    // LOG(Mathf::ToString(rb.transform.position));
    EntityManager::UpdateAll();

    UIContext::GetIO()->DisplaySize =
        ImVec2(Engine::GetWindow()->GetViewportSize().x,
               Engine::GetWindow()->GetViewportSize().y);
    ImGui::SetNextWindowPos(
        ImVec2(Engine::GetWindow()->GetViewportPosition().x,
               Engine::GetWindow()->GetViewportPosition().y));
    ImGui::SetNextWindowSize(ImVec2(0, 0));

    ImGui::Begin("viewport", nullptr,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
    ImGui::Text("FPS: %d", Engine::GetFps());
    ImGui::Text("Delta Time: %f (* %f)", Time::DeltaTime(),
                Time::GetTimeScale());
    ImGui::DragFloat("Time scale", &scale, 0.1f, -1.0f, 1.0f);
    ImGui::Text("Entities: %d", EntityManager::GetNumberOfEntities());
    ImGui::Text("Drawn Entities: %d", Engine::GetDrawnEntities());
    if (ImGui::CollapsingHeader("Fog Settings")) {
      ImGui::ColorEdit3("Sky Color",
                        glm::value_ptr(*Renderer::GetSkyColorPtr()));
      ImGui::ColorEdit3("Fog Color",
                        glm::value_ptr(*Renderer::GetFogColorPtr()));
    }
    // ImGui::Text("Bodies: %d", Physics::GetNumberOfBodies());
    ImGui::DragFloat3("Player Position",
                      glm::value_ptr(player.transform.position));
    ImGui::DragFloat("FOV ", &cam.fov, 1.0f, 60.0f, 200.0f);
    ImGui::DragFloat("Sensitivity", &cam.sens, 0.05f, 0.0f, 4.0f);
    ImGui::DragFloat("Culling Angle", &cam.cullingAngle, 0.05f, -1.0f, 1.0f);
    ImGui::DragFloat("Culling Distance", &cam.cullingDistance, 0.5f, 0.0f,
                     100.0f);
    ImGui::Checkbox("Blackbars", &window.blackBars);
    if (ImGui::Button("Quit")) {
      window.Stop();
    }

    ImGui::End();

    window.SwapAndClear();

    Time::SetTimeScale(scale);

    Engine::EndFrame();
    // window.Stop();
  }

  EntityManager::DestroyAll();

  /*
    FIXME:
    calling Renderer::Shutdown() down after window.Destroy causes
    segfault (???)
  */
  UIContext::Shutdown();
  Renderer::Shutdown();
  window.Destroy();
  Engine::Shutdown();
}