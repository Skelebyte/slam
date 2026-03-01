#include "vertex.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::res;

Vertex::Vertex(Vec3 pos, Vec2 uv, Vec3 norm) {
  position = pos;
  this->uv = uv;
  normal = norm;
}