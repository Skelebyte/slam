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
  static str Read(const str &path);
  static void Write(const str &path, const str &content,
                    bool overwrite = false);
  static bool Exists(const str &path);
};
} // namespace slam::util

#endif