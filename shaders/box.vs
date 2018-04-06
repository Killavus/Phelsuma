#version 330 core

in vec3 vertexPos;
in vec2 texturePos;

out vec2 TexturePos;

uniform mat4 localToWorld;

void main() {
  gl_Position = localToWorld * vec4(vertexPos, 1.0);
  TexturePos = texturePos;
}