#ifndef SLAM_VBO_HPP
#define SLAM_VBO_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/glad/glad.h"

namespace slam::gfx {
struct VBO : public Destroyable, public ID {
  VBO() = default;
  void Init(sF32 *vertices, size_t size);
  void Destroy() override;
  void Bind();
  void Unbind();
};
} // namespace slam::gfx

#endif