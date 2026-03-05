#include "../slam/dpy/window.hpp"
#include "../slam/engine.hpp"
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
using namespace slam;

struct Camera : public Entity {
  Camera(Shader *shader) {
    view = Mat4();
    projection = Mat4();
    this->shader = shader;
  }
  void Destroy() override {
    DESTROY();

    shader = nullptr;
    // deleting stuff/freeing memory
  }
  void Update() override {
    IS_DESTROYED();

    // transform.Process();

    view.LookAt(transform.GetInheritedPosition(),
                transform.GetInheritedPosition() + transform.InheritedForward(),
                Vec3(0, 1, 0));

    projection.Perspective(fov, Engine::Get().window->GetViewportAspect(), near,
                           far);

    shader->Bind();
    shader->GetUniform("view")->SetValue(view);
    shader->GetUniform("projection")->SetValue(projection);
  }

  float fov = 75.0f;
  float near = 0.1f;
  float far = 100.0f;
  Mat4 view;
  Mat4 projection;

private:
  Shader *shader;
};

struct MeshRenderer : public Entity {
  MeshRenderer(Shader *shader, const sString &path) {
    this->shader = shader;
    mesh = Mesh(path);
    texture = Texture("assets/textures/demo/difuse.png", slam::gfx::TF_LINEAR);

    model = Mat4();

    vao = VAO();
    vbo = VBO();
    ebo = EBO();

    vao.Init();
    vao.Bind();

    vbo.Init(mesh.data.Pointer(), sizeof(float) * mesh.data.Size());
    ebo.Init(mesh.indices.Pointer(), sizeof(sUint) * mesh.indices.Size());

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(float), (void *)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(float),
                   (void *)(3 * sizeof(float)));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(float),
                   (void *)(5 * sizeof(float)));

    vbo.Unbind();
    vao.Unbind();
    ebo.Unbind();
  }

  void Destroy() override {
    DESTROY();

    shader = nullptr;
  }

  void Update() override {
    IS_DESTROYED();

    // transform.Process();

    model = Mat4::Transformation(transform.GetInheritedPosition(),
                                 transform.GetInheritedRotation(),
                                 transform.GetInheritedScale());

    shader->Bind();
    shader->GetUniform("model")->SetValue(model);
    glActiveTexture(GL_TEXTURE0);
    texture.Bind();
    shader->GetUniform("diffuse_texture")->SetValue(0);

    vao.Bind();
    glDrawElements(GL_TRIANGLES, mesh.indices.Size(), GL_UNSIGNED_INT, 0);
    THROW_ERROR_GL(FATAL.Derived("GL_DRAW_ELEMENTS_FAIL"));
  }

  Mesh mesh;
  Texture texture;

private:
  Shader *shader;
  Mat4 model;

  VAO vao;
  VBO vbo;
  EBO ebo;
};

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

  MeshRenderer slime = MeshRenderer(&shader, "assets/models/cube.fbx");
  slime.texture = Texture("assets/textures/demo/transparency.png",
                          TextureFilter::TF_NEAREST);

  MeshRenderer slime2 = MeshRenderer(&shader, "assets/models/cube.fbx");
  slime2.texture = Texture("assets/textures/demo/transparency.png",
                           TextureFilter::TF_NEAREST);
  slime2.transform.position.z = -5;

  MeshRenderer gun = MeshRenderer(&shader, "assets/models/BasicGun.fbx");
  gun.transform.position.x += 1;
  gun.transform.position.y -= 0.25;
  gun.transform.position.z -= 1;
  gun.MakeChildOf(&cam);

  InputAxis horizontal = InputAxis(Keycode::D, Keycode::A);
  InputAxis vertical = InputAxis(Keycode::S, Keycode::W);
  InputAxis rotY = InputAxis(Keycode::L_ARROW, Keycode::R_ARROW);

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

    cam.Update();
    cube.Update();
    slime.Update();
    slime2.Update();
    gun.Update();

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