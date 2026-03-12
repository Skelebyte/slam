#include "system.hpp"
#include "body.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::phys;
using namespace slam::err;

Ptr<BoxBody> System::CreateBox(CRef<BoxShape> shape) {
  Ptr<BoxBody> value = new BoxBody(1.0f, 0.1f, shape);

  Get().bodies.Add(value);

  return value;
}

Ptr<SphereBody> System::CreateSphere(CRef<SphereShape> shape) {
  Ptr<SphereBody> value = new SphereBody(1.0f, 0.1f, shape);

  Get().bodies.Add(value);

  return value;
}

void System::RemoveBody(Ptr<Body> target) {
  Get().bodies.RemoveElement(target);
}

bool System::IsSphereIntersecting(Ptr<CollisionData> data, Ptr<SphereBody> a,
                                  Ptr<SphereBody> b) {

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

  f32 aLargestAxis = Mathf::Abs(a->transform.scale.x);
  if (Mathf::Abs(a->transform.scale.y) > aLargestAxis)
    aLargestAxis = Mathf::Abs(a->transform.scale.y);
  if (Mathf::Abs(a->transform.scale.z) > aLargestAxis)
    aLargestAxis = Mathf::Abs(a->transform.scale.z);

  f32 bLargestAxis = Mathf::Abs(b->transform.scale.x);
  if (Mathf::Abs(b->transform.scale.y) > bLargestAxis)
    bLargestAxis = Mathf::Abs(b->transform.scale.y);
  if (Mathf::Abs(b->transform.scale.z) > bLargestAxis)
    bLargestAxis = Mathf::Abs(b->transform.scale.z);

  f32 totalRadius =
      (a->shape.radius * aLargestAxis) + (b->shape.radius * bLargestAxis);

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

  a->OnCollision.Invoke();
  b->OnCollision.Invoke();

  return true;
}

bool System::IsBoxIntersecting(Ptr<CollisionData> data, Ptr<BoxBody> a,
                               Ptr<BoxBody> b) {

  return false;
}

void System::CheckCollisions() {
  if (!Engine::IsProcessFrame())
    return;

  for (Ptr<Body> body : *Get().bodies.Vector()) {
    body->Move(Vec3(0, -9.81f * Time::DeltaTime(), 0));

    if (body->transform.GetInheritedPosition().y < 0.0f) {
      body->MoveTo(Vec3(body->transform.GetInheritedPosition().x, 0,
                        body->transform.GetInheritedPosition().z));
    }
  }

  for (u32 i = 0; i < Get().bodies.Size(); i++) {
    Ptr<Body> a = Get().bodies[i];
    for (u32 j = i + 1; j < Get().bodies.Size(); j++) {
      Ptr<Body> b = Get().bodies[j];
      if (a->GetShapeType() == SPHERE && b->GetShapeType() == SPHERE) {
        CollisionData data;
        if (IsSphereIntersecting(&data, (Ptr<SphereBody>)a,
                                 (Ptr<SphereBody>)b)) {
          a->Move(-data.normal * data.depth / 2.0f * a->bounciness);
          b->Move(data.normal * data.depth / 2.0f * b->bounciness);

          // a->Move(-data.normal * data.depth / 2.0f);
          // b->Move(data.normal * data.depth / 2.0f);
        }
      }
    }
  }
}

u32 System::GetNumberOfBodies() { return Get().bodies.Size(); }