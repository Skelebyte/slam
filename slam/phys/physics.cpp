#include "physics.hpp"
#include <reactphysics3d/mathematics/Vector2.h>

using namespace slam;
using namespace slam::phys;
using namespace slam::err;
using namespace slam::math;

Physics::Physics(f32 timeStep) {
  if (timeStep <= 0.0f) {
    THROW_ERROR(WARNING.Derived("", "timeStep can't be less than or equal to "
                                    "0! Defaulting to 1.0f / 60.0f."));
    this->timeStep = 1.0f / 60.0f;
  } else {
    this->timeStep = timeStep;
  }

  rpWorld = rpCommon.createPhysicsWorld();
  rpWorld->enableSleeping(true);
}

Physics::~Physics() { rpCommon.destroyPhysicsWorld(rpWorld); }

void Physics::Update() {
  accumulator += Time::DeltaTime();
  if (accumulator >= timeStep) {
    rpWorld->update(timeStep);
    accumulator -= timeStep;
  }
}

void Physics::SetGravity(CRef<Vec3> gravity) {
  rpWorld->setGravity(rp::Vector3(gravity.x, gravity.y, gravity.z));
}

Vec3 Physics::GetGravity() {
  return Vec3(rpWorld->getGravity().x, rpWorld->getGravity().y,
              rpWorld->getGravity().z);
}