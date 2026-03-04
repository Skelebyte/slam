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
  static sString Read(const sString &path);
  static void Write(const sString &path, const sString &content,
                    bool overwrite = false);
  static bool Exists(const sString &path);
};
} // namespace slam::util

#endif