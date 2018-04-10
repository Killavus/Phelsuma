#define _USE_MATH_DEFINES
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "WorldObject3D.h"
#include "BasicModel3D.h"
#include "Data3D.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "examples/Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
  GLFWwindow *window = start("RotatingBox");

  float boxVertices[] = {
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
  };

  stbi_set_flip_vertically_on_load(true);
  GLsizei width, height, nrChannels;
  unsigned char *boxImage = stbi_load("textures/box.jpg", &width, &height, &nrChannels, 0);

  Texture2D boxTexture(
    boxImage,
    width,
    height,
    GL_RGB,
    GL_TEXTURE_2D,
    GL_UNSIGNED_BYTE
  );

  unsigned char *faceImage = stbi_load("textures/face.png", &width, &height, &nrChannels, 0);
  Texture2D faceTexture(
    faceImage,
    width,
    height,
    GL_RGBA,
    GL_TEXTURE_2D,
    GL_UNSIGNED_BYTE
  );

  std::vector<Data3DDescription> boxData3DDesc {
    Data3DDescription("vertexPos", 3, 0, 5 * sizeof(GLfloat)),
    Data3DDescription("texturePos", 2, 3 * sizeof(GLfloat), 5 * sizeof(GLfloat))
  };

  Data3D boxData3D(boxVertices, sizeof(boxVertices), boxData3DDesc);

  Shader boxFragment = shaderFromFile("shaders/box.fs", GL_FRAGMENT_SHADER);
  Shader boxVertex = shaderFromFile("shaders/box.vs", GL_VERTEX_SHADER);
  std::vector<Shader> boxShaders{ boxFragment, boxVertex };
  ShaderProgram boxProgram = makeProgram(boxShaders.begin(), boxShaders.end());

  BasicModel3D boxModel(boxData3D, DrawingPipeline{ boxProgram }, TextureSet{ boxTexture, faceTexture });

  std::vector<WorldObject3D> objects {
    WorldObject3D(boxModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.2, 0.2, 0.2)), Vector3(-0.5f, -0.5f, 0.0f)))),
    WorldObject3D(boxModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.2, 0.2, 0.2)), Vector3(0.5f, 0.5f, -2.0f)))),
    WorldObject3D(boxModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.4, 0.4, 0.4)), Vector3(0.0, 0.0, 0.0))))
  };

  float rotationUnit = (2 * M_PI) / 360;

  Matrix4 view = Matrix4::translation(Vector3(0.0, 0.0, -2.5));
  Matrix4 camera = Matrix4::perspective(M_PI / 4, 4.0 / 3.0, 0.1, 100.0);

  boxProgram.use();
  boxProgram.uniformMat44f("view", view);
  boxProgram.uniformMat44f("camera", camera);

  while (!glfwWindowShouldClose(window)) {
    objects[0].transform() *= Matrix4::rotationZYX(Vector3(rotationUnit, rotationUnit, rotationUnit));
    objects[1].transform() *= Matrix4::rotationZYX(Vector3(-rotationUnit, -rotationUnit, -rotationUnit));
    objects[2].transform() *= Matrix4::rotationX(rotationUnit);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    for (WorldObject3D &object : objects) {
      object.draw();
    }    

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate(EXIT_SUCCESS);
}
