#include "evt.hpp"

using namespace slam::evt;

Event::Event(const sString &name) {
  this->name = name;
  listeners = List<std::function<void()>>();
}

void Event::Invoke() {
  IS_DESTROYED();

  for (sU32 i = 0; i < listeners.Size(); i++) {
    listeners[i]();
  }
}

void Event::AddListener(const std::function<void()> &listener) {
  IS_DESTROYED();

  listeners.Add(listener);
}

void Event::Destroy() {
  DESTROY();

  listeners.Clear();
}

void Event::operator+=(const std::function<void()> &listener) {
  IS_DESTROYED();

  AddListener(listener);
}