#ifndef SLAM_RIGIDBODY_HPP
#define SLAM_RIGIDBODY_HPP

#include "../scn/entity.hpp"
#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/engine/PhysicsCommon.h>
#include <reactphysics3d/engine/PhysicsWorld.h>
namespace rp = reactphysics3d;

namespace slam::phys {
struct Rigidbody : public scn::Entity {
  Rigidbody();
  void Destroy() override;
  void Update() override;
  rp::Transform GetRpTransform();
  rp::RigidBody *GetRpRigidbody();
  void Sync();
  f32 mass = 1.0f;

protected:
  rp::Transform rpTransform;
  rp::RigidBody *rpRb;
};
} // namespace slam::phys

#endif

/* TODO: need to add box shape, sphere shape, and capsule shape, and im thinking
   theyll be entities that should be children of Rigidbody. not sure how ill
   apply rotations from physics.
*/
