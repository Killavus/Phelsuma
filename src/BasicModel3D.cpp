#include "BasicModel3D.h"
#include "Texture.h"

#include <iostream>

BasicModel3D::BasicModel3D(Data3D data, const DrawingPipeline& pipeline = DrawingPipeline(), const TextureSet& textureSet = TextureSet()): data(data) {
  setDrawingPipeline(pipeline);
  setTextureSet(textureSet);
}

void BasicModel3D::setTextureSet(const TextureSet& textureSet) {
  this->textureSet = textureSet;

  for (const ShaderProgram &program : drawPipeline) {
    for (int textureOffset = 0; textureOffset < textureSet.size(); ++textureOffset) {
      program.use();
      std::string uniformName = "texture" + std::to_string(textureOffset);
      program.uniformInt(uniformName.c_str(), textureOffset);      
    }
  }
}

void BasicModel3D::setDrawingPipeline(const DrawingPipeline& pipeline) {
  drawPipeline = pipeline;
  
  for (auto it = drawPipeline.begin(); it != drawPipeline.end(); ++it) {    
    data.enableVertexAttributeArrays(*it);
  }
}

void BasicModel3D::prepareToDraw() const {
  data.setActive();

  for (unsigned int textureOffset = 0; textureOffset < textureSet.size(); ++textureOffset) {
    glActiveTexture(GL_TEXTURE0 + textureOffset);
    Texture& texture = textureSet[textureOffset];
    texture.bind();
  }
}