#version 330 core

in vec2 TexturePos;
in vec3 Normal;

out vec4 FragColor;

uniform sampler2D texture0;
uniform sampler2D texture1;

void main() {
  FragColor = mix(texture(texture0, TexturePos), texture(texture1, TexturePos), 0.2);
}