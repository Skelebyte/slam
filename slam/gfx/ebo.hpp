#ifndef SLAM_EBO_HPP
#define SLAM_EBO_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/glad/glad.h"

namespace slam::gfx {
class EBO : public Destroyable, public ID {
public:
  EBO() = default;
  void Init(sUint *indices, size_t size);
  void Destroy() override;
  void Bind();
  void Unbind();
};
} // namespace slam::gfx

#endif