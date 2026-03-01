#ifndef SLAM_SHADER_HPP
#define SLAM_SHADER_HPP

#include "../common.hpp"
#include "../dpy/window.hpp"
#include "../ext/glad/glad.h"
#include "../list.hpp"
#include "../util/file.hpp"
#include <SDL3/SDL.h>

namespace slam::gfx {
struct Uniform {
  Uniform(const sString &name, sUint shaderID);
  sString GetName() const;
  sUint GetID() const;

private:
  sString name;
  sUint id;
};

struct Shader : public ID {

  Uniform *GetUniform(const sString &name);

  List<Uniform> uniforms; // private ??
};

} // namespace slam::gfx

#endif