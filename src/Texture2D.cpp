#include "Texture2D.h"

Texture2D::Texture2D(
  void *data,
  GLsizei width,
  GLsizei height,
  GLenum format,
  GLenum textureType,
  GLenum dataType
) :width(width), height(height), textureType(textureType), dataType(dataType), format(format) {
  glGenTextures(1, &textureId);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(textureType, textureId);
  glTexImage2D(textureType, 0, format, width, height, 0, format, dataType, data);
  glGenerateMipmap(textureType);
  glBindTexture(textureType, 0);
}

void Texture2D::upload(void *newData) {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(textureType, textureId);
  glTexImage2D(textureType, 0, format, width, height, 0, format, dataType, newData);
  glGenerateMipmap(textureType);
  glBindTexture(textureType, 0);
}
