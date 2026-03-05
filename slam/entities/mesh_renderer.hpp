#ifndef SLAM_MESH_RENDERER_HPP
#define SLAM_MESH_RENDERER_HPP

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

    transform.Process();

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

} // namespace slam::entities

#endif