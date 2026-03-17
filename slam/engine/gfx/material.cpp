#include "material.hpp"

using namespace slam;
using namespace slam::gfx;

Material::Material(const str &shaderName) {
  shader = Renderer::GetShader(shaderName);
}

void Material::Destroy() {
  DESTROY();

  shader = nullptr;
}

void Material::Bind() {
  IS_DESTROYED();

  if (shader == nullptr)
    return;
}

Default::Default() : Material("default") {
  diffuse = Texture();
  color = RGB(1.0f);
  faceCulling = FaceCullingStyle::BACK;
  fog = true;
  unlit = false;
}

Default::Default(const str &texturePath, RGB255 color) : Material("default") {
  diffuse = Texture(texturePath, LINEAR);
  this->color = ToRGB(color);
  faceCulling = FaceCullingStyle::BACK;
  fog = true;
  unlit = false;
}

Default::Default(const str &texturePath, RGB color) : Material("default") {
  diffuse = Texture(texturePath, LINEAR);
  this->color = color;
  faceCulling = FaceCullingStyle::BACK;
  fog = true;
  unlit = false;
}

void Default::Destroy() {
  DESTROY();

  diffuse.Destroy();
  color = RGB(0.0f);
}

void Default::Bind() {
  IS_DESTROYED();

  if (diffuse.IsValid() == false) {
    color = RGB(1.0);
    faceCulling = FaceCullingStyle::BACK;
    unlit = true;
    fog = false;
  }

  switch (faceCulling) {
  case OFF:
    glDisable(GL_CULL_FACE);
    break;
  case FRONT:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT);
    break;
  case BACK:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);
    break;
  case BOTH:
    glEnable(GL_CULL_FACE);
    glCullFace(GL_FRONT_AND_BACK);
    break;
  }

  glActiveTexture(GL_TEXTURE0);
  diffuse.Bind();
  shader->GetUniform("diffuse_texture")->SetValue(0);
  shader->GetUniform("color")->SetValue(color);
  shader->GetUniform("affected_by_fog")->SetValue(fog);
  shader->GetUniform("unlit")->SetValue(unlit);
}