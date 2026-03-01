#ifndef SLAM_EVT_SYS_HPP
#define SLAM_EVT_SYS_HPP

#include "evt.hpp"

namespace slam::evt {

struct EventSystem : public Singleton<EventSystem> {
  EventSystem() = default;

  Event on_quit;
  Event on_update;
  Event on_error;
};

} // namespace slam::evt

#endif