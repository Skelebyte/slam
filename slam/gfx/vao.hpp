#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/glad/glad.h"
#include "vbo.hpp"

namespace slam::gfx {

class VAO : public Destroyable, public ID {
public:
  VAO() = default;
  void Init();
  void Destroy() override;
  void Bind();
  void Unbind();
  void LinkAttrib(VBO &vbo, sUint layout, sUint components, sUint type,
                  size_t stride, void *offset);
};

} // namespace slam::gfx

#endif