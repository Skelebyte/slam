#ifndef SLAM_MESH_HPP
#define SLAM_MESH_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/ufbx/ufbx.h"
#include "../list.hpp"
#include "../util/file.hpp"
#include "vertex.hpp"

namespace slam::res {

struct Mesh {
  Mesh() = default;
  Mesh(sString path);
  List<Vertex> vertices;
  List<sUint> indices;

  List<float> data;
};

} // namespace slam::res

#endif