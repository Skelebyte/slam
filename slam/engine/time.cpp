#include "time.hpp"
#include "engine.hpp"

using namespace slam;

f32 Time::DeltaTime() {
  return Engine::GetDeltaTime() * Engine::GetTimeScale();
}

void Time::SetTimeScale(f32 scale) { Engine::SetTimeScale(scale); }

u64 Time::MsToNs(u32 value) { return value * 1000000; }