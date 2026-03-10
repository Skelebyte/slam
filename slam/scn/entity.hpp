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
  bool drawDebugIcon;
  gfx::Texture billboardIcon;

private:
  gfx::Shader *shader;
  math::Mat4 model;
  gfx::VAO vao;
  gfx::VBO vbo;
  gfx::EBO ebo;
  res::Mesh mesh;
};

struct EntityManager : public Singleton<EntityManager> {
  u32 GetNextID();
  void AddEntity(Entity *target);
  void UpdateAll();
  void DestroyAll();

private:
  u32 nextID = 1;
  List<Entity *> entities;
};

} // namespace slam::scn

#endif