#ifndef SLAM_LINE_HPP
#define SLAM_LINE_HPP

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
#include "../scn/component.hpp"
#include "../scn/entity.hpp"
#include "camera.hpp"

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

struct Line : public Entity {
  Line(Camera *camera, const Vec3 &start, const Vec3 &end) {
    shader = Renderer::Get().GetShader("line");
    this->camera = camera;
    this->start = start;
    this->end = end;

    points = List<sF32>();
    points.Add(start.x);
    points.Add(start.y);
    points.Add(start.z);

    points.Add(end.x);
    points.Add(end.y);
    points.Add(end.z);

    vao = VAO();
    vbo = VBO();

    vao.Init();
    vao.Bind();

    vbo.Init(points.Pointer(), sizeof(sF32) * points.Size());

    vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 3 * sizeof(sF32), (void *)0);

    vbo.Unbind();
    vao.Unbind();
  }

  void Destroy() override {
    DESTROY();

    shader = nullptr;
    camera = nullptr;
  }

  void Update() override {
    IS_DESTROYED();

    if (Engine::Get().IsDrawFrame() == false)
      return;

    shader->Bind();
    shader->GetUniform("view")->SetValue(camera->view);
    shader->GetUniform("projection")->SetValue(camera->projection);
    shader->GetUniform("color")->SetValue(color);

    vao.Bind();
    glDrawArrays(GL_LINES, 0, 2);
  }
  Vec3 color = Vec3(1.0f, 0.0f, 0.0f);
  Vec3 start;
  Vec3 end;

private:
  List<sF32> points;
  Camera *camera;
  VAO vao;
  VBO vbo;
  Shader *shader;
};

} // namespace slam::entities

#endif