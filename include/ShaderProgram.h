#ifndef __PHELSUMA_SHADER_PROGRAM_H__
#define __PHELSUMA_SHADER_PROGRAM_H__
#include <GLFW/glfw3.h>

class ShaderProgram {
  ShaderProgram(GLuint programId);
  GLuint id() const { return id; }

  private:

  GLuint id;
}
#endif //__PHELSUMA_SHADER_PROGRAM_H__
