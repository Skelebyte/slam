#include "rigidbody.hpp"
#include "physics.hpp"
#include <reactphysics3d/body/RigidBody.h>
#include <reactphysics3d/mathematics/Quaternion.h>
#include <reactphysics3d/mathematics/Transform.h>
#include <reactphysics3d/mathematics/Vector3.h>

using namespace slam;
using namespace slam::phys;
using namespace slam::err;
using namespace slam::math;

Rigidbody::Rigidbody() {
  rpTransform = rp::Transform(rp::Vector3(), rp::Quaternion::identity());
  rpRb = Physics::CreateRpRb(rpTransform);
  Physics::AddRigidbody(this);
}

void Rigidbody::Destroy() {
  DESTROY();
  Entity::Destroy();

  Physics::DestroyRpRb(rpRb);
}

void Rigidbody::Update() {
  IS_DESTROYED();
  transform.Process();
  // LOG(Mathf::ToString(Vec3(rpRb->getTransform().getPosition().x,
  //                          rpRb->getTransform().getPosition().y,
  //                          rpRb->getTransform().getPosition().z)));
}

rp::Transform Rigidbody::GetRpTransform() { return rpRb->getTransform(); }

rp::RigidBody *Rigidbody::GetRpRigidbody() { return rpRb; }

void Rigidbody::Sync() {
  // rpTransform.setPosition(rp::Vector3(transform.GetInheritedPosition().x,
  //                                     transform.GetInheritedPosition().y,
  //                                     transform.GetInheritedPosition().z));

  // // LOG(Mathf::ToString(Vec3(transform.GetInheritedPosition().x,
  // //                          transform.GetInheritedPosition().y,
  // //                          transform.GetInheritedPosition().z)));

  // rpTransform.setOrientation(rp::Quaternion(
  //     transform.GetInheritedRotation().x, transform.GetInheritedRotation().y,
  //     transform.GetInheritedRotation().z,
  //     transform.GetInheritedRotation().w));

  rpRb->setTransform(
      rp::Transform(rp::Vector3(transform.position.x, transform.position.y,
                                transform.position.z),
                    rpRb->getTransform().getOrientation()));
  rpRb->setLinearVelocity(rp::Vector3(0, 0, 0));
  rpRb->setAngularVelocity(rp::Vector3(0, 0, 0));
}