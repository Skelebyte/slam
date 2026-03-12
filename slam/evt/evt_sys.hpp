#ifndef SLAM_EVT_SYS_HPP
#define SLAM_EVT_SYS_HPP

#include "evt.hpp"

namespace slam::evt {

struct EventSystem : public Singleton<EventSystem> {
  EventSystem() = default;

  Event OnQuit;
  Event OnUpdate;
  Event OnError;
};

} // namespace slam::evt

#endif