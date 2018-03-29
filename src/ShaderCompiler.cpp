#include <iostream>
#include <fstream>
#include <sstream>

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

Shader ShaderCompiler::compile() const {
  GLuint shaderId = glCreateShader(shaderType);
  GLint compilationStatus = GL_TRUE;

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
