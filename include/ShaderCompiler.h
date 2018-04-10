#ifndef __PHELSUMA_SHADER_COMPILER_H__
#define __PHELSUMA_SHADER_COMPILER_H__

#include <unordered_map>
#include <glad/glad.h>
#include "Shader.h"

class ShaderCompiler {
public:
  ShaderCompiler(std::string sourceCode, GLenum shaderType) : sourceCode(sourceCode), shaderType(shaderType) {};
  Shader compile();

  void setTokenReplacement(const std::string& token, const std::string& value);
  static ShaderCompiler fromFile(const std::string& path, GLenum shaderType);

private:
  std::string sourceCode;
  GLenum shaderType;

  std::unordered_map<std::string, std::string> tokenReplacements;

  void replaceTokens();
};
#endif // __PHELSUMA_SHADER_COMPILER_H__
