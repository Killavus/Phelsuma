#include "ShaderCompiler.h"
#include "ShaderProgramLinker.h"
#include "PhongLightScene.h"

#include <glad/glad.h>
#include <iostream>

const PHONG_MAXIMUM_DIRECTIONAL_LIGHTS = 5;
const PHONG_MAXIMUM_POINT_LIGHTS = 100;
const PHONG_MAXIMUM_SPOTLIGHTS = 100;

std::string PhongLightScene::phongFragmentTemplatePath = "shaders/phongScene.fstpl.glsl";
std::string PhongLightScene::phongVertexTemplatePath = "shaders/phongScene.vstpl.glsl";

void PhongLightScene::addDirectionalLight(PhongDirectionalLight& newLight) { directionalLights.push_back(newLight); programReady = false; }
void PhongLightScene::addPointLight(PhongPointLight& newLight) { pointLights.push_back(newLight); programReady = false; }
void PhongLightScene::addSpotlight(PhongSpotlight& newLight) { spotlights.push_back(newLight); programReady = false; }

void PhongLightScene::preparePhongProgram() {
  ShaderProgramLinker linker;
  ShaderCompiler vertexCompiler = ShaderCompiler::fromFile(PhongLightScene::phongVertexTemplatePath, GL_VERTEX_SHADER);
  ShaderCompiler fragmentCompiler = ShaderCompiler::fromFile(PhongLightScene::phongFragmentTemplatePath, GL_FRAGMENT_SHADER);

  fragmentCompiler.setTokenReplacement("$$DIRECTIONAL_LIGHTS_COUNT$$", std::to_string(directionalLights.size()));
  fragmentCompiler.setTokenReplacement("$$POINT_LIGHTS_COUNT$$", std::to_string(pointLights.size()));
  fragmentCompiler.setTokenReplacement("$$SPOTLIGHTS_COUNT$$", std::to_string(spotlights.size()));

  Shader fragment = fragmentCompiler.compile();
  Shader vertex = vertexCompiler.compile();

  if (fragment.invalid()) { std::cerr << "Phong fragment shader compilation failed!\n\n" << fragment.errorMessage() << std::endl; }
  if (vertex.invalid()) { std::cerr << "Phong vertex shader compilation failed!\n\n" << vertex.errorMessage() << std::endl; }

  linker.attachShader(fragment);
  linker.attachShader(vertex);

  ShaderProgram phong = linker.link();
  if (phong.invalid()) { std::cerr << "Phong program linking failed!\n\n" << phong.errorMessage() << std::endl; }

  phongProgram = phong;
  programReady = true;
}

void PhongLightScene::bindUniforms() {
  phongProgram.use();
  for (size_t i = 0; i < directionalLights.size(); ++i) {
    std::string name;
    name += "directionalLights[";
    name += std::to_string(i);
    name += "]";

    PhongDirectionalLight& light = directionalLights[i];

    phongProgram.uniformVec4f(name + ".direction", light.direction);
    bindLightParameters(name, light.parameters);
  }

  for (size_t i = 0; i < pointLights.size(); ++i) {
    std::string name;
    name += "pointLights[";
    name += std::to_string(i);
    name += "]";

    PhongPointLight& light = pointLights[i];
    phongProgram.uniformVec4f(name + ".position", light.position);
    phongProgram.uniformVec3f(name + ".attenuation", light.attenuationParameters);
    bindLightParameters(name, light.parameters);
  }

  for (size_t i = 0; i < spotlights.size(); ++i) {
    std::string name;
    name += "spotlights[";
    name += std::to_string(i);
    name += "]";

    PhongSpotlight& light = spotlights[i];
    phongProgram.uniformVec4f(name + ".position", light.position);
    phongProgram.uniformVec3f(name + ".attenuation", light.attenuationParameters);
    phongProgram.uniformVec4f(name + ".direction", light.direction);
    phongProgram.uniformFloat(name + ".cutoffNear", light.cutoffNear);
    phongProgram.uniformFloat(name + ".cutoffFar", light.cutoffFar);
    bindLightParameters(name, light.parameters);
  }
}

void PhongLightScene::bindUBO() {

}

void PhongLightScene::bindLightParameters(const std::string& name, const PhongLightParameters& parameters) {
  phongProgram.uniformVec4f(name + ".ambientColor", parameters.ambientColor);
  phongProgram.uniformVec4f(name + ".diffuseColor", parameters.diffuseColor);
  phongProgram.uniformVec4f(name + ".specularColor", parameters.specularColor);
}
