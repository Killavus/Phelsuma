#include <iostream>
#include <fstream>
#include <string>
#include <variant>
#include <iterator>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#define _VECTORMATH_DEBUG
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderProgramLinker.h"
#include "ShaderCompiler.h"

using namespace Vectormath::Aos;

void terminate(int status = EXIT_FAILURE) {
  glfwTerminate();
  std::exit(status);
}

GLFWwindow* start() {
  std::srand(std::time(NULL));
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    terminate();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "PointCloud3D", NULL, NULL);

  if (window == nullptr) {
    std::cerr << "Failed to initialize GLFW window." << std::endl;
    terminate();
  }

  glfwMakeContextCurrent(window);
  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context." << std::endl;
    terminate();
  }

  return window;
}

Shader shaderFromFile(const std::string& path, GLenum type) {
  ShaderCompiler compiler = ShaderCompiler::fromFile(path, type);
  std::variant<Shader, std::string> maybeShader = compiler.compile();

  if (std::holds_alternative<std::string>(maybeShader)) {
    std::cerr << path << " -- " << "Shader compilation error!\n\n" << std::get<std::string>(maybeShader) << std::endl;
    terminate();
  }

  return std::get<Shader>(maybeShader);
}

ShaderProgram makeProgram(
  std::vector<Shader>::iterator it,
  std::vector<Shader>::iterator end
) {
  ShaderProgramLinker linker;
  for(; it != end; ++it) { linker.attachShader(*it); }

  std::variant<ShaderProgram, std::string> maybeProgram = linker.link();

  if (std::holds_alternative<std::string>(maybeProgram)) {
    std::cerr << " -- " << "Shader program link error!\n\n" << std::get<std::string>(maybeProgram) << std::endl;
    terminate();
  }
  
  return std::get<ShaderProgram>(maybeProgram);
}

std::vector<float> generatePoints(unsigned int pointsCount = 1000) {
  const float MAX_X = 22.0, MIN_X = -34.0;
  const float MAX_Y = 32.0, MIN_Y = -32.0;
  const float MAX_Z = 41.0, MIN_Z = -13.2;

  std::vector<float> result;
  result.resize(pointsCount * 4);

  for(int i = 0; i < pointsCount; ++i) {
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
  GLFWwindow *window = start();
  glViewport(0, 0, 800, 600);
  
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
  print(projection);

  program.use();
  program.uniformMat4f("camera", camera);
  program.uniformMat4f("projection", projection);

  while (!glfwWindowShouldClose(window)) {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glBindVertexArray(PointsVAO);
    glDrawArrays(GL_POINTS, 0, 1000);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate(EXIT_SUCCESS);
  return 0;
}
