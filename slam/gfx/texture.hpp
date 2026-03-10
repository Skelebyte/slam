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
  Texture(const sString &path, TextureFilter filter = NEAREST);
  void Destroy() override;
  void TextureFallback();
  void LoadFromData(sU8 *data, sU32 channels, sU32 width, sU32 height,
                    TextureFilter filter = NEAREST);
  static sU8 *CustomTexture(sU32 width, sU32 height, sU32 r1, sU32 g1, sU32 b1,
                            sU32 r2, sU32 g2, sU32 b2);
  void Bind();
  void Unbind();
};

} // namespace slam::gfx

#endif
