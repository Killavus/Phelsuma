#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <ctype.h>

#include "ShaderCompiler.h"
#include "Shader.h"

ShaderCompiler ShaderCompiler::fromFile(const std::string &path, GLenum shaderType) {
  std::ifstream sourceFile;
  std::stringstream sourceCodeStream;

  sourceFile.open(path);
  sourceCodeStream << sourceFile.rdbuf();
  sourceFile.close();

  return ShaderCompiler(sourceCodeStream.str(), shaderType);
}

Shader ShaderCompiler::compile() {
  GLuint shaderId = glCreateShader(shaderType);
  GLint compilationStatus = GL_TRUE;

  replaceTokens();

  const char *sourceCodeCstr = sourceCode.c_str();
  glShaderSource(shaderId, 1, &sourceCodeCstr, nullptr);
  glCompileShader(shaderId);
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);

  if (compilationStatus == GL_FALSE) {
    GLint infoLogLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    infoLogLength = infoLogLength == 0 ? 512 : infoLogLength;
    char *infoLog = new char[infoLogLength + 1];
    glGetShaderInfoLog(shaderId, infoLogLength, NULL, infoLog);
    std::string errorMessage(infoLog);
    delete infoLog;

    return Shader(errorMessage);
  }
  
	return Shader(shaderId, shaderType);
}

void ShaderCompiler::setTokenReplacement(const std::string& token, const std::string& value) {
  tokenReplacements.insert(std::make_pair(token, value));
}

void ShaderCompiler::replaceTokens() {
  for (auto it = tokenReplacements.begin(); it != tokenReplacements.end(); ++it) {
    size_t pos = sourceCode.find(it->first);

    while (pos != std::string::npos) {
      sourceCode.replace(pos, it->first.size(), it->second);
      pos = sourceCode.find(it->first, pos + it->second.size());
    }
  }
}