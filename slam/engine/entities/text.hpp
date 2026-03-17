#ifndef SLAM_TEXT_HPP
#define SLAM_TEXT_HPP

#include "../engine.hpp"
#include "../err/err_sys.hpp"
#include "../evt/evt_sys.hpp"
#include "../gfx/ebo.hpp"
#include "../gfx/renderer.hpp"
#include "../gfx/shader.hpp"
#include "../gfx/texture.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"
#include "../input/input.hpp"
#include "../math/mat4.hpp"
#include "../math/vec3.hpp"
#include "../res/mesh.hpp"
#include "../scn/component.hpp"
#include "../scn/entity.hpp"
#include "camera.hpp"

using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam::input;
using namespace slam;

namespace slam::entities {

struct Text : public Entity {
  Text() {}

  void Destroy() override { DESTROY(); }

  void Update() override { IS_DESTROYED(); }
};

} // namespace slam::entities

#endif