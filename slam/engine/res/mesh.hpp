#ifndef SLAM_MESH_HPP
#define SLAM_MESH_HPP

#include "../../third_party/ufbx/ufbx.h"
#include "../common.hpp"
#include "../err/err_sys.hpp"
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
  Mesh(const str &path, bool blenderFix = true);
  static Mesh GeneratePlane(uint32 divisions, const math::Vec2 &dimensions);
  List<Vertex> vertices;
  List<uint32> indices;

  List<float32> data;
};

} // namespace slam::res

#endif