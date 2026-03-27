#ifndef SLAM_SLAM_HPP
#define SLAM_SLAM_HPP

#include "engine/dpy/window.hpp"
#include "engine/engine.hpp"
#include "engine/entities/camera.hpp"
#include "engine/entities/line.hpp"
#include "engine/entities/mesh_renderer.hpp"
#include "engine/err/err_sys.hpp"
#include "engine/evt/evt_sys.hpp"
#include "engine/gfx/ebo.hpp"
#include "engine/gfx/renderer.hpp"
#include "engine/gfx/shader.hpp"
#include "engine/gfx/texture.hpp"
#include "engine/gfx/vao.hpp"
#include "engine/gfx/vbo.hpp"
#include "engine/input/input.hpp"
#include "engine/math/mathf.hpp"
#include "engine/res/mesh.hpp"
#include "engine/scn/entity.hpp"
#include "engine/time.hpp"
#include "engine/ui/element.hpp"
#include "engine/ui/ui_context.hpp"
#include "third_party/imgui/imgui.h"
#include "third_party/imgui/imgui_impl_opengl3.h"
#include "third_party/imgui/imgui_impl_sdl3.h"

#ifdef SLAM_USING_NAMESPACES
using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam::input;
using namespace slam::entities;
using namespace slam::ui;
// using namespace slam::phys;
using namespace slam;
#endif

#endif