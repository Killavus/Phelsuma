#version 330 core

in vec3 vertexPos;
in vec2 texturePos;
in vec3 normal;

out vec2 TexturePos;
out vec4 Normal;
out vec4 WorldPos;

uniform mat4 localToWorld;
uniform mat4 view;
uniform mat4 camera;

void main() {
  WorldPos = localToWorld * vec4(vertexPos, 1.0);
  gl_Position = camera * view * WorldPos;
  TexturePos = texturePos;
  Normal = localToWorld * vec4(normal, 0.0);
}