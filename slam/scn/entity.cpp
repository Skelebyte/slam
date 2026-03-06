#include "entity.hpp"

using namespace slam::scn;
using namespace slam::err;
using namespace slam;

Entity::Entity() {
  transform = Transform();
  SetID(EntityManager::Get().GetNextID());
  components = List<Component *>();
}

void Entity::Destroy() {
  DESTROY();

  for (sI32 i = 0; i < components.Size(); i++) {
    (*components[i]).Destroy();
  }
}

void Entity::Update() {
  IS_DESTROYED();

  for (sI32 i = 0; i < components.Size(); i++) {
    (*components[i]).Process();
  }
}

// template <typename T> T *Entity::GetComponent() {
//   for (sI32 i = 0; i < this->components.Size(); i++) {
//     if (typeid(this->components[i]) == typeid(T)) {
//       return (T)this->components[i];
//     }
//   }

//   THROW_ERROR(ERROR.Derived("", "Could not get component of type `" +
//                                     std::string(typeid(T).name()) +
//                                     "`. Returning `nullptr`."));

//   return nullptr;
// }

// template <typename T> bool Entity::HasComponentOfType() {
//   for (sI32 i = 0; i < this->components.Size(); i++) {
//     if (typeid(this->components[i]) == typeid(T)) {
//       return true;
//     }
//   }
//   return false;
// }

void Entity::AddComponent(Component *component) {
  if (component == nullptr) {
    THROW_ERROR(ERROR.Derived("NULL_REFERENCE",
                              "The component you are trying to add is NULL!"));
    return;
  }

  component->attachedEntityID = GetID();
  component->transform = &transform;

  this->components.Add(component);
}

void Entity::RemoveComponent(Component *component) {
  bool foundComp = false;
  sI32 compIndex = 0;
  for (sI32 i = 0; i < components.Size(); i++) {
    if ((*components[i]).GetID() == component->GetID()) {
      foundComp = true;
      compIndex = i;
      break;
    }
  }

  if (foundComp == false) {
    THROW_ERROR(
        WARNING.Derived("", "This entity doesn't have a component with ID: " +
                                std::to_string(component->GetID()) + "!"));
    return;
  }

  components[compIndex]->attachedEntityID = 0;
  components[compIndex]->transform = nullptr;
  components.Remove(compIndex);
}

sU32 Entity::ComponentAmount() { return components.Size(); }

void Entity::MakeChildOf(Entity *entity) {
  if (entity == nullptr) {
    transform.parent = nullptr;
    return;
  }

  transform.parent = &entity->transform;
}

sU32 EntityManager::GetNextID() {
  nextID++;

  return nextID - 1;
}