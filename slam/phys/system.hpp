#ifndef SLAM_SYSTEM_HPP
#define SLAM_SYSTEM_HPP

#include "../common.hpp"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "body.hpp"

namespace slam::phys {

struct CollisionData {
  CollisionData() = default;
  math::Vec3 normal;
  f32 depth;
};

struct System : public Singleton<System> {
  static BoxBody *CreateBox(const BoxShape &shape = BoxShape());
  static SphereBody *CreateSphere(const SphereShape &shape = SphereShape());
  static bool IsSphereIntersecting(CollisionData *data, SphereBody *a,
                                   SphereBody *b);
  static void CheckCollisions();

private:
  List<Body *> bodies = List<Body *>();
};

} // namespace slam::phys

#endif