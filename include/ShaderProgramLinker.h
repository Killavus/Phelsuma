#ifndef __PHELSUMA_SHADER_PROGRAM_LINKER_H__
#define __PHELSUMA_SHADER_PROGRAM_LINKER_H__
#include <GLFW/glfw3.h>
#include <variant>

#include "ShaderProgram.h"

class ShaderProgramLinker {
  bool attachShader(Shader&& shader);
  bool detachShader(GLenum shaderType);

  std::variant<ShaderProgram, std::string> link();

  private:
  std::vector<Shader> attachedShaders;

  std::vector<Shader>::iterator findShaderByType(GLenum type);
}
#endif //__PHELSUMA_SHADER_PROGRAM_LINKER_H__
