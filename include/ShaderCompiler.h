#ifndef __PHELSUMA_SHADER_COMPILER_H__
#define __PHELSUMA_SHADER_COMPILER_H__

#include <glad/glad.h>
#include <boost/variant.hpp>

#include "Shader.h"

class ShaderCompiler {
public:
  ShaderCompiler(std::string sourceCode, GLenum shaderType) : sourceCode(sourceCode), shaderType(shaderType) {};
  Shader compile() const;

  static ShaderCompiler fromFile(const std::string& path, GLenum shaderType);

private:

  std::string sourceCode;
  GLenum shaderType;
};
#endif // __PHELSUMA_SHADER_COMPILER_H__
