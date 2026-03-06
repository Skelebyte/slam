;
#ifndef SLAM_COMPONENT_HPP
#define SLAM_COMPONENT_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"

namespace slam::scn {

struct Transform {
  Transform();

  void Process();

  Vec3 Forward() const;
  Vec3 InheritedForward() const;
  Vec3 Right() const;
  Vec3 GetInheritedPosition() const;
  Vec3 GetInheritedRotation() const;
  // math::Quat GetInheritedRotation() const;
  Vec3 GetInheritedScale() const;

  Vec3 position;
  Vec3 rotation;
  // Quat qRotation;
  Vec3 scale;

  Transform *parent = nullptr;
};

struct Component : public ID, public Destroyable {
  Component();
  virtual void Process() = 0;
  virtual void Destroy() = 0;

  Transform *transform;
  bool enabled = true;
  sUint attachedEntityID = 0;
};

struct ComponentManager : public Singleton<ComponentManager> {
  sUint GetNextID();

private:
  sUint nextID = 1;
};

} // namespace slam::scn

#endif