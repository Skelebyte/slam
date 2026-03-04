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

Component::Component() { SetID(ComponentManager::Get().GetNextID()); }

sUint ComponentManager::GetNextID() {
  nextID++;

  return nextID - 1;
}