#ifndef SLAM_EBO_HPP
#define SLAM_EBO_HPP

#include "../../third_party/glad/glad.h"
#include "../common.hpp"
#include "../err/err_sys.hpp"

namespace slam::gfx {
class EBO : public Destroyable, public ID {
public:
  EBO() = default;
  void Init(u32 *indices, size_t size);
  void Destroy() override;
  void Bind();
  void Unbind();
};
} // namespace slam::gfx

#endif