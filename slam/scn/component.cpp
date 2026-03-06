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
  rotation.x = Mathf::Wrap(rotation.x, -360, 360);
  rotation.y = Mathf::Wrap(rotation.y, -360, 360);
  rotation.z = Mathf::Wrap(rotation.z, -360, 360);

  // qRotation = Quat(rotation);
}

Vec3 Transform::Forward() const {
  Vec3 forward = Vec3(0, 0, -1);

  forward = Mathf::RotateX(forward, rotation.x);
  forward = Mathf::RotateY(forward, rotation.y);
  forward = Mathf::RotateZ(forward, rotation.z);

  return forward;
}

Vec3 Transform::InheritedForward() const {
  // Vec3 forward = Vec3(0, 0, -1);

  // forward = Mathf::RotateX(forward, GetInheritedRotation().x);
  // forward = Mathf::RotateY(forward, GetInheritedRotation().y);
  // forward = Mathf::RotateZ(forward, GetInheritedRotation().z);

  return GetInheritedRotation() * Vec3(0, 0, -1);
}

Vec3 Transform::Right() const {
  // Vec3 right = Vec3(1, 0, 0);

  // right = Mathf::RotateX(right, rotation.x);
  // right = Mathf::RotateY(right, rotation.y);
  // right = Mathf::RotateZ(right, rotation.z);
  return GetInheritedRotation() * Vec3(1, 0, 0);
}

Vec3 Transform::GetInheritedPosition() const {
  if (parent == nullptr) {
    return position;
  }

  Vec3 result = parent->GetInheritedPosition() +
                (parent->GetInheritedRotation() * position);

  return result;
}

Quat Transform::GetInheritedRotation() const {
  Quat local = Quat(glm::radians(rotation));
  if (parent == nullptr) {
    return local;
  }

  return parent->GetInheritedRotation() * local;
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