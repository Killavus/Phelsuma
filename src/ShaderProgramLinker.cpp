#include <string>
#include "ShaderProgramLinker.h"

#include "Shader.h"
#include "ShaderProgram.h"

bool ShaderProgramLinker::attachShader(const Shader& shader) {
  if (shader.invalid()) { return false; }

  auto sameTypeElement = findShaderByType(shader.type());

  if (sameTypeElement != attachedShaders.end()) {
    return false; 
  }

  attachedShaders.push_back(shader);
  return true;
}

bool ShaderProgramLinker::detachShader(GLenum type) {
  auto element = findShaderByType(type);

  if (element == attachedShaders.end()) {
    return false;
  } else {
    attachedShaders.erase(element);
    return true;
  }
}

ShaderProgram ShaderProgramLinker::link() {
  GLuint programId = glCreateProgram();
  GLint linkStatus = GL_TRUE, infoLogLength;

  for (auto const& shader : attachedShaders) {
    glAttachShader(programId, shader.id());
  }

  glLinkProgram(programId);
  glGetProgramiv(programId, GL_LINK_STATUS, &linkStatus);

  if (linkStatus == GL_FALSE) {
	glGetProgramiv(programId, GL_INFO_LOG_LENGTH, &infoLogLength);
    infoLogLength = infoLogLength == 0 ? 512 : infoLogLength;
  
    char *infoLog = new char[infoLogLength + 1];
    glGetProgramInfoLog(programId, infoLogLength, NULL, infoLog);
    std::string errorMessage(infoLog);

    return ShaderProgram(errorMessage);
  }

	for (auto const& shader : attachedShaders) {
	  glDetachShader(programId, shader.id());
	}

  return ShaderProgram(programId);
}

std::vector<Shader>::iterator ShaderProgramLinker::findShaderByType(GLenum type) {
  return std::find_if(
    attachedShaders.begin(), attachedShaders.end(),
    [type](const Shader& attachedShader) -> bool { 
	  return type == attachedShader.type();
    }
  );
}


