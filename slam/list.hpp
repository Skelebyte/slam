#ifndef SLAM_LIST_HPP
#define SLAM_LIST_HPP

#include "common.hpp"
#include "err/err_sys.hpp"
#include <vector>

namespace slam {
template <typename T> struct List {
  List() { data = std::vector<T>(); }
  sUint Size() { return data.size(); }
  void Add(const T &value, bool first = false) {
    if (first) {
      data.insert(data.begin(), value);
    } else {
      data.push_back(value);
    }
  }

  void Remove(sUint index) {
    if (index > Size()) {
      err::ErrorSystem::THROW_ERROR(err::ERROR.Derived(
          "INDEX_OUT_OF_BOUNDS", "Index " + std::to_string(index) +
                                     " is out of bounds. Size of list: " +
                                     std::to_string(Size()) + "."));
      return;
    }

    data.erase(data.begin() + index);
  }

  void Clear() { data.clear(); }

  T &operator[](sUint index) {
    if (index > Size()) {
      err::ErrorSystem::THROW_ERROR(err::FATAL.Derived(
          "INDEX_OUT_OF_BOUNDS", "Index " + std::to_string(index) +
                                     " is out of bounds. Size of list: " +
                                     std::to_string(Size()) + "."));
      // return nullptr;
    }

    return data[index];
  }

private:
  std::vector<T> data;
};
} // namespace slam

#endif