#version 330 core

in vec4 WorldPos;
in vec2 TexturePos;
in vec4 Normal;

out vec4 FragColor;

uniform sampler2D texture0;
uniform vec4 lightPos;
uniform vec4 lightColor;
uniform vec4 viewPos;

void main() {
  vec4 norm = normalize(Normal);
  vec4 ray = normalize(lightPos - WorldPos);
  vec4 viewToFrag = normalize(viewPos - WorldPos);
  vec4 reflectedRay = reflect(-ray, norm);

  float specularC = pow(max(dot(viewToFrag, reflectedRay), 0.0), 32);
  float ambientC = 0.1;
  float diffuseC = max(dot(norm, ray), 0.0);
  float specularStrength = 0.5;
  
  vec4 ambient = ambientC * lightColor;
  vec4 diffuse = diffuseC * lightColor;
  vec4 specular = specularStrength * specularC * lightColor;

  FragColor = (ambient + diffuse + specular) * texture(texture0, TexturePos);
}