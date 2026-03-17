#include "vbo.hpp"

using namespace slam;
using namespace slam::gfx;
using namespace slam::err;

void VBO::Init(f32 *vertices, size_t size) {
  glGenBuffers(1, GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("GL_GEN_BUFFERS_FAIL",
                               "Generating the VBO buffer failed!"));

  glBindBuffer(GL_ARRAY_BUFFER, *GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("GL_BIND_BUFFER_FAIL",
                               "Binding VBO failed (Constructor)!"));

  glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
  THROW_ERROR_GL(FATAL.Derived("GL_BUFFER_DATA_FAIL",
                               "Assigning data to the VBO failed!"));
}

void VBO::Destroy() {
  DESTROY();

  glDeleteBuffers(1, GetID_Ptr());
}

void VBO::Bind() {
  IS_DESTROYED();

  glBindBuffer(GL_ARRAY_BUFFER, *GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("GL_BIND_BUFFER_FAIL", "Binding VBO failed!"));
}

void VBO::Unbind() {
  IS_DESTROYED();

  glBindBuffer(GL_ARRAY_BUFFER, 0);
}