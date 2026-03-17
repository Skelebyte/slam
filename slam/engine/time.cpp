#include "time.hpp"

using namespace slam;

f32 Time::DeltaTime() {
  return Engine::GetDeltaTime() * Engine::GetTimeScale();
}

void Time::SetTimeScale(f32 scale) { Engine::SetTimeScale(scale); }