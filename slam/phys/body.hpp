#ifndef SLAM_BODY_HPP
#define SLAM_BODY_HPP

#include "../common.hpp"
#include "../evt/evt_sys.hpp"
#include "../math/mathf.hpp"
#include "../scn/entity.hpp"

namespace slam::phys {

enum ShapeType {
  BOX = 0,
  SPHERE = 1,
};

struct Shape {
  virtual ~Shape() = default;
  // virtual math::Vec3 GetFurthestPoint(CRef<math::Vec3> direction) = 0;
};

struct BoxShape : public Shape {
  BoxShape(CRef<math::Vec3> d = math::Vec3(1.0f));
  List<math::Vec3> GetVertices() const;
  List<math::Vec3> GetTransformedVertices(CRef<scn::Transform> transform);
  math::Vec3 dimensions;
  bool transformedUpdateReq;

protected:
  List<math::Vec3> vertices;
  List<math::Vec3> transformedVertices;
};

struct SphereShape : public Shape {
  SphereShape(f32 r = 0.5f);
  f32 radius;
};

struct Body : public scn::Entity {
  Body(f32 mass = 1.0f, f32 bounciness = 0.1f);
  void Destroy() override;
  virtual void Move(CRef<math::Vec3> amount, bool force = false);
  virtual void MoveTo(CRef<math::Vec3> position, bool force = false);
  virtual void Rotate(CRef<math::Vec3> angles) = 0;

  bool freeze;
  f32 mass;
  f32 bounciness;
  ShapeType GetShapeType() const;
  evt::Event OnCollision;

protected:
  ShapeType type;
  math::Vec3 linearVelocity;
};

struct BoxBody : public Body {
  BoxBody(f32 mass = 1.0f, f32 bounciness = 0.1f, BoxShape shape = BoxShape());
  BoxShape shape;
  void Move(CRef<math::Vec3> amount, bool force = false) override;
  void MoveTo(CRef<math::Vec3> position, bool force = false) override;
  void Rotate(CRef<math::Vec3> angles) override;
};

struct SphereBody : public Body {
  SphereBody(f32 mass = 1.0f, f32 bounciness = 0.1f,
             SphereShape shape = SphereShape());
  void Rotate(CRef<math::Vec3> angles) override {}
  SphereShape shape;
};

} // namespace slam::phys

#endif