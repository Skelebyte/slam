#include "system.hpp"
#include "body.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::phys;

Body *System::CreateBox(const BoxShape &shape) {
  Body *value = new Body(1.0f, 0.1f, shape);

  Get().bodies.Add(value);

  return value;
}

Body *System::CreateSphere(const SphereShape &shape) {
  Body *value = new Body(1.0f, 0.1f, shape);

  Get().bodies.Add(value);

  return value;
}