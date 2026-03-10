#ifndef SLAM_TRANSFORM_HPP
#define SLAM_TRANSFORM_HPP

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

} // namespace slam::scn

#endif