#include "system.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::phys;
using namespace slam::err;

BoxBody *System::CreateBox(const BoxShape &shape) {
  BoxBody *value = new BoxBody(1.0f, 0.1f, shape);

  Get().bodies.Add(value);

  return value;
}

SphereBody *System::CreateSphere(const SphereShape &shape) {
  SphereBody *value = new SphereBody(1.0f, 0.1f, shape);

  Get().bodies.Add(value);

  return value;
}

bool System::IsSphereIntersecting(CollisionData *data, SphereBody *a,
                                  SphereBody *b) {

  if (a->GetShapeType() != SPHERE) {
    THROW_ERROR(WARNING.Derived("", "a is not a Sphere shape!"));
    return false;
  }
  if (b->GetShapeType() != SPHERE) {
    THROW_ERROR(WARNING.Derived("", "b is not a Sphere shape!"));
    return false;
  }

  f32 distance = Mathf::Distance(a->transform.GetInheritedPosition(),
                                 b->transform.GetInheritedPosition());

  f32 totalRadius = a->shape.radius + b->shape.radius;

  if (distance >= totalRadius) {
    return false;
  }

  data->normal = Mathf::Normalized(
      b->transform.GetInheritedPosition() -
      a->transform
          .GetInheritedPosition()); // TODO: do a - b so the normal is the
                                    // direction for a. get direction for b by
                                    // just doing -normal

  data->depth = totalRadius - distance;

  return true;
}

void System::CheckCollisions() {
  for (u32 i = 0; i < Get().bodies.Size(); i++) {
    Body *a = Get().bodies[i];
    for (u32 j = i + 1; j < Get().bodies.Size(); j++) {
      Body *b = Get().bodies[j];
      if (a->GetShapeType() == SPHERE && b->GetShapeType() == SPHERE) {
        CollisionData data;
        if (IsSphereIntersecting(&data, (SphereBody *)a, (SphereBody *)b)) {
          a->Move(-data.normal * data.depth / 2.0f);
          b->Move(data.normal * data.depth / 2.0f);
        }
      }
    }
  }
}