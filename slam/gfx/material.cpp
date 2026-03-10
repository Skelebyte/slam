#include "material.hpp"

using namespace slam;
using namespace slam::gfx;

Material::Material(const sString &shaderName) {
  shader = Renderer::Get().GetShader(shaderName);
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
}

Default::Default(const sString &texturePath, RGB255 color)
    : Material("default") {
  diffuse = Texture(texturePath, LINEAR);
  this->color = ToRGB(color);
  faceCulling = FaceCullingStyle::BACK;
}

Default::Default(const sString &texturePath, RGB color) : Material("default") {
  diffuse = Texture(texturePath, LINEAR);
  this->color = color;
  faceCulling = FaceCullingStyle::BACK;
}

void Default::Destroy() {
  DESTROY();

  diffuse.Destroy();
  color = RGB(0.0f);
}

void Default::Bind() {
  IS_DESTROYED();

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
}