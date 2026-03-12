#ifndef SLAM_BODY_HPP
#define SLAM_BODY_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"
#include "../scn/entity.hpp"

namespace slam::phys {

enum ShapeType {
  BOX = 0,
  SPHERE = 1,
};

struct Shape {
  virtual ~Shape() = default;
};

struct BoxShape : public Shape {
  BoxShape(const math::Vec3 &d = math::Vec3(1.0f));
  math::Vec3 dimensions;
};

struct SphereShape : public Shape {
  SphereShape(f32 r = 0.5f);
  f32 radius;
};

struct Body : public scn::Entity {
  Body(f32 mass = 1.0f, f32 bounciness = 0.1f);
  void Move(const math::Vec3 &amount);
  void MoveTo(const math::Vec3 &position);

  bool freeze;
  f32 mass;
  f32 bounciness;
  ShapeType GetShapeType() const;

protected:
  ShapeType type;
  math::Vec3 linearVelocity;
};

struct BoxBody : public Body {
  BoxBody(f32 mass = 1.0f, f32 bounciness = 0.1f, BoxShape shape = BoxShape());
  BoxShape shape;
};

struct SphereBody : public Body {
  SphereBody(f32 mass = 1.0f, f32 bounciness = 0.1f,
             SphereShape shape = SphereShape());
  SphereShape shape;
};

} // namespace slam::phys

#endif