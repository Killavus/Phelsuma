#include "Shader.h"

void Shader::destroy() const {
  glDeleteShader(shaderId);
}