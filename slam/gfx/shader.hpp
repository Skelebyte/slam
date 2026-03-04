#ifndef SLAM_SHADER_HPP
#define SLAM_SHADER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../math/mat4.hpp"
#include "../util/file.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {
struct Uniform {
  Uniform(const sString &name, sUint shaderID);
  sString GetName() const;
  sUint GetID() const;

  void SetValue(const math::Mat4 &value);
  void SetValue(const math::Vec3 &value);
  void SetValue(float value);
  void SetValue(int value);

private:
  sString name;
  sUint id;
};

struct Shader : public ID, public Destroyable {
  Shader(const sString &fragPath = "assets/shaders/fragment.glsl",
         const sString &vertPath = "assets/shaders/vertex.glsl");
  void Destroy() override;
  void AddUniform(const sString &name);
  Uniform *GetUniform(const sString &name);
  void Bind();

private:
  List<Uniform> uniforms;
  bool IsCompileNotOK(sUint shader, const sString &type);
  bool IsLinkOK();
};

} // namespace slam::gfx

#endif