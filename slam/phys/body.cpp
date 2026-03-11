#include "body.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::phys;

BoxShape::BoxShape(const Vec3 &d) { dimensions = d; }

SphereShape::SphereShape(f32 r) { radius = r; }

Body::Body(f32 mass, f32 bounciness, const Shape &shape) {
  this->mass = mass;
  this->bounciness = Mathf::Clamp(bounciness, 0.0f, 5.0f);
  this->shape = shape;
  freeze = false;
  linearVelocity = Vec3(0.0f);
}