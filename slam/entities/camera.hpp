#ifndef SLAM_CAMERA_HPP
#define SLAM_CAMERA_HPP

#include "../engine.hpp"
#include "../err/err_sys.hpp"
#include "../evt/evt_sys.hpp"
#include "../gfx/ebo.hpp"
#include "../gfx/renderer.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/texture.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"
#include "../input/input.hpp"
#include "../math/mathf.hpp"
#include "../res/mesh.hpp"
#include "../scn/entity.hpp"

using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam::input;
using namespace slam;

namespace slam::entities {

struct Camera : public Entity {
  Camera() {
    view = Mat4();
    projection = Mat4();
    shader = Renderer::Get().GetShader("default");

    Renderer::Get().cameraPosition = &transform.position;
    Renderer::Get().cameraView = &view;
    Renderer::Get().cameraProjection = &projection;
  }
  void Destroy() override {
    DESTROY();

    shader = nullptr;
    // deleting stuff/freeing memory
  }
  void Update() override {
    IS_DESTROYED();

    transform.Process();

    view = glm::lookAt(transform.GetInheritedPosition(),
                       transform.GetInheritedPosition() +
                           transform.InheritedForward(),
                       Vec3(0, 1, 0));

    projection =
        glm::perspective(Mathf::ToRadians(fov),
                         Engine::Get().window->GetViewportAspect(), near, far);

    shader->Bind();
    shader->GetUniform("view")->SetValue(view);
    shader->GetUniform("projection")->SetValue(projection);
    shader->GetUniform("camera_position")
        ->SetValue(transform.GetInheritedPosition());
    // shader->GetUniform("light_position")
    //     ->SetValue(transform.GetInheritedPosition());
    Entity::Update();
  }

  f32 fov = 75.0f;
  f32 near = 0.1f;
  f32 far = 1000.0f;
  Mat4 view;
  Mat4 projection;

private:
  Shader *shader;
};

} // namespace slam::entities

#endif