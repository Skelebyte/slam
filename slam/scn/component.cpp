#include "component.hpp"
#include "entity.hpp"

using namespace slam;
using namespace slam::scn;

Component::Component() { SetID(ComponentManager::Get().GetNextID()); }

sUint ComponentManager::GetNextID() {
  nextID++;

  return nextID - 1;
}