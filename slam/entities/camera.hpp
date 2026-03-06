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
#include "../math/mat4.hpp"
#include "../math/vec3.hpp"
#include "../res/mesh.hpp"
#include "../scn/component.hpp"
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
  }
  void Destroy() override {
    DESTROY();

    shader = nullptr;
    // deleting stuff/freeing memory
  }
  void Update() override {
    IS_DESTROYED();

    transform.Process();

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

} // namespace slam::entities

#endif