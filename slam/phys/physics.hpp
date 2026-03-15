#ifndef SLAM_PHYSICS_HPP
#define SLAM_PHYSICS_HPP

#include <reactphysics3d/engine/PhysicsCommon.h>
#include <reactphysics3d/engine/PhysicsWorld.h>

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../math/mathf.hpp"
#include "../time.hpp"

namespace rp = reactphysics3d;

namespace slam::phys {

struct Physics {
  Physics(f32 timeStep = 1.0f / 60.0f);
  ~Physics();
  void Update();
  void SetGravity(CRef<math::Vec3> gravity);
  math::Vec3 GetGravity();

private:
  rp::PhysicsCommon rpCommon;
  rp::PhysicsWorld *rpWorld;
  f32 timeStep;
  f32 accumulator;
};

} // namespace slam::phys

#endif