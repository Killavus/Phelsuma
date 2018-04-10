#version 330 core

in vec3 vertexPos;
in vec2 texturePos;
in vec3 normal;

out vec2 TexturePos;
out vec4 Normal;
out vec4 WorldPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 camera;

void main() {
  WorldPos = model * vec4(vertexPos, 1.0);
  TexturePos = texturePos;
  Normal = model * vec4(normal, 0.0);
  gl_Position = camera * view * WorldPos;
}