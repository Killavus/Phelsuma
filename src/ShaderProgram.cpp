#include "ShaderProgram.h"

void ShaderProgram::destroy() const {
  glDeleteProgram(programId);
}

void ShaderProgram::use() const {
  glUseProgram(programId);
}

void ShaderProgram::uniformFloat(const std::string& name, GLfloat value) const {
  glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderProgram::uniformUint(const std::string& name, GLuint value) const {
  glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderProgram::uniformInt(const std::string& name, GLint value) const {
  glUniform1f(glGetUniformLocation(programId, name.c_str()), value);
}

void ShaderProgram::uniformVec4f(const std::string& name, const Vector4& vec) const {
  glUniform4f(glGetUniformLocation(programId, name.c_str()), vec.getX(), vec.getY(), vec.getZ(), vec.getW());
}

void ShaderProgram::uniformVec4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const {
  glUniform4f(glGetUniformLocation(programId, name.c_str()), v0, v1, v2, v3);
}

void ShaderProgram::uniformVec3f(const std::string& name, const Vector3& vec) const {
  glUniform3f(glGetUniformLocation(programId, name.c_str()), vec.getX(), vec.getY(), vec.getZ());
}

void ShaderProgram::uniformVec3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const {
  glUniform3f(glGetUniformLocation(programId, name.c_str()), v0, v1, v2);
}

void ShaderProgram::uniformMat4f(const std::string& name, const Matrix4& mat) const {
  glUniformMatrix4fv(glGetUniformLocation(programId, name.c_str()), 1, GL_FALSE, (GLfloat*)&mat);
}