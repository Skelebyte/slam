#include "body.hpp"
#include "system.hpp"

using namespace slam;
using namespace slam::math;
using namespace slam::scn;
using namespace slam::phys;

BoxShape::BoxShape(CRef<Vec3> d) {
  dimensions = d;
  vertices = List<Vec3>();

  Vec3 pXpYpZ = Vec3(d.x / 2.0f, d.y / 2.0f, d.z / 2.0f);   // +x +y +z
  Vec3 pXmYpZ = Vec3(d.x / 2.0f, -d.y / 2.0f, d.z / 2.0f);  // +x -y +z
  Vec3 mXmYpZ = Vec3(-d.x / 2.0f, -d.y / 2.0f, d.z / 2.0f); // -x -y +z
  Vec3 mXpYpZ = Vec3(-d.x / 2.0f, d.y / 2.0f, d.z / 2.0f);  // -x +y +z

  Vec3 pXpYmZ = Vec3(d.x / 2.0f, d.y / 2.0f, -d.z / 2.0f);   // +x +y -z
  Vec3 pXmYmZ = Vec3(d.x / 2.0f, -d.y / 2.0f, -d.z / 2.0f);  // +x -y -z
  Vec3 mXmYmZ = Vec3(-d.x / 2.0f, -d.y / 2.0f, -d.z / 2.0f); // -x -y -z
  Vec3 mXpYmZ = Vec3(-d.x / 2.0f, d.y / 2.0f, -d.z / 2.0f);  // -x +y -z

  vertices.Add(pXpYpZ);
  vertices.Add(pXmYpZ);
  vertices.Add(mXmYpZ);
  vertices.Add(mXpYpZ);

  vertices.Add(pXpYmZ);
  vertices.Add(pXmYmZ);
  vertices.Add(mXmYmZ);
  vertices.Add(mXpYmZ);

  transformedUpdateReq = true;
}

List<Vec3> BoxShape::GetVertices() const { return vertices; }

List<Vec3> BoxShape::GetTransformedVertices(CRef<Transform> transform) {
  Vec3 euler = glm::eulerAngles(transform.GetInheritedRotation());
  if (transformedUpdateReq) { // FIXME: XYZ order may be wrong, if it is try
                              // YXZ, also, position and scale may not be added.
    for (u32 i = 0; i < transformedVertices.Size(); i++) {
      transformedVertices[i] =
          Mathf::RotateX(transformedVertices[i], Mathf::ToDegrees(euler.x));
      transformedVertices[i] =
          Mathf::RotateY(transformedVertices[i], Mathf::ToDegrees(euler.y));
      transformedVertices[i] =
          Mathf::RotateZ(transformedVertices[i], Mathf::ToDegrees(euler.z));
    }
  }

  transformedUpdateReq = false;

  return transformedVertices;
}

SphereShape::SphereShape(f32 r) { radius = r; }

Body::Body(f32 mass, f32 bounciness) {
  this->mass = mass;
  this->bounciness = Mathf::Clamp(bounciness, 0.0f, 5.0f);
  freeze = false;
  linearVelocity = Vec3(0.0f);
}

void Body::Destroy() {
  DESTROY();
  Entity::Destroy();
  System::RemoveBody(this);
}

void Body::Move(CRef<Vec3> amount, bool force) {
  if (freeze && !force)
    return;
  transform.position += amount;
}

void Body::MoveTo(CRef<Vec3> position, bool force) {
  if (freeze && !force)
    return;
  transform.position = position;
}

ShapeType Body::GetShapeType() const { return type; }

BoxBody::BoxBody(f32 mass, f32 bouncienss, BoxShape shape)
    : Body(mass, bouncienss) {
  this->shape = shape;
  this->type = BOX;
}

void BoxBody::Move(CRef<Vec3> amount, bool force) {
  if (freeze && !force)
    return;
  transform.position += amount;
  shape.transformedUpdateReq = true;
}

void BoxBody::MoveTo(CRef<Vec3> position, bool force) {
  if (freeze && !force)
    return;
  transform.position = position;
  shape.transformedUpdateReq = true;
}

void BoxBody::Rotate(CRef<Vec3> angles) {
  transform.rotation += angles;
  shape.transformedUpdateReq = true;
}

SphereBody::SphereBody(f32 mass, f32 bouncienss, SphereShape shape)
    : Body(mass, bouncienss) {
  this->shape = shape;
  this->type = SPHERE;
}