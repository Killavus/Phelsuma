#ifndef __PHELSUMA_TEXTURE_2D_H__
#define __PHELSUMA_TEXTURE_2D_H__
#include <glad/glad.h>

#include "Texture.h"

class Texture2D : public Texture {
public:
  Texture2D(void *data, GLsizei width, GLsizei height, GLenum format, GLenum textureType, GLenum dataType); /* assumption: internalFormat = format */
  void bind() const override {
    glBindTexture(textureType, textureId);
  };
  void upload(void *newData);
private:
  GLsizei width, height;
  GLenum textureType, dataType, format;
};
#endif //__PHELSUMA_TEXTURE_H__