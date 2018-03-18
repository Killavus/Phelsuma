#ifndef __PHELSUMA_SHADER_H__
#define __PHELSUMA_SHADER_H__
#include <glad/glad.h>

class Shader {
public:
  Shader(GLuint shaderId, GLuint shaderType) : shaderId(shaderId), shaderType(shaderType) {}
  void destroy() const;

  GLuint id() const { return shaderId; }
  GLenum type() const { return shaderType; }
private:
  GLuint shaderId;
  GLenum shaderType;
};
#endif //__PHELSUMA_SHADER_H__