#include "Shader.h"

Shader::Shader(GLuint shaderId, GLenum shaderType) : id(shaderId), type(shaderType) {}

Shader::Shader(const Shader&& other) {
  id = other.id;
  type = other.type;

  other.id = (GLenum) -1;
  other.type = (GLenum) -1;
}

Shader& Shader::operator=(Shader&& other) {
  id = other.id;
  type = other.type;

  other.id = (GLenum) -1;
  other.type = (GLenum) -1;

  return *this;
}

Shader::~Shader() {
  if (!invalid()) {
    glDeleteShader(id);
  }
}
