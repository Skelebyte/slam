#include "time.hpp"
#include "engine.hpp"

using namespace slam;

float32 Time::DeltaTime() {
  return Engine::GetDeltaTime() * Engine::GetTimeScale();
}

float32 Time::UnscaledDeltaTime() { return Engine::GetDeltaTime(); }

void Time::SetTimeScale(float32 scale) { Engine::SetTimeScale(scale); }

float32 Time::GetTimeScale() { return Engine::GetTimeScale(); }

uint64 Time::MsToNs(uint32 value) { return value * 1000000; }