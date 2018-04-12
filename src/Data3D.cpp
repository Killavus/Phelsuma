#include "Data3D.h"
#include "ShaderProgram.h"

/* Default buffer structure: [x] [y] [z] [u] [v] [nx] [ny] [nz] */
std::vector<Data3DDescription> Data3D::defaultBufferDescription{
  Data3DDescription("vertexPos", 3, 0, 8 * sizeof(GLfloat)),
  Data3DDescription("texturePos", 2, 3 * sizeof(GLfloat), 8 * sizeof(float)),
  Data3DDescription("normalPos", 3, 5 * sizeof(GLfloat), 8 * sizeof(float))
};

Data3D::Data3D(
  GLfloat vertices[],
  GLfloat elements[],
  GLuint verticesSize,
  GLuint elementsSize,
  std::vector<Data3DDescription>& bufferDescription = Data3D::defaultBufferDescription
) : indexedDraw(true), bufferDescription(bufferDescription) {
  glGenVertexArrays(1, &VAO);
  GLuint VBO, EBO;
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, elementsSize, elements, GL_STATIC_DRAW);

  _drawCount = elementsSize / sizeof(GLuint);
  glBindVertexArray(0);
}

Data3D::Data3D(
  GLfloat vertices[],
  GLuint verticesSize,
  std::vector<Data3DDescription>& bufferDescription = Data3D::defaultBufferDescription
) : indexedDraw(false), bufferDescription(bufferDescription) {
  glGenVertexArrays(1, &VAO);
  GLuint VBO;
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, verticesSize, vertices, GL_STATIC_DRAW);

  GLuint vertexSize = 0;
  for (Data3DDescription &description : bufferDescription) { vertexSize += description.length; }
  _drawCount = verticesSize / (vertexSize * sizeof(GLfloat));

  glBindVertexArray(0);
}

Data3D::~Data3D() {
//  glDeleteVertexArrays(1, &VAO);
}

void Data3D::enableVertexAttributeArrays(const ShaderProgram& program) {
  glBindVertexArray(VAO);
  program.use();

  for (auto it = bufferDescription.begin(); it != bufferDescription.end(); ++it) {
    GLint location = glGetAttribLocation(program.id(), it->name.c_str());

    if (location != -1) {
      glVertexAttribPointer(location, it->length, GL_FLOAT, GL_FALSE, it->stride, (void*)(size_t)(it->offset));
      glEnableVertexAttribArray(location);
    }
  }

  glBindVertexArray(0);
}
