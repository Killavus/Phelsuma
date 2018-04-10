#define _USE_MATH_DEFINES
#include <math.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "WorldObject3D.h"
#include "PhongObject3D.h"
#include "PhongLightScene.h"
#include "BasicModel3D.h"
#include "Data3D.h"
#include "Texture2D.h"
#include "ShaderProgram.h"
#include "Shader.h"
#include "examples/Utils.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

Matrix4 rotateAroundAxis(const Vector3& axis, const Vector3& objectPos, float rotation) {
  Vector3 objectToAxisDir = normalize(objectPos - axis);
  Vector3 objectToAxisAfterRot = Matrix3::rotationY(rotation) * objectToAxisDir + axis;
  Vector3 delta = objectToAxisAfterRot - objectPos;

  return Matrix4::translation(delta);
}

int main() {
  GLFWwindow *window = start("LightingBoxesPhongScene");

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

  float rotationUnit = (2 * M_PI) / 360;

  PhongMaterial mat(32);
  PhongDirectionalLight dirLight(normalize(Vector4(-0.25, -0.6, -0.4, 0.0)), PhongLightParameters(
    Vector4(0.0, 0.0, 0.1, 1.0),
    Vector4(0.0, 0.0, 0.5, 0.5),
    Vector4(0.0, 0.0, 1.0, 1.0)
  ));

  PhongPointLight ptLight(
    Vector4(0.0, 0.0, 2.5, 1.0), 
    Vector3(1.0, 0.09, 0.032),
    PhongLightParameters(
      Vector4(0.1, 0.1, 0.1, 1.0),
      Vector4(0.5, 0.5, 0.5, 0.5),
      Vector4(1.0, 1.0, 1.0, 1.0)
    )
  );

  PhongSpotlight spotlight(
    Vector4(0.0, 0.0, -4.5, 1.0),
    Vector4(0.0, 0.0,  1.0, 0.0),
    Vector3(1.0, 0.09, 0.032),
    cos(rotationUnit * 4.5), cos(rotationUnit * 8.5),
    PhongLightParameters(
      Vector4(0.1, 0.0, 0.0, 1.0),
      Vector4(0.5, 0.0, 0.0, 0.5),
      Vector4(1.0, 0.0, 0.0, 1.0)
    )
  );
  
  Shader lightFragment = shaderFromFile("shaders/light.fs", GL_FRAGMENT_SHADER);
  Shader lightVertex = shaderFromFile("shaders/light.vs", GL_VERTEX_SHADER);
  std::vector<Shader> lightShaders{ lightFragment, lightVertex };
  ShaderProgram lightProgram = makeProgram(lightShaders.begin(), lightShaders.end());
  BasicModel3D lightModel(boxData3D, DrawingPipeline{ lightProgram }, TextureSet{});
  WorldObject3D light(lightModel, Matrix4(Transform3(Matrix3::scale(Vector3(0.1, 0.1, 0.1)), ptLight.position.getXYZ())));

  PhongObject3D box(boxData3D, Matrix4(Transform3(Matrix3::scale(Vector3(0.4, 0.4, 0.4)), Vector3(-0.5f, 0.0f, 0.5f))), boxTexture, 0.5, mat);
  PhongObject3D box2(boxData3D, Matrix4(Transform3(Matrix3::scale(Vector3(0.4, 0.4, 0.4)), Vector3(0.5f, 0.0f, 1.5f))), boxTexture, 0.5, mat);

  Matrix4 view = Matrix4::translation(Vector3(0.0, 0.0, -4.5));
  Matrix4 camera = Matrix4::perspective(M_PI / 4, 4.0 / 3.0, 0.1, 100.0);


  PhongLightScene scene;
  scene.addDirectionalLight(dirLight);
  scene.addPointLight(ptLight);
  scene.addSpotlight(spotlight);

  double lastTime = 0.0;
  int frameCount = 0;
  while (!glfwWindowShouldClose(window)) {
    double time = glfwGetTime();
    frameCount++;

    if (((int)time - (int)lastTime) >= 1.0) {      
      glfwSetWindowTitle(window, (std::string("LightingBoxesPhongScene FPS: ") + std::to_string(frameCount)).c_str());
      frameCount = 0;
    }

    ptLight.position = rotateAroundAxis(Vector3(0.0, 0.0, 1.0), ptLight.position.getXYZ(), rotationUnit / 4) * ptLight.position;
    light.transform().setTranslation(ptLight.position.getXYZ());

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ShaderProgram& phongProgram = scene.program();
    phongProgram.use();
    phongProgram.uniformMat44f("camera", camera);
    phongProgram.uniformMat44f("view", view);
    phongProgram.uniformVec4f("ViewPos", -Vector4(view.getTranslation(), 1.0));
    lightProgram.use();
    lightProgram.uniformMat44f("view", view);
    lightProgram.uniformMat44f("camera", camera);
    lightProgram.uniformVec4f("lightColor", ptLight.parameters.diffuseColor);


    light.draw();
    box.draw(scene);
    box2.draw(scene);

    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
      view *= Matrix4::rotationY(rotationUnit);
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
      view *= Matrix4::rotationY(-rotationUnit);
    }

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
      view *= Matrix4::rotationX(rotationUnit);
    }

    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
      view *= Matrix4::rotationX(-rotationUnit);
    }

    glfwSwapBuffers(window);
    glfwPollEvents();
    lastTime = time;
  }

  terminate(EXIT_SUCCESS);
}