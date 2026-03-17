#ifndef SLAM_SHADER_HPP
#define SLAM_SHADER_HPP

#include "../../third_party/glad/glad.h"
#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "../util/file.hpp"
#include "color.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {
struct Uniform {
  Uniform(const str &name, u32 shaderID);
  str GetName() const;
  u32 GetID() const;

  void SetValue(const math::Mat4 &value);
  void SetValue(const math::Vec3 &value);
  void SetValue(const RGB255 &value);
  void SetValue(const RGB &value);
  void SetValue(f32 value);
  void SetValue(i32 value);
  void SetValue(bool value);

private:
  str name;
  u32 id;
};

struct Shader : public ID, public Destroyable {
  Shader(const str &name, const str &fragPath = "assets/shaders/fragment.glsl",
         const str &vertPath = "assets/shaders/vertex.glsl");
  void Destroy() override;
  void AddUniform(const str &name);
  Uniform *GetUniform(const str &name);
  void Bind();
  void SetName(const str &name);
  str &GetName();

private:
  str name = "";
  List<Uniform> uniforms;
  bool IsCompileNotOK(u32 shader, const str &type);
  bool IsLinkOK();
};

} // namespace slam::gfx

#endif