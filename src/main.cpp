#define SLAM_USING_NAMESPACES
#define SLAM_ENTRY_POINT "My Game"
#include "../slam/slam.hpp"

Camera *camera;
MeshRenderer *ground;
MeshRenderer *tree;
f32 speed = 5.0f;

Text *text;
Text *text2;

Button *quit;

void App::Start() {
  camera = new Camera();

  ground = new MeshRenderer("assets/models/cube.fbx");
  ground->transform.position.y = -1.0f;
  ground->transform.scale = Vec3(10, 1, 10);

  tree = new MeshRenderer("assets/models/TreePodium.fbx");
  tree->material.diffuse = Texture("assets/textures/TreePodium.png");
  tree->transform.position = Vec3(2.5, -.5, 2.5);
  tree->transform.scale = Vec3(0.3f);

  text = new Text("Hi mum!");
  text2 = new Text("Hi dad!");
  text2->position = Vec2(123, 231);

  quit = new Button("QUIT");
  quit->position.y = 32;
}

void App::Update() {
  if (quit->IsPressed()) {
    Engine::GetWindow()->Stop();
  }

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