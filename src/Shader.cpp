#include "Shader.h"

void Shader::destroy() const {
  if (!invalid()) {
    glDeleteShader(shaderId);
  }
}
