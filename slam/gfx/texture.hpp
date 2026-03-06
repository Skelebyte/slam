#ifndef SLAM_TEXTURE_HPP
#define SLAM_TEXTURE_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/glad/glad.h"
#include "../ext/stb/stb_image.h"
#include "../util/file.hpp"

namespace slam::gfx {

enum TextureFilter {
  TF_LINEAR = 0,
  TF_NEAREST = 1,
};

struct Texture : public Destroyable, public ID {
  Texture();
  Texture(const sString &path, TextureFilter filter = TF_NEAREST);
  void Destroy() override;
  void TextureFallback();
  void LoadFromData(sUchar *data, sUint channels, sUint width, sUint height,
                    TextureFilter filter = TF_NEAREST);
  static sUchar *CustomTexture(sUint width, sUint height, sUint r1, sUint g1,
                               sUint b1, sUint r2, sUint g2, sUint b2);
  void Bind();
  void Unbind();
};

} // namespace slam::gfx

#endif
