#ifndef __PHELSUMA_PHONG_LIGHT_PARAMETERS_H__
#define __PHELSUMA_PHONG_LIGHT_PARAMETERS_H__

#include <vectormath/SSE/cpp/vectormath_aos.h>

using namespace Vectormath::Aos;

struct PhongLightParameters {
  PhongLightParameters(
    Vector4 ambientColor,
    Vector4 specularColor,
    Vector4 diffuseColor
  ) : ambientColor(ambientColor), specularColor(specularColor), diffuseColor(diffuseColor) {};
  Vector4 ambientColor;
  Vector4 specularColor;
  Vector4 diffuseColor;
};

#endif // __PHELSUMA_PHONG_LIGHT_PARAMETERS_H__