#ifndef __PHELSUMA_SHADER_COMPILER_H__
#define __PHELSUMA_SHADER_COMPILER_H__

#include <variant>
#include <GLFW/glfw3.h>

#include "Shader.h"

class ShaderCompiler {
  ShaderCompiler(std::string sourceCode, GLenum shaderType);
  std::variant<Shader, std::string> compile() const;

  static ShaderCompiler fromFile(const char *path, GLenum shaderType);

  private:

  std::string sourceCode;
  GLenum shaderType;
}

#endif // __SHADER_COMPILER_H__
