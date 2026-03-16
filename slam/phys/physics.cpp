#include "physics.hpp"
#include "rigidbody.hpp"
#include <reactphysics3d/mathematics/Quaternion.h>
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/mathematics/Vector3.h>

using namespace slam;
using namespace slam::phys;
using namespace slam::err;
using namespace slam::math;
using namespace slam::scn;

void Physics::Init(f32 timeStep) {
  if (timeStep <= 0.0f) {
    THROW_ERROR(WARNING.Derived("", "timeStep can't be less than or equal to "
                                    "0! Defaulting to 1.0f / 60.0f."));
    Get().timeStep = 1.0f / 60.0f;
  } else {
    Get().timeStep = timeStep;
  }

  Get().rpWorld = Get().rpCommon.createPhysicsWorld();
  // Get().rpWorld->enableSleeping(true);
}

void Physics::Shutdown() { Get().rpCommon.destroyPhysicsWorld(Get().rpWorld); }

void Physics::Update() {
  if (!Engine::IsProcessFrame())
    return;

  Get().accumulator += Time::DeltaTime();
  if (Get().accumulator >= Get().timeStep) {
    Get().rpWorld->update(Get().timeStep);
    Get().accumulator -= Get().timeStep;
  }

  for (u32 i = 0; i < Get().bodies.Size(); i++) {
    Get().bodies[i]->transform.position =
        Vec3(Get().bodies[i]->GetRpRigidbody()->getTransform().getPosition().x,
             Get().bodies[i]->GetRpRigidbody()->getTransform().getPosition().y,
             Get().bodies[i]->GetRpRigidbody()->getTransform().getPosition().z);

    Quat rpRot = Quat(
        Get().bodies[i]->GetRpRigidbody()->getTransform().getOrientation().w,
        Get().bodies[i]->GetRpRigidbody()->getTransform().getOrientation().x,
        Get().bodies[i]->GetRpRigidbody()->getTransform().getOrientation().y,
        Get().bodies[i]->GetRpRigidbody()->getTransform().getOrientation().z);

    Get().bodies[i]->transform.rotation = Mathf::ToEuler(rpRot);
  }
}

void Physics::SetGravity(CRef<Vec3> gravity) {
  Get().rpWorld->setGravity(rp::Vector3(gravity.x, gravity.y, gravity.z));
}

Vec3 Physics::GetGravity() {
  return Vec3(Get().rpWorld->getGravity().x, Get().rpWorld->getGravity().y,
              Get().rpWorld->getGravity().z);
}

rp::RigidBody *Physics::CreateRpRb(const rp::Transform &transform) {
  return Get().rpWorld->createRigidBody(transform);
}

void Physics::DestroyRpRb(rp::RigidBody *target) {
  Get().rpWorld->destroyRigidBody(target);
}

void Physics::AddRigidbody(Rigidbody *target) {
  for (u32 i = 0; i < Get().bodies.Size(); i++) {
    if (target->GetID() == Get().bodies[i]->GetID())
      return;
  }

  Get().bodies.Add(target);
}

u32 Physics::GetNumberOfBodies() { return Get().bodies.Size(); }