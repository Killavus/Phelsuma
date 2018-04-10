#include <iostream>
#include "PhongObject3D.h"

std::unordered_map<float, Texture2D> PhongObject3D::specularStrengthTextures = std::unordered_map<float, Texture2D>();

void PhongObject3D::generateSpecularTextureFromStrength(float specularStrength) {
  if (PhongObject3D::specularStrengthTextures.find(specularStrength) == PhongObject3D::specularStrengthTextures.end()) {
    float s = specularStrength;
    float data[] = { s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s,
      s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s, s };

    PhongObject3D::specularStrengthTextures.insert(std::make_pair(specularStrength, Texture2D(data, 8, 8, GL_RGB, GL_TEXTURE_2D, GL_FLOAT)));
  }
}

void PhongObject3D::draw(PhongLightScene &scene) {
  ShaderProgram& phongProgram = scene.program();

  _worldObject.objectModel().setDrawingPipeline(DrawingPipeline{ phongProgram });

  phongProgram.use();
  phongProgram.uniformUint("material.shininess", _material.shininess);  
  phongProgram.uniformInt("ModelTexture", 0);
  phongProgram.uniformInt("SpecularTexture", 1);

  _worldObject.draw();
}