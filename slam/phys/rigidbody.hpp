#ifndef SLAM_RIGIDBODY_HPP
#define SLAM_RIGIDBODY_HPP

#include "../scn/entity.hpp"

namespace slam::phys {
struct Rigidbody : public scn::Entity {
  Rigidbody();
  void Destroy() override;
  void Update() override;
};
} // namespace slam::phys

#endif

/* TODO: need to add box shape and sphere shape, and im thinking theyll be
   entities that should be children of Rigidbody. not sure how ill apply
   rotations from physics.

*/
