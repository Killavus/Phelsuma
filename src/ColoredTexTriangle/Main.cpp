#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include <cstdlib>

#include <vectormath/SSE/cpp/vectormath_aos.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "examples/Utils.h"

int main(int argc, char *argv[]) {
  GLFWwindow *window = start("ColoredTexturedTriangle");

  Shader vertex = shaderFromFile("shaders/simple.vs", GL_VERTEX_SHADER),
         fragment = shaderFromFile("shaders/simple.fs", GL_FRAGMENT_SHADER);

  ShaderProgramLinker linker;
  linker.attachShader(vertex);
  linker.attachShader(fragment);
  ShaderProgram program = linker.link();

  if (program.invalid()) {
    std::cerr << "Shader program link error!\n\n" << program.errorMessage() << std::endl;
    std::exit(1);
  }

  stbi_set_flip_vertically_on_load(true);
  float vertices[] = {
    /* positions        *//* colors          *//* tex coords */
     0.0f,  0.5f,  0.0f,    1.0f, 0.0f, 0.0f,  0.0f, 1.0f,
    -0.5f, -0.5f,  0.0f,    0.0f, 1.0f, 0.0f,  1.0f, 1.0f,
     0.5f, -0.5f,  0.0f,    0.0f, 0.0f, 1.0f,  0.0f, 0.0f
  };

  GLuint VAO, VBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glBindVertexArray(VAO);
  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) 0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void *) (6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  int width, height, nrChannels;
  unsigned char *data = stbi_load("textures/grass.jpg", &width, &height, &nrChannels, 0);
  std::cout << nrChannels << std::endl;
  GLuint texture;
  glGenTextures(1, &texture);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
  glGenerateMipmap(GL_TEXTURE_2D);
  stbi_image_free(data);

  Matrix4 mat;

  while (!glfwWindowShouldClose(window)) {
    double time = glfwGetTime();
    mat = Matrix4::rotationZ((float) time / 1.0);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    program.uniformMat44f("transform", mat);
    program.use();

    glBindVertexArray(VAO);    
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  terminate(EXIT_SUCCESS);
}
