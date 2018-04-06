#ifndef __PHELSUMA_EXAMPLES_UTILS_H__
#define __PHELSUMA_EXAMPLES_UTILS_H__
#include <cstdlib>
#include <ctime>

#include <iostream>
#include <fstream>
#include <string>
#include <iterator>
#include <vector>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "ShaderProgram.h"
#include "ShaderProgramLinker.h"
#include "ShaderCompiler.h"

#ifdef PHELSUMA_DEBUG_OGL
void APIENTRY glDebugOutput(GLenum source,
  GLenum type,
  GLuint id,
  GLenum severity,
  GLsizei length,
  const GLchar *message,
  const void *userParam)
{
  // ignore non-significant error/warning codes
  if (id == 131169 || id == 131185 || id == 131218 || id == 131204) return;

  std::cout << "---------------" << std::endl;
  std::cout << "Debug message (" << id << "): " << message << std::endl;

  switch (source)
  {
  case GL_DEBUG_SOURCE_API:             std::cout << "Source: API"; break;
  case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cout << "Source: Window System"; break;
  case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cout << "Source: Shader Compiler"; break;
  case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cout << "Source: Third Party"; break;
  case GL_DEBUG_SOURCE_APPLICATION:     std::cout << "Source: Application"; break;
  case GL_DEBUG_SOURCE_OTHER:           std::cout << "Source: Other"; break;
  } std::cout << std::endl;

  switch (type)
  {
  case GL_DEBUG_TYPE_ERROR:               std::cout << "Type: Error"; break;
  case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: std::cout << "Type: Deprecated Behaviour"; break;
  case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:  std::cout << "Type: Undefined Behaviour"; break;
  case GL_DEBUG_TYPE_PORTABILITY:         std::cout << "Type: Portability"; break;
  case GL_DEBUG_TYPE_PERFORMANCE:         std::cout << "Type: Performance"; break;
  case GL_DEBUG_TYPE_MARKER:              std::cout << "Type: Marker"; break;
  case GL_DEBUG_TYPE_PUSH_GROUP:          std::cout << "Type: Push Group"; break;
  case GL_DEBUG_TYPE_POP_GROUP:           std::cout << "Type: Pop Group"; break;
  case GL_DEBUG_TYPE_OTHER:               std::cout << "Type: Other"; break;
  } std::cout << std::endl;

  switch (severity)
  {
  case GL_DEBUG_SEVERITY_HIGH:         std::cout << "Severity: high"; break;
  case GL_DEBUG_SEVERITY_MEDIUM:       std::cout << "Severity: medium"; break;
  case GL_DEBUG_SEVERITY_LOW:          std::cout << "Severity: low"; break;
  case GL_DEBUG_SEVERITY_NOTIFICATION: std::cout << "Severity: notification"; break;
  } std::cout << std::endl;
  std::cout << std::endl;
}
#endif // PHELSUMA_DEBUG_OGL

void terminate(int status) {
  glfwTerminate();
  std::exit(status);
}

GLFWwindow* start(const char *title) {
  std::srand(std::time(NULL));
  if (glfwInit() == GLFW_FALSE) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    terminate(EXIT_FAILURE);
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef PHELSUMA_DEBUG_OGL
  glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
#endif // PHELSUMA_DEBUG_OGL

  GLFWwindow* window = glfwCreateWindow(800, 600, title, NULL, NULL);

  if (window == nullptr) {
    std::cerr << "Failed to initialize GLFW window." << std::endl;
    terminate(EXIT_FAILURE);
  }

  glfwMakeContextCurrent(window);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize OpenGL context." << std::endl;
    terminate(EXIT_FAILURE);
  }
#ifdef PHELSUMA_DEBUG_OGL
  glDebugMessageCallback(glDebugOutput, nullptr);
  glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, nullptr, GL_TRUE);
#endif // PHELSUMA_DEBUG_OGL

  glEnable(GL_DEPTH_TEST);
  glViewport(0, 0, 800, 600);
  return window;
}

Shader shaderFromFile(const std::string& path, GLenum type) {
  ShaderCompiler compiler = ShaderCompiler::fromFile(path, type);
  Shader shader = compiler.compile();

  if (shader.invalid()) {
    std::cerr << path << " -- " << "Shader compilation error!\n\n" << shader.errorMessage() << std::endl;
    std::exit(1);
  }

  return shader;
}

ShaderProgram makeProgram(
  std::vector<Shader>::iterator it,
  std::vector<Shader>::iterator end
) {
  ShaderProgramLinker linker;
  for (; it != end; ++it) { linker.attachShader(*it); }

  ShaderProgram program = linker.link();

  if (program.invalid()) {
    std::cerr << " -- " << "Shader program link error!\n\n" << program.errorMessage() << std::endl;
    terminate(EXIT_FAILURE);
  }

  return program;
}
#endif // __PHELSUMA_EXAMPLES_UTILS_H__