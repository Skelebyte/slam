#include "shader.hpp"

using namespace slam;
using namespace slam::dpy;
using namespace slam::gfx;
using namespace slam::err;
using namespace slam::util;
using namespace slam::math;

Uniform::Uniform(const sString &name, sUint shaderID) {
  id = glGetUniformLocation(shaderID, name.c_str());
  THROW_ERROR_GL(FATAL.Derived(
      "GL_GET_UNIFORM_LOCATION_FAIL",
      "Something is wrong here, is the uniform name `" + name + "` correct?"));

  this->name = name;
}

sString Uniform::GetName() const { return name; }

sUint Uniform::GetID() const { return id; }

void Uniform::SetValue(const Mat4 &value) {
  glUniformMatrix4fv(id, 1, GL_FALSE, value.data);
  THROW_ERROR_GL(
      FATAL.Derived("GL_UNIFORM_MATRIX_4FV_FAIL",
                    "Failed to set Matrix4x4 uniform `" + name + "`."));
}

void Uniform::SetValue(const Vec3 &value) {
  glUniform3fv(id, 1, value.data);
  THROW_ERROR_GL(FATAL.Derived("GL_UNIFORM_3FV_FAIL",
                               "Failed to set float3 uniform `" + name + "`."));
}

void Uniform::SetValue(float value) {
  glUniform1f(id, value);
  THROW_ERROR_GL(FATAL.Derived("GL_UNIFORM_1F_FAIL",
                               "Failed to set float1 uniform `" + name + "`."));
}

void Uniform::SetValue(int value) {
  glUniform1i(id, value);
  THROW_ERROR_GL(FATAL.Derived("GL_UNIFORM_1I_FAIL",
                               "Failed to set int1 uniform `" + name + "`."));
}

Shader::Shader(const sString &name, const sString &fragPath,
               const sString &vertPath) {
  if (File::Exists(fragPath) == false) {
    THROW_ERROR(FATAL.Derived("", "No file " + fragPath + " found."));
    return;
  }
  if (File::Exists(vertPath) == false) {
    THROW_ERROR(FATAL.Derived("", "No file " + vertPath + " found."));
    return;
  }

  SetName(name);

  sString fragContent = File::Read(fragPath);
  sString vertContent = File::Read(vertPath);

  if (fragContent.empty()) {
    THROW_ERROR(
        FATAL.Derived("", "Failed to read fragment shader " + fragPath + "."));
  }

  if (vertContent.empty()) {
    THROW_ERROR(
        FATAL.Derived("", "Failed to read vertex shader " + vertPath + "."));
  }

  // content in c-string format
  const char *ccFrag = fragContent.c_str();
  const char *ccVert = vertContent.c_str();

  sUint frag = glCreateShader(GL_FRAGMENT_SHADER);
  THROW_ERROR_GL(FATAL.Derived("GL_CREATE_SHADER_FAIL",
                               "Failed to create fragment shader."));

  glShaderSource(frag, 1, &ccFrag, NULL);

  glCompileShader(frag);
  THROW_ERROR_GL(FATAL.Derived("GL_COMPILE_SHADER_FAIL",
                               "Fragment shader compile failed."));

  if (IsCompileNotOK(frag, "FRAGMENT"))
    return;

  sUint vert = glCreateShader(GL_VERTEX_SHADER);
  THROW_ERROR_GL(FATAL.Derived("GL_CREATE_SHADER_FAIL",
                               "Failed to create vertex shader."));

  glShaderSource(vert, 1, &ccVert, NULL);

  glCompileShader(vert);
  THROW_ERROR_GL(
      FATAL.Derived("GL_COMPILE_SHADER_FAIL", "Vertex shader compile failed."));

  if (IsCompileNotOK(vert, "VERTEX"))
    return;

  SetID(glCreateProgram());

  glAttachShader(GetID(), frag);
  THROW_ERROR_GL(FATAL.Derived("GL_ATTACH_SHADER_FAIL",
                               "Failed to attach fragment shader."));

  glAttachShader(GetID(), vert);
  THROW_ERROR_GL(FATAL.Derived("GL_ATTACH_SHADER_FAIL",
                               "Failed to attach vertex shader."));

  glLinkProgram(GetID());
  THROW_ERROR_GL(
      FATAL.Derived("GL_LINK_PROGRAM_FAIL", "Failed to link shader program."));

  IsLinkOK();

  int isProgramValid = glIsProgram(GetID());
  LOG("Is program valid: " << isProgramValid << ".");

  glDeleteShader(frag);
  glDeleteShader(vert);
}

void Shader::Destroy() {
  DESTROY();

  glDeleteProgram(GetID());
  SetID(0);
}

void Shader::AddUniform(const sString &name) {
  IS_DESTROYED();

  for (int i = 0; i < uniforms.Size(); i++) {
    if (uniforms[i].GetName() == name) {
      THROW_ERROR(ERROR.Derived("", "Uniform `" + name +
                                        "` already exists in this shader!"));
      return;
    }
  }

  uniforms.Add(Uniform(name, GetID()));
}

Uniform *Shader::GetUniform(const sString &name) {
  IS_DESTROYED(nullptr);

  for (int i = 0; i < uniforms.Size(); i++) {
    if (uniforms[i].GetName() == name)
      return &uniforms[i];
  }

  THROW_ERROR(
      FATAL.Derived("", "No uniform with the name " + name +
                            " was found. Have you used `Shader::AddUniform()` "
                            "or renamed the uniform in the .glsl?"));
  return nullptr;
}

void Shader::Bind() {
  IS_DESTROYED();

  glUseProgram(GetID());
  THROW_ERROR_GL(FATAL.Derived("GL_USE_PROGRAM_FAIL"));
}

void Shader::SetName(const sString &name) { this->name = name; }

sString &Shader::GetName() { return name; }

bool Shader::IsCompileNotOK(sUint shader, const sString &type) {
  int success;
  char log[1024];
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 1024, NULL, log);
    THROW_ERROR_GL(FATAL.Derived(
        "asasd", type + " compile is NOT ok! OpenGL Log: " + sString(log)));
    return true;
  }
  return false;
}

bool Shader::IsLinkOK() {
  GLint success;
  GLchar log[1024];
  glGetProgramiv(GetID(), GL_LINK_STATUS, &success);

  GLint logLength;
  glGetProgramiv(GetID(), GL_INFO_LOG_LENGTH, &logLength);

  if (!success) {
    glGetProgramInfoLog(GetID(), 1024, NULL, log);
    THROW_ERROR_GL(FATAL.Derived("", "Program link is NOT ok! OpenGL log: " +
                                         sString(log)));
    return true;
  }

  return false;
}