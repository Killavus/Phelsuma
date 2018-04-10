#version 330 core

uniform sampler2D ModelTexture;
uniform sampler2D SpecularTexture;
uniform vec4 ViewPos;

in vec4 WorldPos;
in vec2 TexturePos;
in vec4 Normal;

struct Material {
  uint shininess;
};

uniform Material material;

#define SPOTLIGHTS_COUNT $$SPOTLIGHTS_COUNT$$
#define POINT_LIGHTS_COUNT $$POINT_LIGHTS_COUNT$$
#define DIRECTIONAL_LIGHTS_COUNT $$DIRECTIONAL_LIGHTS_COUNT$$

struct PointLight {
  vec4 ambientColor;
  vec4 diffuseColor;
  vec4 specularColor;

  vec4 position;
  vec3 attenuation;
};
uniform PointLight pointLights[10];

vec4 calculatePointLight(PointLight light, vec4 normal, vec4 fragToView, vec4 worldPos) {
  vec4 worldToLight = light.position - worldPos;
  float rayLength = length(worldToLight);
  vec4 ray = normalize(worldToLight);
  vec4 reflectedRay = reflect(-ray, normal);

  float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * rayLength + light.attenuation.z * rayLength * rayLength);

  float diffuseIntensity = max(dot(normal, ray), 0.0);
  float specularIntensity = pow(max(dot(fragToView, reflectedRay), 0.0), material.shininess);

  vec4 ambient = (light.ambientColor * texture(ModelTexture, TexturePos)) / (POINT_LIGHTS_COUNT + SPOTLIGHTS_COUNT + DIRECTIONAL_LIGHTS_COUNT);
  vec4 diffuse = light.diffuseColor * diffuseIntensity * texture(ModelTexture, TexturePos);
  vec4 specular = light.specularColor * specularIntensity * texture(SpecularTexture, TexturePos);

  return attenuation * (ambient + diffuse + specular);
}

struct Spotlight {
  vec4 ambientColor;
  vec4 diffuseColor;
  vec4 specularColor;

  vec4 position;
  vec4 direction;
  vec3 attenuation;

  float cutoffNear;
  float cutoffFar;
};
uniform Spotlight spotlights[10];

vec4 calculateSpotlight(Spotlight light, vec4 normal, vec4 fragToView, vec4 worldPos) {
  vec4 worldToLight = light.position - worldPos;
  vec4 worldToLightDir = normalize(worldToLight);
  vec4 ray = normalize(-light.direction);
  vec4 reflectedRay = reflect(-ray, normal);

  float rayLength = length(worldToLight);
  float attenuation = 1.0 / (light.attenuation.x + light.attenuation.y * rayLength + light.attenuation.z * rayLength * rayLength);

  float lightAngle = dot(worldToLightDir, ray);
  float nearFarDelta = light.cutoffNear - light.cutoffFar;
  float spotIntensity = clamp((lightAngle - light.cutoffFar) / nearFarDelta, 0.0, 1.0);

  float diffuseIntensity = max(dot(normal, ray), 0.0);
  float specularIntensity = pow(max(dot(fragToView, reflectedRay), 0.0), material.shininess);

  vec4 ambient = (light.ambientColor * texture(ModelTexture, TexturePos)) / (POINT_LIGHTS_COUNT + SPOTLIGHTS_COUNT + DIRECTIONAL_LIGHTS_COUNT);
  vec4 diffuse = light.diffuseColor * diffuseIntensity * texture(ModelTexture, TexturePos);
  vec4 specular = light.specularColor * specularIntensity * texture(SpecularTexture, TexturePos);

  return attenuation * spotIntensity * (ambient + diffuse + specular);
}

struct DirectionalLight {
  vec4 ambientColor;
  vec4 diffuseColor;
  vec4 specularColor;

  vec4 direction;
};
uniform DirectionalLight directionalLights[10];
out vec4 FragColor;

uniform mat4 model;

vec4 calculateDirectionalLight(DirectionalLight light, vec4 normal, vec4 fragToView) {
  vec4 ray = normalize(-light.direction);
  vec4 reflectedRay = reflect(-ray, normal);
  
  float diffuseIntensity = max(dot(normal, ray), 0.0);
  float specularIntensity = pow(max(dot(fragToView, reflectedRay), 0.0), material.shininess);

  vec4 ambient = (light.ambientColor * texture(ModelTexture, TexturePos)) / (POINT_LIGHTS_COUNT + SPOTLIGHTS_COUNT + DIRECTIONAL_LIGHTS_COUNT);
  vec4 diffuse = light.diffuseColor * diffuseIntensity * texture(ModelTexture, TexturePos);
  vec4 specular = light.specularColor * specularIntensity * texture(SpecularTexture, TexturePos);

  return vec4((ambient + diffuse + specular).xyz, 1.0);
}

void main() {
  vec4 normal = normalize(Normal);
  vec4 fragToView = normalize(ViewPos - WorldPos);

  vec4 result = vec4(0.0);

  for(int i = 0; i < DIRECTIONAL_LIGHTS_COUNT; i++) {
	result += calculateDirectionalLight(directionalLights[i], normal, fragToView);
  }

  for(int i = 0; i < POINT_LIGHTS_COUNT; i++) {
    result += calculatePointLight(pointLights[i], normal, fragToView, WorldPos);
  }

  for(int i = 0; i < SPOTLIGHTS_COUNT; i++) {
    result += calculateSpotlight(spotlights[i], normal, fragToView, WorldPos);
  }

  FragColor = result;
}

