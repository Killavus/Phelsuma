#ifndef __PHELSUMA_SHADER_H__
#define __PHELSUMA_SHADER_H__
#include <string>
#include <glad/glad.h>

class Shader {
public:
  Shader(GLuint shaderId, GLuint shaderType) : shaderId(shaderId), shaderType(shaderType), error("") {}
  Shader(const std::string& error): error(error), shaderId(0), shaderType(GL_INVALID_VALUE) {}

  void destroy() const;

  GLuint id() const { return shaderId; }
  GLenum type() const { return shaderType; }

  bool invalid() const { return shaderType == GL_INVALID_VALUE; }
  const std::string& errorMessage() const { return error; }

private:
  GLuint shaderId;
  GLenum shaderType;
  std::string error;
};
#endif //__PHELSUMA_SHADER_H__
