#include "component.hpp"
#include "entity.hpp"

using namespace slam;
using namespace slam::scn;
using namespace slam::math;

Transform::Transform() {
  position = Vec3(0);
  rotation = Vec3(0, 0, 0);
  scale = Vec3(1);
}

void Transform::Process() {
  rotation.x = Mathf::Wrap(rotation.x, -360, 360);
  rotation.y = Mathf::Wrap(rotation.y, -360, 360);
  rotation.z = Mathf::Wrap(rotation.z, -360, 360);

  qRotation = Quat(rotation);
}

Vec3 Transform::Forward() const {
  Vec3 forward = Vec3(0, 0, -1);
  forward.Rotate(rotation.x, Vec3(1, 0, 0));
  forward.Rotate(rotation.y, Vec3(0, 1, 0));
  forward.Rotate(rotation.z, Vec3(0, 0, -1));

  return forward;
}

// Vec3 Transform::InheritedForward() const {
//   Vec3 forward = Vec3(0, 0, -1);
//   forward.Rotate(GetInheritedRotation().x, Vec3(1, 0, 0));
//   forward.Rotate(GetInheritedRotation().y, Vec3(0, 1, 0));
//   forward.Rotate(GetInheritedRotation().z, Vec3(0, 0, -1));

//   return forward;
// }

Vec3 Transform::Right() const {
  Vec3 right = Vec3(1, 0, 0);

  right = glm::rotate(right);

  right.Rotate(rotation.x, Vec3(1, 0, 0));
  right.Rotate(rotation.y, Vec3(0, 1, 0));
  right.Rotate(rotation.z, Vec3(0, 0, -1));
  return right;
}

// Vec3 Transform::GetInheritedPosition() const {

//   if (parent == nullptr) {
//     return position;
//   }
//   Vec3 value = Vec3();

//   Vec3 inheritedRot = parent->GetInheritedRotation();

//   Vec3 result = inheritedRot * position;

//   value = parent->GetInheritedPosition() + Vec3(result.x, result.y, result.z);

//   return value;
// }

// Vec3 Transform::GetInheritedRotation() const {
//   if (parent == nullptr) {
//     return rotation;
//   }

//   return parent->GetInheritedRotation() * rotation;
// }

/*
Quat Transform::GetInheritedRotation() const {
  if (parent == nullptr) {
    return rotation;
  }

  return parent->GetInheritedRotation() * qRotation;
}
*/

// Vec3 Transform::GetInheritedScale() const {
//   Vec3 value = scale;
//   if (parent != nullptr) {
//     value *= parent->scale;
//   }
//   return value;
// }

Component::Component() { SetID(ComponentManager::Get().GetNextID()); }

sUint ComponentManager::GetNextID() {
  nextID++;

  return nextID - 1;
}