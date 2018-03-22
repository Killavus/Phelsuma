CMAKE_MINIMUM_REQUIRED(VERSION 2.8.12.1)

SET(CMAKE_CXX_STANDARD 17)
PROJECT(Phelsuma)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(glfw3 REQUIRED)
INCLUDE_DIRECTORIES(
  "${PROJECT_SOURCE_DIR}/include"
  ${glfw3_INCLUDE_DIR}
  ${SCE_VECTORMATH_PATH}
)

SET(SCE_VECTORMATH_PATH "")

ADD_EXECUTABLE(Test src/Main.cpp src/glad.c src/ShaderCompiler.cpp src/ShaderProgramLinker.cpp src/ShaderProgram.cpp src/Shader.cpp)
ADD_LIBRARY(mygl src/glad.c src/ShaderCompiler.cpp src/ShaderProgramLinker.cpp src/ShaderProgram.cpp src/Shader.cpp)

TARGET_LINK_LIBRARIES(mygl glfw ${CMAKE_DL_LIBS} -std=c++17)
TARGET_LINK_LIBRARIES(Test glfw ${CMAKE_DL_LIBS} -std=c++17)
