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
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 0.0f, 0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  0.0f, -1.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, 0.0f,  0.0f, -1.0f,

    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 1.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  0.0f, 1.0f,

    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, -1.0f,  0.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, -1.0f,  0.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  1.0f, 0.0f, -1.0f,  0.0f,  0.0f,

    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 1.0f,  0.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 1.0f,  0.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 1.0f,  0.0f,  0.0f,

    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,
    0.5f, -0.5f, -0.5f,  1.0f, 1.0f, 0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    0.5f, -0.5f,  0.5f,  1.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f,  0.5f,  0.0f, 0.0f, 0.0f, -1.0f,  0.0f,
    -0.5f, -0.5f, -0.5f,  0.0f, 1.0f, 0.0f, -1.0f,  0.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
    0.5f,  0.5f, -0.5f,  1.0f, 1.0f, 0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    0.5f,  0.5f,  0.5f,  1.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f,  0.5f,  0.0f, 0.0f, 0.0f,  1.0f,  0.0f,
    -0.5f,  0.5f, -0.5f,  0.0f, 1.0f, 0.0f,  1.0f,  0.0f,
  };

  stbi_set_flip_vertically_on_load(true);
  GLsizei width, height, nrChannels;
  unsigned char *boxImage = stbi_load("textures/box.jpg", &width, &height, &nrChannels, 0);

  Data3D boxData3D(boxVertices, sizeof(boxVertices), std::vector<Data3DDescription> {
    Data3DDescription("vertexPos", 3, 0, 8 * sizeof(GLfloat)),
    Data3DDescription("texturePos", 2, 3 * sizeof(GLfloat), 8 * sizeof(GLfloat)),
    Data3DDescription("normal", 3, 5 * sizeof(GLfloat), 8 * sizeof(GLfloat))
  });

  Texture2D boxTexture(
    boxImage,
    width,
    height,
    GL_RGB,
    GL_TEXTURE_2D,
    GL_UNSIGNED_BYTE
  );

  Shader phongFragment = shaderFromFile("shaders/phong.fs", GL_FRAGMENT_SHADER);
  Shader phongVertex = shaderFromFile("shaders/phong.vs", GL_VERTEX_SHADER);
  Shader lightFragment = shaderFromFile("shaders/light.fs", GL_FRAGMENT_SHADER);
  Shader lightVertex = shaderFromFile("shaders/light.vs", GL_VERTEX_SHADER);

  std::vector<Shader> phongShaders{ phongFragment, phongVertex };
  std::vector<Shader> lightShaders{ lightFragment, lightVertex };

  ShaderProgram phongProgram = makeProgram(phongShaders.begin(), phongShaders.end());
  ShaderProgram lightProgram = makeProgram(lightShaders.begin(), lightShaders.end());

  BasicModel3D boxModel(boxData3D, DrawingPipeline{ phongProgram }, TextureSet{ boxTexture });
  BasicModel3D lightModel(boxData3D, DrawingPipeline{ lightProgram }, TextureSet{});

  WorldObject3D box(boxModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.4, 0.4, 0.4)), Vector3(-0.5f, 0.0f, 0.5f))));
  WorldObject3D box2(boxModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.4, 0.4, 0.4)), Vector3(0.5f, 0.0f, 0.5f))));
  WorldObject3D light(lightModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.1, 0.1, 0.1)), Vector3(0.0f, 0.0f, 1.5f))));

  Matrix4 view = Matrix4::translation(Vector3(0.0, 0.0, -4.5));
  Matrix4 camera = Matrix4::perspective(M_PI / 4, 4.0 / 3.0, 0.1, 100.0);

  Vector4 lightColor(1.0f, 1.0f, 1.0f, 1.0f);

  phongProgram.use();
  phongProgram.uniformMat44f("view", view);
  phongProgram.uniformVec4f("viewPos", Vector4(view.getTranslation(), 1.0));
  phongProgram.uniformMat44f("camera", camera);
  phongProgram.uniformVec4f("lightColor", lightColor);
  phongProgram.uniformVec4f("lightPos", Vector4(light.transform().getTranslation(), 1.0));

  lightProgram.use();
  lightProgram.uniformMat44f("view", view);
  lightProgram.uniformMat44f("camera", camera);
  lightProgram.uniformVec4f("lightColor", lightColor);

  float rotationUnit = (2 * M_PI) / 360;
  Vector3 lightRotationAxis = Vector3(0.0, 0.0, 0.5);

  while (!glfwWindowShouldClose(window)) {
    Vector3 lightToRotAxis = normalize(light.transform().getTranslation() - lightRotationAxis);
    Vector3 afterRotPos = Matrix3::rotationY(rotationUnit * 4) * lightToRotAxis + lightRotationAxis;
    Vector3 rotationTransDelta = afterRotPos - light.transform().getTranslation();
    light.transform() *= Matrix4::translation(rotationTransDelta);

    phongProgram.use();
    phongProgram.uniformVec4f("lightPos", Vector4(light.transform().getTranslation(), 1.0));

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    box.draw();
    box2.draw();
    light.draw();

    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
      view *= Matrix4::rotationY(rotationUnit);
    }

    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
      view *= Matrix4::rotationY(-rotationUnit);
    }

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
      view *= Matrix4::rotationX(rotationUnit);
    }

    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
      view *= Matrix4::rotationX(-rotationUnit);
    }

    lightProgram.use();
    lightProgram.uniformMat44f("view", view);
    phongProgram.use();
    phongProgram.uniformMat44f("view", view);
    phongProgram.uniformVec4f("viewPos", Vector4(view.getTranslation(), 1.0));

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate(EXIT_SUCCESS);
}