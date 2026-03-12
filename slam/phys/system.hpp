#ifndef SLAM_SYSTEM_HPP
#define SLAM_SYSTEM_HPP

#include "../common.hpp"
#include "../engine.hpp"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "../time.hpp"
#include "body.hpp"

namespace slam::phys {

struct CollisionData {
  CollisionData() = default;
  math::Vec3 normal;
  f32 depth;
};

struct System : public Singleton<System> {
  static Ptr<BoxBody> CreateBox(CRef<BoxShape> shape = BoxShape());
  static Ptr<SphereBody> CreateSphere(CRef<SphereShape> shape = SphereShape());
  static void RemoveBody(Ptr<Body> target);
  static bool IsSphereIntersecting(Ptr<CollisionData> data, Ptr<SphereBody> a,
                                   Ptr<SphereBody> b);
  static bool IsBoxIntersecting(Ptr<CollisionData> data, Ptr<BoxBody> a,
                                Ptr<BoxBody> b);
  static void CheckCollisions();
  static u32 GetNumberOfBodies();

private:
  List<Ptr<Body>> bodies = List<Ptr<Body>>();
};

} // namespace slam::phys

#endif