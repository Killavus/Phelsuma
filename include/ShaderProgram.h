#ifndef __PHELSUMA_SHADER_PROGRAM_H__
#define __PHELSUMA_SHADER_PROGRAM_H__
#include <string>
#include <glad/glad.h>
#include <vectormath/SSE/cpp/vectormath_aos.h>

using namespace Vectormath::Aos;

class ShaderProgram {
public:
  ShaderProgram(GLuint programId) : programId(programId) {};
  GLuint id() const { return programId; }
  void destroy() const;
  void use() const;

  void uniformFloat(const std::string& name, GLfloat value) const;
  void uniformInt(const std::string& name, GLint value) const;
  void uniformUint(const std::string& name, GLuint value) const;
  void uniformVec4f(const std::string& name, const Vector4& vec) const;
  void uniformVec4f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2, GLfloat v3) const;
  void uniformVec3f(const std::string& name, const Vector3& vec) const;
  void uniformVec3f(const std::string& name, GLfloat v0, GLfloat v1, GLfloat v2) const;
  void uniformMat4f(const std::string& name, const Matrix4& mat) const;
private:
  GLuint programId;
};
#endif //__PHELSUMA_SHADER_PROGRAM_H__
