#ifndef SLAM_ENTITY_HPP
#define SLAM_ENTITY_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../list.hpp"
#include "component.hpp"

namespace slam::scn {

struct Entity : public ID, public Destroyable {
  Entity();
  void Destroy() override;
  virtual void Update();
  template <typename T> T *GetComponent() {
    for (int i = 0; i < this->components.Size(); i++) {
      if (typeid(this->components[i]) == typeid(T)) {
        return (T)this->components[i];
      }
    }

    err::ErrorSystem::THROW_ERROR(err::ERROR.Derived(
        "", "Could not get component of type `" +
                std::string(typeid(T).name()) + "`. Returning `nullptr`."));

    return nullptr;
  }

  template <typename T> bool HasComponentOfType() {
    for (int i = 0; i < this->components.Size(); i++) {
      if (dynamic_cast<T *>(this->components[i]) != nullptr) {
        return true;
      }
    }
    return false;
  }

  void AddComponent(Component *component);
  void RemoveComponent(Component *component);
  sUint ComponentAmount();

  Transform transform;

protected:
  List<Component *> components;
};

struct EntityManager : public Singleton<EntityManager> {
  sUint GetNextID();

private:
  sUint nextID = 1;
};

} // namespace slam::scn

#endif