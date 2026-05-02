#ifndef SLAM_VERTEX_HPP
#define SLAM_VERTEX_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"

namespace slam::res {

struct Vertex {
  Vertex() = default;
  Vertex(math::Vec3 pos, math::Vec2 uv, math::Vec3 norm);
  math::Vec3 position;
  math::Vec2 uv;
  math::Vec3 normal;
};

} // namespace slam::res

#endif
