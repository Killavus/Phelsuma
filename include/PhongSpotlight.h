#ifndef __PHELSUMA_PHONG_SPOTLIGHT_H__
#define __PHELSUMA_PHONG_SPOTLIGHT_H__
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "PhongLightParameters.h"

using namespace Vectormath::Aos;

struct PhongSpotlight {
  PhongSpotlight(
    Vector4 position,
    Vector4 direction,
    Vector3 attenuationParameters,
    float cutoffNear,
    float cutoffFar,
    PhongLightParameters parameters
  ) : position(position), direction(direction), attenuationParameters(attenuationParameters), cutoffNear(cutoffNear), cutoffFar(cutoffFar), parameters(parameters) {}

  float cutoffNear;
  float cutoffFar;
  Vector4 direction;
  Vector4 position;
  Vector3 attenuationParameters;
  PhongLightParameters parameters;
};
#endif //__PHELSUMA_PHONG_SPOTLIGHT_H__