#version 330 core

in vec3 vertexPos;
in vec2 texturePos;

out vec2 TexturePos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 camera;

void main() {
  gl_Position = camera * view * model * vec4(vertexPos, 1.0);
  TexturePos = texturePos;
}
