#ifndef __PHELSUMA_TEXTURE_H__
#define __PHELSUMA_TEXTURE_H__
#include <glad/glad.h>

class Texture {
public:
  virtual ~Texture() { glDeleteTextures(1, &textureId); }
  virtual void bind() const = 0;
protected:
  GLuint textureId;
};
#endif //__PHELSUMA_TEXTURE_H__