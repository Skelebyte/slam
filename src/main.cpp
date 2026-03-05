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
#include "../slam/math/mat4.hpp"
#include "../slam/math/vec3.hpp"
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

int main() {
  Engine::Get().Init();
  Window window = Window("Hi mum!");
  Renderer::Get().Init(&window);

  ErrorSystem::Get().silenceWarnings = true;

  Shader shader =
      Shader("assets/shaders/fragment.glsl", "assets/shaders/vertex.glsl");
  shader.AddUniform("model");
  shader.AddUniform("view");
  shader.AddUniform("projection");
  shader.AddUniform("diffuse_texture");
  shader.AddUniform("light_color");

  Keybind toggleWireframe = Keybind(Keycode::F1);

  Camera cam = Camera(&shader);

  MeshRenderer cube = MeshRenderer(&shader, "assets/models/cube.fbx");
  cube.transform.position = Vec3(0, -2, 0);
  cube.transform.scale = Vec3(10, 1, 10);
  cube.texture =
      Texture("assets/textures/demo/ground.png", slam::gfx::TF_NEAREST);

  MeshRenderer slime = MeshRenderer(&shader, "assets/models/cube.fbx");
  slime.texture = Texture("assets/textures/demo/transparency.png",
                          TextureFilter::TF_NEAREST);

  MeshRenderer slime2 = MeshRenderer(&shader, "assets/models/cube.fbx");
  slime2.texture = Texture("assets/textures/demo/transparency.png",
                           TextureFilter::TF_NEAREST);
  slime2.transform.position.z = -5;

  slime2.MakeChildOf(&slime);

  MeshRenderer gun = MeshRenderer(&shader, "assets/models/BasicGun.fbx");
  gun.transform.position.x += 1;
  gun.transform.position.y -= 0.25;
  gun.transform.position.z -= 1;
  gun.MakeChildOf(&cam);

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);

  Line line = Line(&cam, Vec3(0, 1, 0), Vec3(4, 0.5, -3));

  while (window.IsRunning()) {
    window.Update();

    shader.Bind();
    shader.GetUniform("light_color")->SetValue(Vec3(1.0, 1.0f, 1.0f));

    if (Input::Get().GetKeyOnce(&toggleWireframe)) {
      Renderer::Get().ToggleWireframe();
    }

    Vec3 velocity = Vec3();
    velocity +=
        cam.transform.Right() * ((float)Input::Get().GetAxis(horizontal) / 100);
    velocity += cam.transform.Forward() *
                -((float)Input::Get().GetAxis(vertical) / 100);

    cam.transform.position += velocity.Normalized() / 100;

    cam.transform.rotation.y +=
        Mathf::ToDegrees((float)Input::Get().GetAxis(rotY) / 100);

    slime.transform.rotation.x += 0.5f;
    slime.transform.rotation.y += 0.5f;
    slime.transform.rotation.z += 0.5f;

    cam.Update();
    cube.Update();
    slime.Update();
    slime2.Update();
    gun.Update();

    line.Update();

    glClearColor(0.05f, 0.1f, 0.05f, 1.0f);

    window.SwapAndClear();
    SDL_Delay(10);
  }

  cam.Destroy();
  cube.Destroy();

  window.Destroy();
  Renderer::Get().Shutdown();
  Engine::Get().Shutdown();
}