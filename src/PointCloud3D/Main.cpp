#include <iostream>
#include <ctime>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <vectormath/SSE/cpp/vectormath_aos.h>
#include "examples/Utils.h"

using namespace Vectormath::Aos;

std::vector<float> generatePoints(unsigned int pointsCount = 1000) {
  const float MAX_X = 22.0, MIN_X = -34.0;
  const float MAX_Y = 32.0, MIN_Y = -32.0;
  const float MAX_Z = 41.0, MIN_Z = -13.2;

  std::vector<float> result;
  result.resize(pointsCount * 4);

  for(unsigned int i = 0; i < pointsCount; ++i) {
    float x = MIN_X + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / (MAX_X - MIN_X));
    float y = MIN_Y + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / (MAX_Y - MIN_Y));
    float z = MIN_Z + static_cast<float>(std::rand()) / static_cast<float>(RAND_MAX / (MAX_Z - MIN_Z));
    float w = 1.0;

    result[i * 4] = x;
    result[i * 4 + 1] = y;
    result[i * 4 + 2] = z;
    result[i * 4 + 3] = w;
  }

  return result;
}

int main(int argc, char *argv[]) {
  GLFWwindow *window = start("PointCloud3D");
  
  Shader vertexShader = shaderFromFile("shaders/point3d.vs", GL_VERTEX_SHADER);
  Shader fragmentShader = shaderFromFile("shaders/point3d.fs", GL_FRAGMENT_SHADER);
  std::vector<Shader> shaders = { vertexShader, fragmentShader };

  ShaderProgram program = makeProgram(shaders.begin(), shaders.end());

  std::vector<float> points = generatePoints();
  for (unsigned int i = 0; i < points.size() / 4; ++i) {
    printf("%f %f %f %f\n", points[i * 4], points[i * 4 + 1], points[i * 4 + 2], points[i * 4 + 3]);
  }

  GLuint PointsVAO, PointsVBO;
  glGenBuffers(1, &PointsVBO);
  glGenVertexArrays(1, &PointsVAO);
  glBindVertexArray(PointsVAO);
  glBindBuffer(GL_ARRAY_BUFFER, PointsVBO);
  glBufferData(GL_ARRAY_BUFFER, 
    points.size() * sizeof(float),
    points.data(),
    GL_STATIC_DRAW
  );
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glPointSize(5.0f);
  Matrix4 camera = Matrix4::identity();
  Matrix4 projection = Matrix4::frustum(25.0, -50.0, -32.0, 32.0, 0.1, 100.0); 

  program.use();
  program.uniformMat44f("camera", camera);
  program.uniformMat44f("projection", projection);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glBindVertexArray(PointsVAO);
    glDrawArrays(GL_POINTS, 0, 1000);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate(EXIT_SUCCESS);
  return 0;
}
