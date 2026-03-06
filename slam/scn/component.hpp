;
#ifndef SLAM_COMPONENT_HPP
#define SLAM_COMPONENT_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"

namespace slam::scn {

struct Transform {
  Transform();

  void Process();

  math::Vec3 Forward() const;
  math::Vec3 InheritedForward() const;
  math::Vec3 Right() const;
  math::Vec3 GetInheritedPosition() const;
  math::Quat GetInheritedRotation() const;
  // // math::Quat GetInheritedRotation() const;
  math::Vec3 GetInheritedScale() const;

  math::Vec3 position;
  math::Vec3 rotation;
  // Quat qRotation;
  math::Vec3 scale;

  Transform *parent = nullptr;
};

struct Component : public ID, public Destroyable {
  Component();
  virtual void Process() = 0;
  virtual void Destroy() = 0;

  Transform *transform;
  bool enabled = true;
  sU32 attachedEntityID = 0;
};

struct ComponentManager : public Singleton<ComponentManager> {
  sU32 GetNextID();

private:
  sU32 nextID = 1;
};

} // namespace slam::scn

#endif