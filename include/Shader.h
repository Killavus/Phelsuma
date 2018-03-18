#ifndef __PHELSUMA_SHADER_H__
#define __PHELSUMA_SHADER_H__
#include <GLFW/glfw3.h>

class Shader {
  Shader(GLuint shaderId, GLenum shaderType);
  Shader(Shader&& other);
  Shader& operator=(Shader&& other);
  ~Shader();
  
  Shader(const Shader& other) = delete;
  Shader& operator=(Shader& other) = delete;

  ~Shader();

  inline GLenum type() const { return type; };
  inline GLuint id() const { return id };
  inline bool invalid() const { return id == -1 || type == -1; } 

  private:

  GLenum type;
  GLuint id;
}
#endif //__PHELSUMA_SHADER_H__
