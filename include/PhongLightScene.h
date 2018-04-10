#ifndef __PHELSUMA_PHONG_LIGHT_SCENE_H__
#define __PHELSUMA_PHONG_LIGHT_SCENE_H__
#include "ShaderProgram.h"
#include "PhongDirectionalLight.h"
#include "PhongPointLight.h"
#include "PhongSpotlight.h"

#include <vector>
#include <functional>

class PhongLightScene {
public:
  PhongLightScene(): programReady(false), phongProgram(ShaderProgram("Phong Lighting not compiled yet")) {}

  ShaderProgram& program() {
    if (!programReady) { preparePhongProgram(); }
    bindUniforms();
    return phongProgram;
  }

  void addDirectionalLight(PhongDirectionalLight& newLight);
  void addPointLight(PhongPointLight& newLight);
  void addSpotlight(PhongSpotlight& newLight);

private:
  static std::string phongFragmentTemplatePath;
  static std::string phongVertexTemplatePath;

  std::vector<std::reference_wrapper<PhongDirectionalLight>> directionalLights;
  std::vector<std::reference_wrapper<PhongPointLight>> pointLights;
  std::vector<std::reference_wrapper<PhongSpotlight>> spotlights; 

  void preparePhongProgram();
  void bindUniforms();
  void bindLightParameters(const std::string& name, const PhongLightParameters& parameters);

  ShaderProgram phongProgram;
  bool programReady;
};
#endif //__PHELSUMA_PHONG_LIGHT_SCENE_H__