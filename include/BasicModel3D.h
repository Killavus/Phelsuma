#ifndef __PHELSUMA_BASICMODEL3D_H__
#define __PHELSUMA_BASICMODEL3D_H__

#include <functional>

#include "Data3D.h"
#include "ShaderProgram.h"

class Texture;

typedef std::vector<std::reference_wrapper<ShaderProgram>> DrawingPipeline;
typedef std::vector<std::reference_wrapper<Texture>> TextureSet;

class BasicModel3D {
public:
  BasicModel3D(Data3D data, const DrawingPipeline& pipeline, const TextureSet& textureSet);

  void setTextureSet(const TextureSet& textureSet);
  void setDrawingPipeline(const DrawingPipeline& pipeline);

  const TextureSet& currentTextureSet() const { return textureSet; }
  const DrawingPipeline& currentDrawingPipeline() const { return drawPipeline; }
  const Data3D& rawData() const { return data; }
  
  void prepareToDraw() const;
private:
  Data3D data;
  DrawingPipeline drawPipeline;
  TextureSet textureSet;
};
#endif // __PHELSUMA_BASICMODEL3D_H__