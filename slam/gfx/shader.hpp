#ifndef SLAM_SHADER_HPP
#define SLAM_SHADER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "../util/file.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {
struct Uniform {
  Uniform(const sString &name, sU32 shaderID);
  sString GetName() const;
  sU32 GetID() const;

  void SetValue(const math::Mat4 &value);
  void SetValue(const math::Vec3 &value);
  void SetValue(sF32 value);
  void SetValue(sI32 value);

private:
  sString name;
  sU32 id;
};

struct Shader : public ID, public Destroyable {
  Shader(const sString &name,
         const sString &fragPath = "assets/shaders/fragment.glsl",
         const sString &vertPath = "assets/shaders/vertex.glsl");
  void Destroy() override;
  void AddUniform(const sString &name);
  Uniform *GetUniform(const sString &name);
  void Bind();
  void SetName(const sString &name);
  sString &GetName();

private:
  sString name = "";
  List<Uniform> uniforms;
  bool IsCompileNotOK(sU32 shader, const sString &type);
  bool IsLinkOK();
};

} // namespace slam::gfx

#endif