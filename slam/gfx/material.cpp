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
}

Default::Default(const sString &texturePath, RGB255 color)
    : Material("default") {
  diffuse = Texture(texturePath, TF_LINEAR);
  this->color = ToRGB(color);
}

Default::Default(const sString &texturePath, RGB color) : Material("default") {
  diffuse = Texture(texturePath, TF_LINEAR);
  this->color = color;
}

void Default::Destroy() {
  DESTROY();

  diffuse.Destroy();
  color = RGB(0.0f);
}

void Default::Bind() {
  IS_DESTROYED();

  glActiveTexture(GL_TEXTURE0);
  diffuse.Bind();
  shader->GetUniform("diffuse_texture")->SetValue(0);
  shader->GetUniform("color")->SetValue(color);
}