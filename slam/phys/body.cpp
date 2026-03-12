#include "body.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::phys;

BoxShape::BoxShape(const Vec3 &d) { dimensions = d; }

SphereShape::SphereShape(f32 r) { radius = r; }

Body::Body(f32 mass, f32 bounciness) {
  this->mass = mass;
  this->bounciness = Mathf::Clamp(bounciness, 0.0f, 5.0f);
  freeze = false;
  linearVelocity = Vec3(0.0f);
}

void Body::Move(const Vec3 &amount) {
  if (freeze)
    return;
  transform.position += amount;
}

void Body::MoveTo(const Vec3 &position) { transform.position = position; }

ShapeType Body::GetShapeType() const { return type; }

BoxBody::BoxBody(f32 mass, f32 bouncienss, BoxShape shape)
    : Body(mass, bouncienss) {
  this->shape = shape;
  this->type = BOX;
}

SphereBody::SphereBody(f32 mass, f32 bouncienss, SphereShape shape)
    : Body(mass, bouncienss) {
  this->shape = shape;
  this->type = SPHERE;
}