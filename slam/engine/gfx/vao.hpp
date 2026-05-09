#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "vbo.hpp"

namespace slam::gfx {

class VAO : public Destroyable, public ID {
public:
  VAO() = default;
  void Init();
  void Destroy() override;
  void Bind();
  void Unbind();
  void LinkAttrib(VBO &vbo, uint32 layout, uint32 components, uint32 type,
                  size_t stride, void *offset);
};

} // namespace slam::gfx

#endif