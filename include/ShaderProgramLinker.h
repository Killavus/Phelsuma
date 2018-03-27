#ifndef __PHELSUMA_SHADER_PROGRAM_LINKER_H__
#define __PHELSUMA_SHADER_PROGRAM_LINKER_H__
#include <glad/glad.h>
#include <vector>
#include <algorithm>

class ShaderProgram;
class Shader;

class ShaderProgramLinker {
public:
  bool attachShader(const Shader& shader);
  bool detachShader(GLenum shaderType);

  ShaderProgram link();

private:
  std::vector<Shader> attachedShaders;
  std::vector<Shader>::iterator findShaderByType(GLenum type);
};
#endif //__PHELSUMA_SHADER_PROGRAM_LINKER_H__
