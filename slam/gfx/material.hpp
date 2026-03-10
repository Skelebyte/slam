#ifndef SLAM_MATERIAL_HPP
#define SLAM_MATERIAL_HPP

#include "../common.hpp"
#include "color.hpp"
#include "renderer.hpp"
#include "texture.hpp"

namespace slam::gfx {

enum FaceCullingStyle { OFF = 0, FRONT = 1, BACK = 2, BOTH = 3 };

struct Material : public Destroyable {
  Material(const str &shaderName);
  void Destroy() override;
  virtual void Bind();

protected:
  Shader *shader;
};

struct Default : public Material {
  Default();
  Default(const str &texturePath, RGB255 color);
  Default(const str &texturePath, RGB color);

  void Destroy() override;
  void Bind() override;

  Texture diffuse;
  RGB color;
  FaceCullingStyle faceCulling = FaceCullingStyle::BACK;
};

} // namespace slam::gfx

#endif
