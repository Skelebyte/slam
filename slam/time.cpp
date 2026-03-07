#include "time.hpp"

using namespace slam;

sF32 Time::DeltaTime() {
  return Engine::Get().deltaTime * Engine::Get().timeScale;
}

void Time::SetTimeScale(sF32 scale) { Engine::Get().timeScale = scale; }