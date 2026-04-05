#include "time.hpp"
#include "engine.hpp"

using namespace slam;

f32 Time::DeltaTime() {
  return Engine::GetDeltaTime() * Engine::GetTimeScale();
}

f32 Time::UnscaledDeltaTime() { return Engine::GetDeltaTime(); }

void Time::SetTimeScale(f32 scale) { Engine::SetTimeScale(scale); }

f32 Time::GetTimeScale() { return Engine::GetTimeScale(); }

u64 Time::MsToNs(u32 value) { return value * 1000000; }