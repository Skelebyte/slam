#include "time.hpp"

using namespace slam;

f32 Time::DeltaTime() {
  return Engine::Get().deltaTime * Engine::Get().timeScale;
}

void Time::SetTimeScale(f32 scale) { Engine::Get().timeScale = scale; }