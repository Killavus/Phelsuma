#ifndef __PHELSUMA_PHONG_OBJECT_3D__
#define __PHELSUMA_PHONG_OBJECT_3D__
#include <unordered_map>
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "Texture2D.h"
#include "WorldObject3D.h"
#include "BasicModel3D.h"
#include "PhongLightScene.h"

using namespace Vectormath::Aos;

struct PhongMaterial {
  PhongMaterial(unsigned int shininess = 32) : shininess(shininess) {}

  unsigned int shininess;
};

class PhongObject3D {
public:
  PhongObject3D(Data3D data, Matrix4 worldTransform, Texture2D& texture, Texture2D& specularTexture, PhongMaterial material) : _worldObject(WorldObject3D(BasicModel3D(data, DrawingPipeline{}, TextureSet{ texture, specularTexture }), worldTransform)), _material(material) {};
  PhongObject3D(Data3D data, Matrix4 worldTransform, Texture2D& texture, float specularStrength, PhongMaterial material) : _worldObject(WorldObject3D(BasicModel3D(data, DrawingPipeline{}, TextureSet{}), worldTransform)), _material(material) {
    PhongObject3D::generateSpecularTextureFromStrength(specularStrength);
    _worldObject.objectModel().setTextureSet(TextureSet{ texture, texture });
  }

  void draw(PhongLightScene& scene);
  
  WorldObject3D& worldObject() { return _worldObject; }
  const WorldObject3D& worldObject() const { return _worldObject; }

  PhongMaterial& material() { return _material; };
  const PhongMaterial& material() const { return _material; };

  static void generateSpecularTextureFromStrength(float specularStrength);
private:
  WorldObject3D _worldObject;
  PhongMaterial _material;

  static std::unordered_map<float, Texture2D> specularStrengthTextures;
};
#endif // __PHELSUMA_PHONG_OBJECT_3D__