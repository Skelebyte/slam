#ifndef SLAM_TEXTURE_HPP
#define SLAM_TEXTURE_HPP

#include "../../third_party/stb/stb_image.h"
#include "../common.hpp"
#include "../err/err_sys.hpp"
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
  void LoadFromData(uchar *data, uint32 channels, uint32 width, uint32 height,
                    TextureFilter filter = NEAREST);
  static uchar *CustomTexture(uint32 width, uint32 height, uint32 r1, uint32 g1,
                              uint32 b1, uint32 r2, uint32 g2, uint32 b2);
  void Bind();
  void Unbind();
  bool IsValid() const;

private:
  bool isValid;
};

} // namespace slam::gfx

#endif
