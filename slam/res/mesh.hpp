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
  /**
   * @brief Construct a new Mesh object
   *
   * @param path
   * @param blenderFix if true, will change the way its imported to make +y the
   * up vector.
   */
  Mesh(const sString &path, bool blenderFix = true);
  List<Vertex> vertices;
  List<sU32> indices;

  List<sF32> data;
};

} // namespace slam::res

#endif