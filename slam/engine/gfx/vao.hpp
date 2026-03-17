#ifndef GRAPHICS_HPP
#define GRAPHICS_HPP

#include "../../third_party/glad/glad.h"
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
  void LinkAttrib(VBO &vbo, u32 layout, u32 components, u32 type, size_t stride,
                  void *offset);
};

} // namespace slam::gfx

#endif