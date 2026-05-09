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
  math::Vec3 GetGlobalPosition() const;
  math::Quat GetGlobalRotation() const;
  // // math::Quat GetGlobalRotation() const;
  math::Vec3 GetGlobalScale() const;

  // TODO: this afor position, rotation, and scale. prep for implmenting jolt
  //  void SetPosition(float32 xyz);
  //  void SetPosition(float32 x, float32 y, float32 z);
  //  math::Vec3 GetPositionLocal();
  //  math::Vec3 GetPositionGlobal();
  //  math::Vec3 *GetPositionLocalPtr();

  void SetRotation(float32 x, float32 y, float32 z);

  math::Vec3 position;
  math::Vec3 rotation;
  // Quat qRotation;
  math::Vec3 scale;

  Transform *parent = nullptr;
};

} // namespace slam::scn

#endif