#include "vao.hpp"

using namespace slam;
using namespace slam::gfx;
using namespace slam::err;

void VAO::Init() {
  glGenVertexArrays(1, GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("GL_GEN_VERTEX_ARRAYS_FAIL",
                               "Generating the VAO buffer failed!"));
}

void VAO::Destroy() {
  DESTROY();

  glDeleteVertexArrays(1, GetID_Ptr());
}

void VAO::Bind() {
  IS_DESTROYED();

  glBindVertexArray(*GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("GL_BIND_VERTEX_ARRAY_FAIL",
                               "Binding the VAO buffer failed!"));
}

void VAO::Unbind() {
  IS_DESTROYED();

  glBindVertexArray(0);
}

void VAO::LinkAttrib(VBO &vbo, sUint layout, sUint components, sUint type,
                     size_t stride, void *offset) {
  IS_DESTROYED();

  vbo.Bind();
  glVertexAttribPointer(layout, components, type, GL_FALSE, stride, offset);
  THROW_ERROR_GL(FATAL.Derived("GL_VERTEX_ATTRIB_POINTER_FAIL"));

  glEnableVertexAttribArray(layout);
  THROW_ERROR_GL(FATAL.Derived("GL_ENABLE_VERTEX_ATTRIB_ARRAY_FAIL"));

  vbo.Unbind();
}