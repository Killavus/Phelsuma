#ifndef __PHELSUMA_WORLD_OBJECT_3D_H__
#define __PHELSUMA_WORLD_OBJECT_3D_H__
#include "BasicModel3D.h"
#include <vectormath/SSE/cpp/vectormath_aos.h>
using namespace Vectormath::Aos;

class WorldObject3D {
public:
  WorldObject3D(BasicModel3D model, Matrix4 worldTransform) : model(model), worldTransform(worldTransform) {}
  Matrix4& transform() { return worldTransform; }
  const Matrix4& transform() const { return worldTransform; }
  BasicModel3D& objectModel() { return model; }
  const BasicModel3D& objectModel() const { return model; }

  void draw() const;
private:
  BasicModel3D model;
  Matrix4 worldTransform;
};
#endif //__PHELSUMA_WORLD_OBJECT_3D_H__