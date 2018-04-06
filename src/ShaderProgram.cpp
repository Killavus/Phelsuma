#include "ShaderProgram.h"
#include <iostream>

void ShaderProgram::destroy() const {
  if(!invalid()) {
    glDeleteProgram(programId);
  }
}

void ShaderProgram::use() const {
  if(!invalid()) {
    glUseProgram(programId);
  }
}

void ShaderProgram::uniformFloat(const std::string& name, GLfloat value) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform1f(location, value);
  }
}

void ShaderProgram::uniformUint(const std::string& name, GLuint value) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform1ui(location, value);
  }
}

void ShaderProgram::uniformInt(const std::string& name, GLint value) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform1i(location, value);
  }  
}

void ShaderProgram::uniformVec4f(const std::string& name, const Vector4& vec) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform4f(location, vec.getX(), vec.getY(), vec.getZ(), vec.getW());
  }
}

void ShaderProgram::uniformVec4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform4f(location, v0, v1, v2, v3);
  }
}

void ShaderProgram::uniformVec3f(const std::string& name, const Vector3& vec) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform3f(location, vec.getX(), vec.getY(), vec.getZ());
  }
}

void ShaderProgram::uniformVec3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniform3f(location, v0, v1, v2);
  }
}

void ShaderProgram::uniformMat44f(const std::string& name, const Matrix4& mat) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniformMatrix4fv(location, 1, GL_FALSE, (GLfloat*)&mat);
  }
}

void ShaderProgram::uniformMat43f(const std::string& name, const Transform3& mat) const {
  GLint location = glGetUniformLocation(programId, name.c_str());

  if (location != -1) {
    glUniformMatrix3x4fv(location, 1, GL_FALSE, (GLfloat*)&mat);
  }
}
