#ifndef SLAM_MESH_RENDERER_HPP
#define SLAM_MESH_RENDERER_HPP

#include "../engine.hpp"
#include "../err/err_sys.hpp"
#include "../evt/evt_sys.hpp"
#include "../gfx/ebo.hpp"
#include "../gfx/material.hpp"
#include "../gfx/renderer.hpp"
#include "../gfx/shader.hpp"
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

struct MeshRenderer : public Entity {
  MeshRenderer(const str &path) : Entity() {

    this->shader = Renderer::GetShader("default");
    mesh = Mesh(path);
    material = Default("", RGB255(255));

    model = Mat4();

    vao = VAO();
    vbo = VBO();
    ebo = EBO();

    vao.Init();
    vao.Bind();

    vbo.Init(mesh.data.Pointer(), sizeof(f32) * mesh.data.Size());
    ebo.Init(mesh.indices.Pointer(), sizeof(u32) * mesh.indices.Size());

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(f32), (void *)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(f32),
                   (void *)(3 * sizeof(f32)));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(f32),
                   (void *)(5 * sizeof(f32)));

    vbo.Unbind();
    vao.Unbind();
    ebo.Unbind();
  }

  void Destroy() override {
    DESTROY();
    Entity::Destroy();
    shader = nullptr;
  }

  void Update() override {
    IS_DESTROYED();

    transform.Process();

    if (!Engine::Get().IsProcessFrame()) {
      return;
    }

    Vec3 direction = Mathf::Normalized(
        transform.GetGlobalPosition() -
        Renderer::GetCameraTransformPtr()->GetGlobalPosition());

    if (Mathf::Dot(direction,
                   Renderer::GetCameraTransformPtr()->InheritedForward()) <
            Renderer::GetCameraCullingAngle() &&
        Mathf::Distance(
            transform.GetGlobalPosition(),
            Renderer::GetCameraTransformPtr()->GetGlobalPosition()) >=
            Renderer::GetCameraCullingDistance() &&
        allowViewCulling) {
      return;
    }

    Engine::SetDrawnEntities(Engine::GetDrawnEntities() + 1);

    model = Mat4(1.0f);

    model = glm::translate(model, transform.GetGlobalPosition());

    model *= glm::mat4_cast(
        transform.GetGlobalRotation()); // convert to mat4x4 rotation

    model = glm::scale(model, transform.GetGlobalScale());

    shader->Bind();
    shader->GetUniform("model")->SetValue(model);
    material.Bind();

    vao.Bind();
    glDrawElements(GL_TRIANGLES, mesh.indices.Size(), GL_UNSIGNED_INT, 0);
    THROW_ERROR_GL(FATAL.Derived("GL_DRAW_ELEMENTS_FAIL"));

    Entity::Update();
  }

  Mesh mesh;
  Default material;
  bool allowViewCulling = true;

private:
  Shader *shader;
  Mat4 model;

  VAO vao;
  VBO vbo;
  EBO ebo;
};

} // namespace slam::entities

#endif