#ifndef SLAM_ENTITY_HPP
#define SLAM_ENTITY_HPP

#include "../common.hpp"
#include "../engine.hpp"
#include "../err/err_sys.hpp"
#include "../gfx/ebo.hpp"
#include "../gfx/renderer.hpp"
#include "../gfx/texture.hpp"
#include "../gfx/vao.hpp"
#include "../gfx/vbo.hpp"
#include "../list.hpp"
#include "../res/mesh.hpp"
#include "transform.hpp"

namespace slam::scn {

struct Entity : public ID, public Destroyable {
  Entity();
  ~Entity();
  void Destroy() override;
  virtual void Update();

  void MakeChildOf(Entity *entity);

  Transform transform;
};

struct EntityManager : public Singleton<EntityManager> {
  static u32 GetNextID();
  static void AddEntity(Ptr<Entity> target);
  static void RemoveEntity(Ptr<Entity> target);
  static void UpdateAll();
  static void DestroyAll();
  static u32 GetNumberOfEntities();

private:
  u32 nextID = 1;
  List<Entity *> entities;
};

} // namespace slam::scn

#endif