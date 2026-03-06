#define STB_IMAGE_IMPLEMENTATION
#include "texture.hpp"

using namespace slam;
using namespace slam::gfx;
using namespace slam::err;
using namespace slam::util;

Texture::Texture() {
  sU8 *data = Texture::CustomTexture(4, 4, 255, 255, 255, 200, 200, 200);

  LoadFromData(data, 3, 4, 4);
}

Texture::Texture(const sString &path, TextureFilter filter) {
  if (path.empty() == true) {
    sU8 *data = Texture::CustomTexture(4, 4, 255, 255, 255, 200, 200, 200);

    LoadFromData(data, 3, 4, 4);
  }

  if (File::Exists(path) == false) {
    THROW_ERROR(WARNING.Derived(
        "", "File " + path + " does not exist! Loading missing texture."));

    TextureFallback();
    return;
  }

  stbi_set_flip_vertically_on_load(1);

  sI32 width, height, channels;

  sU8 *data;

  data = stbi_load(path.c_str(), &width, &height, &channels, 0);
  if (!data) {
    THROW_ERROR(WARNING.Derived("", "Failed to load texture " + path +
                                        ". Loading missing texture."));
    TextureFallback();
    return;
  }

  LoadFromData(data, channels, width, height, filter);
}

void Texture::Destroy() {
  DESTROY();

  glDeleteTextures(1, GetID_Ptr());
}

void Texture::TextureFallback() {
  sU8 *data = Texture::CustomTexture(4, 4, 255, 0, 255, 0, 0, 0);

  LoadFromData(data, 3, 4, 4);
}

void Texture::LoadFromData(sU8 *data, sU32 channels, sU32 width, sU32 height,
                           TextureFilter filter) {
  if (!data) {
    THROW_ERROR(ERROR.Derived("", "The `data` parameter is not valid!"));
    return;
  }

  glGenTextures(1, GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("", "Failed to generate texture."));

  glBindTexture(GL_TEXTURE_2D, *GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("", "Failed to bind texture."));

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  THROW_ERROR_GL(
      FATAL.Derived("", "Setting GL_TEXTURE_WRAP_S parameter failed."));

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  THROW_ERROR_GL(
      FATAL.Derived("", " Setting GL_TEXTURE_WRAP_T parameter failed."));

  if (filter == TF_NEAREST) {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    THROW_ERROR_GL(FATAL.Derived("", "Setting MIN_FILTER failed."));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    THROW_ERROR_GL(FATAL.Derived("", "Setting MAG_FILTER failed."));
  } else {
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    THROW_ERROR_GL(FATAL.Derived("", "Setting MIN_FILTER failed."));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    THROW_ERROR_GL(FATAL.Derived("", "Setting MAG_FILTER failed."));
  }

  sU32 format = channels == 4 ? GL_RGBA : GL_RGB;

  glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format,
               GL_UNSIGNED_BYTE, data);
  THROW_ERROR_GL(FATAL.Derived("", "Failed to set texture data."));

  glGenerateMipmap(GL_TEXTURE_2D);
  THROW_ERROR_GL(FATAL.Derived("", "Failed to generate mipmap."));

  free(data);
}

sU8 *Texture::CustomTexture(sU32 width, sU32 height, sU32 r1, sU32 g1, sU32 b1,
                            sU32 r2, sU32 g2, sU32 b2) {
  sU8 *data = (sU8 *)malloc(width * height * 3);
  for (sI32 y = 0; y < height; y++) {
    for (sI32 x = 0; x < width; x++) {
      sF32 t = (sF32)x / width;
      sF32 s = (sF32)y / height;

      sI32 index = (y * width + x) * 3;
      if (((sI32)(s * height) + (sI32)(t * width)) % 2 == 0) {
        data[index] = r1;
        data[index + 1] = g1;
        data[index + 2] = b1;
      } else {
        data[index] = r2;
        data[index + 1] = g2;
        data[index + 2] = b2;
      }
    }
  }

  return data;
}

void Texture::Bind() {
  IS_DESTROYED();

  glBindTexture(GL_TEXTURE_2D, *GetID_Ptr());
  THROW_ERROR_GL(FATAL.Derived("Failed to bind texture."));
}

void Texture::Unbind() {
  IS_DESTROYED();

  glBindTexture(GL_TEXTURE_2D, 0);
}