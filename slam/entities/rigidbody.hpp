#ifndef SLAM_RIGIDBODY_HPP
#define SLAM_RIGIDBODY_HPP

#include "../common.hpp"
#include "../math/mathf.hpp"
#include "../scn/entity.hpp"
#include "../time.hpp"

using namespace slam::err;
using namespace slam::math;
using namespace slam::scn;
using namespace slam;

namespace slam::entities {
struct Rigidbody : public scn::Entity {
  Rigidbody(sF32 groundCoord = -1.0f, sF32 gravity = -9.81f) {
    this->groundCoord = groundCoord;
    this->gravity = gravity;
    frozen = false;
  }
  void Destroy() override { DESTROY(); }
  void Update() override {
    IS_DESTROYED();
    Entity::Update();

    if (frozen)
      return;

    transform.position.y += gravity * Time::DeltaTime();

    if (transform.position.y <= groundCoord - (groundCoord * transform.scale.y))
      transform.position.y = groundCoord - (groundCoord * transform.scale.y);
  }
  sF32 groundCoord;
  sF32 gravity;
  bool frozen;
};
} // namespace slam::entities

#endif