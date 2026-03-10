#ifndef SLAM_TEXTURE_HPP
#define SLAM_TEXTURE_HPP

#include "../common.hpp"
#include "../err/err_sys.hpp"
#include "../ext/glad/glad.h"
#include "../ext/stb/stb_image.h"
#include "../util/file.hpp"

namespace slam::gfx {

enum TextureFilter {
  LINEAR = 0,
  NEAREST = 1,
};

struct Texture : public Destroyable, public ID {
  Texture();
  Texture(const str &path, TextureFilter filter = NEAREST);
  void Destroy() override;
  void TextureFallback();
  void LoadFromData(u8 *data, u32 channels, u32 width, u32 height,
                    TextureFilter filter = NEAREST);
  static u8 *CustomTexture(u32 width, u32 height, u32 r1, u32 g1, u32 b1,
                           u32 r2, u32 g2, u32 b2);
  void Bind();
  void Unbind();
};

} // namespace slam::gfx

#endif
