#include "glad/glad.h"
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>

void killProgram(int status = EXIT_FAILURE) {
  glfwTerminate();
  std::exit(status);
}

GLFWwindow* initializeOpenGL() {
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    killProgram();
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(800, 600, "Phelsuma", NULL, NULL); 
  if (window == nullptr) {
    std::cerr << "Failed to initialize GLFW window." << std::endl;
    killProgram();
  }
  
  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context." << std::endl;
    killProgram();
  }

  return window;
}

int main(int argc, char *argv[]) {
  GLFWwindow *window = initializeOpenGL();
  glViewport(0, 0, 800, 600);

  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
  }

  killProgram(EXIT_SUCCESS);
}
