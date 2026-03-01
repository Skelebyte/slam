#ifndef SLAM_EVT_HPP
#define SLAM_EVT_HPP

#include "../common.hpp"
#include "../list.hpp"
#include <functional>
#include <string>
#include <vector>

namespace slam::evt {
struct Event : public Destroyable {
  Event() = default;
  Event(const sString &name);
  void Invoke();
  void AddListener(const std::function<void()> &listener);
  void Destroy() override;
  void operator+=(const std::function<void()> &listener);

private:
  sString name;
  List<std::function<void()>> listeners;
};
} // namespace slam::evt

#endif