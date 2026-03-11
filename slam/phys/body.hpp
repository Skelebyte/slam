#ifndef SLAM_BODY_HPP
#define SLAM_BODY_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"
#include "../scn/entity.hpp"

namespace slam::phys {

struct Shape {};

struct BoxShape : public Shape {
  BoxShape(const math::Vec3 &d = math::Vec3(1.0f));
  math::Vec3 dimensions;
};

struct SphereShape : public Shape {
  SphereShape(f32 r = 0.5f);
  f32 radius;
};

struct Body : public scn::Entity {
  Body(f32 mass = 1.0f, f32 bounciness = 0.1f, const Shape &shape = BoxShape());

  bool freeze;

  f32 mass;
  f32 bounciness;

  Shape shape;

private:
  math::Vec3 linearVelocity;
};

} // namespace slam::phys

#endif