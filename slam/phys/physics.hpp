#ifndef SLAM_PHYSICS_HPP
#define SLAM_PHYSICS_HPP

#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/engine/PhysicsCommon.h>
#include <reactphysics3d/engine/PhysicsWorld.h>

#include "../common.hpp"
#include "../engine.hpp"
#include "../err/err_sys.hpp"
#include "../math/mathf.hpp"
#include "../scn/transform.hpp"
#include "../time.hpp"
#include "rigidbody.hpp"

namespace rp = reactphysics3d;

namespace slam::phys {

struct Physics : Singleton<Physics> {
  static void Init(f32 timeStep = 1.0f / 60.0f);
  static void Shutdown();
  static void Update();
  static void SetGravity(CRef<math::Vec3> gravity);
  static math::Vec3 GetGravity();
  /**
   * @brief Create a ReactPhysics3D Rigidbody object
   *
   * @return rp::RigidBody*
   */
  static rp::RigidBody *CreateRpRb(const rp::Transform &transform);
  static void DestroyRpRb(rp::RigidBody *target);
  static void AddRigidbody(Rigidbody *target);
  static void RemoveRigidbody(Rigidbody *target);
  static u32 GetNumberOfBodies();

  rp::PhysicsCommon rpCommon;

private:
  List<Rigidbody *> bodies;
  rp::PhysicsWorld *rpWorld;
  f32 timeStep = 1.0f / 60.0f;
  f32 accumulator;
};

} // namespace slam::phys

#endif