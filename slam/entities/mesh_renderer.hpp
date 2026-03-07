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

struct MeshRenderer : public Entity {
  MeshRenderer(const sString &path) {
    this->shader = Renderer::Get().GetShader("default");
    mesh = Mesh(path);
    material = Default("", RGB255(255));

    model = Mat4();

    vao = VAO();
    vbo = VBO();
    ebo = EBO();

    vao.Init();
    vao.Bind();

    vbo.Init(mesh.data.Pointer(), sizeof(sF32) * mesh.data.Size());
    ebo.Init(mesh.indices.Pointer(), sizeof(sU32) * mesh.indices.Size());

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(sF32), (void *)0);
    vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(sF32),
                   (void *)(3 * sizeof(sF32)));
    vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(sF32),
                   (void *)(5 * sizeof(sF32)));

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

    transform.Process();

    if (!Engine::Get().IsDrawFrame()) {
      return;
    }

    model = Mat4(1.0f);

    model = glm::translate(model, transform.GetInheritedPosition());

    model *= glm::mat4_cast(transform.GetInheritedRotation());

    model = glm::scale(model, transform.GetInheritedScale());

    // model = Mat4::Transformation(transform.GetInheritedPosition(),
    //                              transform.GetInheritedRotation(),
    //                              transform.GetInheritedScale());

    shader->Bind();
    shader->GetUniform("model")->SetValue(model);
    material.Bind();

    vao.Bind();
    glDrawElements(GL_TRIANGLES, mesh.indices.Size(), GL_UNSIGNED_INT, 0);
    THROW_ERROR_GL(FATAL.Derived("GL_DRAW_ELEMENTS_FAIL"));
  }

  Mesh mesh;
  Default material;

private:
  Shader *shader;
  Mat4 model;

  VAO vao;
  VBO vbo;
  EBO ebo;
};

} // namespace slam::entities

#endif