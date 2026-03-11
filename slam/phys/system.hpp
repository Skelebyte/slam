#ifndef SLAM_SYSTEM_HPP
#define SLAM_SYSTEM_HPP

#include "../common.hpp"
#include "../list.hpp"
#include "../math/mathf.hpp"
#include "body.hpp"

namespace slam::phys {

struct System : public Singleton<System> {
  static Body *CreateBox(const BoxShape &shape = BoxShape());
  static Body *CreateSphere(const SphereShape &shape = SphereShape());

private:
  List<Body *> bodies = List<Body *>();
};

} // namespace slam::phys

#endif