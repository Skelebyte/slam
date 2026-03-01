;
#ifndef SLAM_COMPONENT_HPP
#define SLAM_COMPONENT_HPP

#include "../common.hpp"

namespace slam::scn {
struct Component : public ID, public Destroyable {
  Component();
  virtual void Process() = 0;
  virtual void Destroy() = 0;

  bool enabled = true;
  sUint attachedEntityID = 0;
};

struct ComponentManager : public Singleton<ComponentManager> {
  sUint GetNextID();

private:
  sUint nextID = 1;
};

struct Transform : public Component {

  Transform() = default;

  void Process() override {}
  void Destroy() override {}
};
} // namespace slam::scn

#endif