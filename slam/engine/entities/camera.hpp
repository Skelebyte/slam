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
#include "../time.hpp"

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
  Camera() : pauseLook(Keycode::ESC) {
    view = Mat4();
    projection = Mat4();
    shader = Renderer::Get().GetShader("default");

    Renderer::Get().cameraTransform = &transform;
    Renderer::Get().cameraView = &view;
    Renderer::Get().cameraProjection = &projection;
    Renderer::Get().cameraCullingAngle = &cullingAngle;
    Renderer::Get().cameraCullingDistance = &cullingDistance;
  }
  void Destroy() override {
    DESTROY();
    Entity::Destroy();
    shader = nullptr;
    // deleting stuff/freeing memory
  }
  void Update() override {
    IS_DESTROYED();

    transform.Process();
    MouseLook();

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

  void MouseLook() {
    if (Input::GetKeyOnce(&pauseLook)) {
      allowMouseLook = !allowMouseLook;
      LOG("allowMouseLook: " << allowMouseLook);
    }

    if (!allowMouseLook) {
      Input::SetCursor(false, false);
      return;
    }

    Input::SetCursor(true, true);

    Vec2 mouse = Input::GetMousePosition();

    f32 x = (-mouse.y) * sens * Time::DeltaTime();
    f32 y = (-mouse.x) * sens * Time::DeltaTime();

    transform.rotation.x += Mathf::ToDegrees(x);
    if (transform.parent != nullptr) {
      transform.parent->rotation.y += Mathf::ToDegrees(y);
    } else {
      transform.rotation.y += Mathf::ToDegrees(y);
    }

    transform.rotation.x = Mathf::Clamp(transform.rotation.x, -89.0f, 89.0f);
  }

  f32 fov = 75.0f;
  f32 near = 0.1f;
  f32 far = 1000.0f;
  Mat4 view;
  Mat4 projection;
  bool allowMouseLook = false;
  f32 sens = 0.1f;
  f32 cullingAngle = 0.4f;
  // minimum distance before culling
  f32 cullingDistance = 10.0f;

private:
  Shader *shader;
  Keybind pauseLook;
};

} // namespace slam::entities

#endif