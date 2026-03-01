#ifndef SLAM_FILE_HPP
#define SLAM_FILE_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include <ctime>
#include <filesystem>
#include <fstream>
#include <iostream>

namespace slam::util {
struct File {
  static sString Read(sString path);
  static void Write(sString path, sString content, bool overwrite = false);
  static bool Exists(sString path);
};
} // namespace slam::util

#endif