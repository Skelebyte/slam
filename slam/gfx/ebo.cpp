
#include "ebo.hpp"

using namespace slam;
using namespace slam::gfx;
using namespace slam::err;

void EBO::Init(sU32 *indices, size_t size) {
  glGenBuffers(1, GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("GL_GEN_BUFFERS_FAIL",
                               "Generating the EBO buffer failed!"));

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *GetID_Ptr());
  THROW_ERROR_GL(
      FATAL.Derived("GL_BIND_BUFFER_FAIL", "Binding the EBO buffer failed!"));

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
  THROW_ERROR_GL(FATAL.Derived("GL_BUFFER_DATA_FAIL",
                               "Assigning data to the EBO buffer failed!"));
}

void EBO::Destroy() {
  DESTROY();

  glDeleteBuffers(1, GetID_Ptr());
}

void EBO::Bind() {
  IS_DESTROYED();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *GetID_Ptr());
}

void EBO::Unbind() {
  IS_DESTROYED();

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}