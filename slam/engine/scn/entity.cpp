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

  shaderBillboard = Renderer::Get().GetShader("billboard");

  billboardIcon = Texture();

  meshBillboard = Mesh::GeneratePlane(1, Vec2(1));

  vaoBillboard = VAO();
  vboBillboard = VBO();
  eboBillboard = EBO();

  vaoBillboard.Init();
  vaoBillboard.Bind();

  vboBillboard.Init(meshBillboard.data.Pointer(),
                    sizeof(f32) * meshBillboard.data.Size());
  eboBillboard.Init(meshBillboard.indices.Pointer(),
                    sizeof(u32) * meshBillboard.indices.Size());

  vaoBillboard.LinkAttrib(vboBillboard, 0, 3, GL_FLOAT, 8 * sizeof(f32),
                          (void *)0);
  vaoBillboard.LinkAttrib(vboBillboard, 1, 2, GL_FLOAT, 8 * sizeof(f32),
                          (void *)(3 * sizeof(f32)));
  vaoBillboard.LinkAttrib(vboBillboard, 2, 3, GL_FLOAT, 8 * sizeof(f32),
                          (void *)(5 * sizeof(f32)));

  vboBillboard.Unbind();
  vaoBillboard.Unbind();
  eboBillboard.Unbind();

  EntityManager::AddEntity(this);

  drawDebugIcon = false;
}

Entity::~Entity() { Destroy(); }

void Entity::Destroy() {
  // DESTROY();

  EntityManager::RemoveEntity(this);
}

void Entity::Update() {
  IS_DESTROYED();

  transform.Process();

  if (Engine::GetDrawEntityIcons() == false || drawDebugIcon == false)
    return;

  if (!drawDebugIcon)
    return;

  if (Renderer::Get().cameraTransform == nullptr ||
      Renderer::Get().cameraView == nullptr ||
      Renderer::Get().cameraProjection == nullptr) {
    return;
  }

  modelBillboard = Mat4(1.0f);

  modelBillboard = glm::translate(modelBillboard, transform.position);

  // model *= glm::lookAt(transform.GetInheritedPosition(),
  //                      transform.GetInheritedPosition() +
  //                          *Renderer::Get().cameraPosition,
  //                      Vec3(0, 1, 0));

  modelBillboard *= glm::mat4_cast(
      transform.GetInheritedRotation()); // convert to mat4x4 rotation

  modelBillboard = glm::scale(modelBillboard, Vec3(1.0f));

  shaderBillboard->Bind();
  shaderBillboard->GetUniform("view")->SetValue(*Renderer::Get().cameraView);
  shaderBillboard->GetUniform("projection")
      ->SetValue(*Renderer::Get().cameraProjection);
  shaderBillboard->GetUniform("model")->SetValue(modelBillboard);
  glActiveTexture(GL_TEXTURE0);
  billboardIcon.Bind();
  shaderBillboard->GetUniform("diffuse_texture")->SetValue(0);

  // LOG("ip" << Mathf::ToString(transform.GetInheritedPosition()));
  vaoBillboard.Bind();
  glDisable(GL_CULL_FACE);
  glDisable(GL_DEPTH_TEST);
  glDrawElements(GL_TRIANGLES, meshBillboard.indices.Size(), GL_UNSIGNED_INT,
                 0);
  THROW_ERROR_GL(
      FATAL.Derived("GL_DRAW_ELEMENTS_FAIL (Entity Icon Billboard)"));
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_CULL_FACE);

  // LOG("drawing icon!");
}

// template <typename T> T *Entity::GetComponent() {
//   for (i32 i = 0; i < this->components.Size(); i++) {
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
//   for (i32 i = 0; i < this->components.Size(); i++) {
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

u32 EntityManager::GetNextID() {
  Get().nextID++;

  return Get().nextID - 1;
}

void EntityManager::AddEntity(Ptr<Entity> target) {
  if (target == nullptr) {
    THROW_ERROR(WARNING.Derived(
        "NULL_REFERENCE", "Can not add `nullptr` to the entity manager!"));
    return;
  }
  for (Ptr<Entity> entity : *Get().entities.Vector()) {
    if (entity->GetID() == target->GetID()) {
      THROW_ERROR(WARNING.Derived(
          "", "Can not add an entity twice to the entity manager!"));
      return;
    }
  }

  Get().entities.Add(target);
}

void EntityManager::RemoveEntity(Ptr<Entity> target) {
  if (target == nullptr) {
    THROW_ERROR(WARNING.Derived(
        "NULL_REFERENCE", "Can not remove `nullptr` from the entity manager!"));
    return;
  }

  for (u32 i = 0; i < Get().entities.Size(); i++) {
    if (Get().entities[i]->GetID() == target->GetID()) {
      Get().entities.Remove(i);
      break;
    }
  }
}

void EntityManager::DestroyAll() {
  LOG("Destroying " << Get().entities.Size() << " entities!");
  for (Ptr<Entity> entity : *Get().entities.Vector()) {
    entity->Destroy();
  }
}

void EntityManager::UpdateAll() {
  for (Ptr<Entity> entity : *Get().entities.Vector()) {

    entity->Update();
  }
}

u32 EntityManager::GetNumberOfEntities() { return Get().entities.Size(); }