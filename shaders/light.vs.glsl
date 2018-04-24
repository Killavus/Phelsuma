#version 330 core

in vec3 vertexPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 camera;

void main() {
	gl_Position = camera * view * model * vec4(vertexPos, 1.0);
}