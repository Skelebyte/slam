#define SLAM_USING_NAMESPACES
#define SLAM_ENTRY_POINT "My Game"
#include "../slam/slam.hpp"

Camera *camera;
MeshRenderer *ground;
MeshRenderer *tree;
float32 speed = 5.0f;

void App::Start() {
  camera = new Camera();

  ground = new MeshRenderer("assets/models/cube.fbx");
  ground->transform.position.y = -1.0f;
  ground->transform.scale = Vec3(10, 1, 10);

  tree = new MeshRenderer("assets/models/TreePodium.fbx");
  tree->material.diffuse = Texture("assets/textures/TreePodium.png");
  tree->transform.position = Vec3(2.5, -.5, 2.5);
  tree->transform.scale = Vec3(0.3f);
}

void App::Update() {

  if (Input::GetKey(Keycode::RMB)) {
    camera->allowMouseLook = true;
  } else {
    camera->allowMouseLook = false;
  }

  camera->transform.position +=
      Mathf::Normalized(Input::GetAxis(Keycode::A, Keycode::D) *
                            camera->transform.Right() * speed +
                        Input::GetAxis(Keycode::S, Keycode::W) *
                            camera->transform.Forward() * speed) *
      Time::DeltaTime();
}

void App::Quit() { Engine::GetWindow()->Stop(); }