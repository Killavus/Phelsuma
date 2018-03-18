#include <fstream>
#include <sstream>

#include "ShaderCompiler.h"

ShaderCompiler::ShaderCompiler(std::string sourceCode, GLenum shaderType) : sourceCode(sourceCode), shaderType(shaderType) {}

ShaderCompiler ShaderCompiler::fromFile(const char *path, GLenum shaderType) {
  std::ifstream sourceFile(path);
  std::stringstream sourceCodeStream;

  sourceFile.open();
  sourceCodeStream << sourceFile.rdbuf();
  sourceFile.close();

  return ShaderCompiler(sourceCodeStream.str(), shaderType);
}

std::variant<Shader, std::string> ShaderCompiler::compile() const {
  std::variant<Shader, std::string> result;

  GLuint shaderId = glCreateShader(shaderType);
  GLint compilationStatus = GL_TRUE;

  glShaderSource(shaderId, 1, sourceCode.c_str(), nullptr);
  glCompileShader(shaderId);
  glGetShaderiv(shaderId, GL_COMPILE_STATUS, &compilationStatus);

  if (compilationStatus == GL_FALSE) {
    GLint infoLogLength;
    glGetShaderiv(shaderId, GL_INFO_LOG_LENGTH, &infoLogLength);
    infoLogLength = infoLogLength == 0 ? 512 : infoLogLength;
    char infoLog[] = new char[infoLogLength + 1];
    glGetShaderInfoLog(shaderId, infoLogLength, NULL, infoLog);
    result = std::string(infoLog);
    delete infoLog;
  } else {
    result = Shader(shaderId, shaderType);
  }

  return result;
}
