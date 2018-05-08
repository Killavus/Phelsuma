#ifndef __PHELSUMA_PHONG_POINT_LIGHT_H__
#define __PHELSUMA_PHONG_POINT_LIGHT_H__
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "PhongLightParameters.h"

using namespace Vectormath::Aos;

struct PhongPointLight {
  PhongPointLight(Vector4 position, Vector3 attenuationParameters, PhongLightParameters parameters) : position(position), attenuationParameters(attenuationParameters), parameters(parameters) {}
  Vector4 position;
  Vector3 attenuationParameters;
  PhongLightParameters parameters;
};
#endif //__PHELSUMA_PHONG_POINT_LIGHT_H__
