#include "shader.hpp"

using namespace slam;
using namespace slam::dpy;
using namespace slam::gfx;
using namespace slam::err;
using namespace slam::util;

Uniform::Uniform(const sString &name, sUint shaderID) {
  id = glGetUniformLocation(shaderID, name.c_str());

  this->name = name;
}

sString Uniform::GetName() const { return name; }

sUint Uniform::GetID() const { return id; }

Uniform *Shader::GetUniform(const sString &name) {
  for (int i = 0; i < uniforms.Size(); i++) {
    if (uniforms[i].GetName() == name)
      return &uniforms[i];
  }

  THROW_ERROR(ERROR.Derived(
      "", "No uniform with the name " + name +
              " was found. Have you used `Renderer::Get().AddUniform()`?"));
  return nullptr;
}