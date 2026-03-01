#include "../slam/dpy/window.hpp"
#include "../slam/engine.hpp"
#include "../slam/err/err_sys.hpp"
#include "../slam/evt/evt_sys.hpp"
#include "../slam/gfx/renderer.hpp"
#include "../slam/gfx/texture.hpp"
#include "../slam/math/mat4.hpp"
#include "../slam/math/vec3.hpp"
#include "../slam/res/mesh.hpp"
#include "../slam/scn/component.hpp"
#include "../slam/scn/entity.hpp"

using namespace slam::err;
using namespace slam::evt;
using namespace slam::gfx;
using namespace slam::dpy;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::res;
using namespace slam;

struct Camera : public Component {
  Camera() {
    view = Mat4();
    projection = Mat4();
  }
  void Destroy() override {
    DESTROY();

    // deleting stuff/freeing memory
  }
  void Process() override {
    IS_DESTROYED();
    // ...
  }
  float fov = 75.0f;
  float near = 0.1f;
  float far = 1.0f;
  Mat4 view;
  Mat4 projection;
};

int main() {
  Engine::Get().Init();
  Window window = Window("Hi mum!");
  Renderer::Get().Init(&window);

  Entity cam = Entity();
  cam.AddComponent(new Camera());

  while (window.IsRunning()) {
    window.Update();
    window.Swap();

    cam.Update();

    glClearColor(0.1f, 0.2f, 0.1f, 1.0f);
  }

  cam.Destroy();

  window.Destroy();
  Renderer::Get().Shutdown();
  Engine::Get().Shutdown();
}