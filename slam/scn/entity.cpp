#include "entity.hpp"

using namespace slam::scn;
using namespace slam::err;
using namespace slam::math;
using namespace slam::gfx;
using namespace slam::res;
using namespace slam;

Entity::Entity() {
  transform = Transform();
  SetID(EntityManager::Get().GetNextID());

  shader = Renderer::Get().GetShader("billboard");

  billboardIcon = Texture();

  mesh = Mesh::GeneratePlane(1, Vec2(1));

  vao = VAO();
  vbo = VBO();
  ebo = EBO();

  vao.Init();
  vao.Bind();

  vbo.Init(mesh.data.Pointer(), sizeof(sF32) * mesh.data.Size());
  ebo.Init(mesh.indices.Pointer(), sizeof(sU32) * mesh.indices.Size());

  vao.LinkAttrib(vbo, 0, 3, GL_FLOAT, 8 * sizeof(sF32), (void *)0);
  vao.LinkAttrib(vbo, 1, 2, GL_FLOAT, 8 * sizeof(sF32),
                 (void *)(3 * sizeof(sF32)));
  vao.LinkAttrib(vbo, 2, 3, GL_FLOAT, 8 * sizeof(sF32),
                 (void *)(5 * sizeof(sF32)));

  vbo.Unbind();
  vao.Unbind();
  ebo.Unbind();

  EntityManager::Get().AddEntity(this);

  drawDebugIcon = false;
}

Entity::~Entity() { Destroy(); }

void Entity::Destroy() { DESTROY(); }

void Entity::Update() {
  IS_DESTROYED();

  transform.Process();

  // if (!Engine::Get().drawEntityIcons || !drawDebugIcon)
  //   return;

  if (!drawDebugIcon)
    return;

  if (Renderer::Get().cameraPosition == nullptr ||
      Renderer::Get().cameraView == nullptr ||
      Renderer::Get().cameraProjection == nullptr) {
    return;
  }

  model = Mat4(1.0f);

  model = glm::translate(model, transform.position);

  // model *= glm::lookAt(transform.GetInheritedPosition(),
  //                      transform.GetInheritedPosition() +
  //                          *Renderer::Get().cameraPosition,
  //                      Vec3(0, 1, 0));

  model *= glm::mat4_cast(
      transform.GetInheritedRotation()); // convert to mat4x4 rotation

  model = glm::scale(model, Vec3(1.0f));

  shader->Bind();
  shader->GetUniform("view")->SetValue(*Renderer::Get().cameraView);
  shader->GetUniform("projection")->SetValue(*Renderer::Get().cameraProjection);
  shader->GetUniform("model")->SetValue(model);
  glActiveTexture(GL_TEXTURE0);
  billboardIcon.Bind();
  shader->GetUniform("diffuse_texture")->SetValue(0);

  // LOG("ip" << Mathf::ToString(transform.GetInheritedPosition()));
  vao.Bind();
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glDrawElements(GL_TRIANGLES, mesh.indices.Size(), GL_UNSIGNED_INT, 0);
  THROW_ERROR_GL(
      FATAL.Derived("GL_DRAW_ELEMENTS_FAIL (Entity Icon Billboard)"));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // LOG("drawing icon!");
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

void EntityManager::AddEntity(Entity *target) {
  if (target == nullptr) {
    THROW_ERROR(WARNING.Derived(
        "NULL_REFERENCE", "Can not add `nullptr` to the entity manager!"));
    return;
  }
  for (Entity *entity : *entities.Vector()) {
    if (entity->GetID() == target->GetID()) {
      THROW_ERROR(WARNING.Derived(
          "", "Can not add an entity twice to the entity manager!"));
      return;
    }
  }

  entities.Add(target);
}

void EntityManager::DestroyAll() {
  LOG("Destroying " << entities.Size() << " entities.");
  for (Entity *entity : *entities.Vector()) {
    entity->Destroy();
  }
}

void EntityManager::UpdateAll() {
  for (Entity *entity : *entities.Vector()) {

    entity->Update();
  }
}

// trying to draw billboards, but cant see them event when the bool is on.