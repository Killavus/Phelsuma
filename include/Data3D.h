#ifndef __PHELSUMA_DATA3D_H__
#define __PHELSUMA_DATA3D_H__
#include <vector>
#include <string>
#include <glad/glad.h>

class ShaderProgram;

struct Data3DDescription {
  std::string name;
  GLuint length;
  GLuint offset;
  GLuint stride;

  Data3DDescription(std::string name, GLuint length, GLuint offset, GLuint stride) : name(name), length(length), offset(offset), stride(stride) {}
};

class Data3D {
public:
  Data3D(GLfloat vertices[], GLfloat elements[], GLuint verticesSize, GLuint elementsSize, std::vector<Data3DDescription>& bufferDescription);
  Data3D(GLfloat vertices[], GLuint verticesSize, std::vector<Data3DDescription>& description);
  ~Data3D();

  void enableVertexAttributeArrays(const ShaderProgram& program);
  bool indexed() const { return indexedDraw; }
  GLsizei drawCount() const { return _drawCount; }
  void setActive() const { glBindVertexArray(VAO); }

private:
  bool indexedDraw;
  GLsizei _drawCount;
  GLuint VAO;
  std::vector<Data3DDescription> bufferDescription;
  static std::vector<Data3DDescription> defaultBufferDescription;
};
#endif // __PHELSUMA_DATA3D_H__
