#include "ShaderProgramLinker.h"

bool ShaderProgramLinker::attachShader(Shader&& shader) {
  auto sameTypeElement = findShaderByType(shader.type());

  if (sameTypeElement != attachedShaders.end()) {
    return false; 
  }

  attachedShaders.push_back(shader);
  return true;
}

bool ShaderProgramLinker::detachShader(GLenum shaderType) {
  auto element = findShaderByType(shaderType);

  if (element == attachedShaders.end()) {
    return false;
  } else {
    attachedShaders.erase(element);
    return true;
  }
}

std::variant<ShaderProgram, std::string> link() {
  std::variant<ShaderProgram, std::string> result;

  GLuint programId = glCreateProgram();
  GLint linkStatus = GL_FALSE, infoLogLength;

  for (auto const& shader : attachedShaders) {
    glAttachShader(programId, shader.id());
  }

  glLinkProgram(programId);
  glGetProgram(programId, GL_LINK_STATUS, &linkStatus);
  if (linkStatus == GL_FALSE) {
    glGetProgram(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    infoLogLength = infoLogLength == 0 ? 512 : infoLogLength;
  
    char infoLog[] = new char[infoLogLength + 1];
    glGetProgramInfoLog(programId, infoLogLength, NULL, infoLog);
    result = std::string(infoLog);
    delete infoLog;
  } else {
    result = ShaderProgram(programId);
  }

  return result;
}

std::vector<Shader>::iterator ShaderProgramLinker::findShaderByType(GLenum type) {
  return std::find_if(
    attachedShaders.begin(), attachedShaders.end(),
    [](const Shader& shader) -> bool { 
      return shader.type() == type 
    }
  );
}


