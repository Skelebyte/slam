#include "component.hpp"
#include "entity.hpp"

using namespace slam;
using namespace slam::scn;
using namespace slam::math;

Transform::Transform() {
  position = Vec3(0);
  rotation = Vec3(0);
  scale = Vec3(1);
}

void Transform::Process() {
  if (rotation.x > 360)
    rotation.x -= 360;
  if (rotation.x < 0)
    rotation.x += 360;

  if (rotation.y > 360)
    rotation.y -= 360;
  if (rotation.y < 0)
    rotation.y += 360;

  if (rotation.z > 360)
    rotation.z -= 360;
  if (rotation.z < 0)
    rotation.z += 360;
}

Vec3 Transform::Forward() const {
  Vec3 forward = Vec3(0, 0, -1);
  forward.Rotate(rotation.x, Vec3(1, 0, 0));
  forward.Rotate(rotation.y, Vec3(0, 1, 0));
  forward.Rotate(rotation.z, Vec3(0, 0, -1));

  return forward;
}

Vec3 Transform::InheritedForward() const {
  Vec3 forward = Vec3(0, 0, -1);
  forward.Rotate(GetInheritedRotation().x, Vec3(1, 0, 0));
  forward.Rotate(GetInheritedRotation().y, Vec3(0, 1, 0));
  forward.Rotate(GetInheritedRotation().z, Vec3(0, 0, -1));

  return forward;
}

Vec3 Transform::Right() const {
  Vec3 right = Vec3(1, 0, 0);
  right.Rotate(rotation.x, Vec3(1, 0, 0));
  right.Rotate(rotation.y, Vec3(0, 1, 0));
  right.Rotate(rotation.z, Vec3(0, 0, -1));
  return right;
}

Vec3 Transform::GetInheritedPosition() const {

  if (parent == nullptr) {
    return position;
  }
  Vec3 value = Vec3();

  Quat inheritedRot = Quat::FromEuler(parent->GetInheritedRotation());

  Quat result = inheritedRot * position;

  value = parent->GetInheritedPosition() + Vec3(result.x, result.y, result.z);

  return value;
}

Vec3 Transform::GetInheritedRotation() const {
  if (parent == nullptr) {
    return rotation;
  }

  Quat parentRotation = Quat::FromEuler(parent->GetInheritedRotation());
  Quat thisRotation = Quat::FromEuler(rotation);
  Quat newRotation = thisRotation * parentRotation;

  return newRotation.ToEuler();
}

Vec3 Transform::GetInheritedScale() const {
  Vec3 value = scale;
  if (parent != nullptr) {
    value *= parent->scale;
  }
  return value;
}

Component::Component() { SetID(ComponentManager::Get().GetNextID()); }

sUint ComponentManager::GetNextID() {
  nextID++;

  return nextID - 1;
}