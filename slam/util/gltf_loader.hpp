#ifndef SLAM_GLTF_LOADER_HPP
#define SLAM_GLTF_LOADER_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/json.hpp"
#include "file.hpp"

namespace slam::util {

struct Loader {
  static void Load(const sString &path);
};

} // namespace slam::util

#endif