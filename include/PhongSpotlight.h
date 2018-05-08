#ifndef __PHELSUMA_PHONG_SPOTLIGHT_H__
#define __PHELSUMA_PHONG_SPOTLIGHT_H__
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "PhongLightParameters.h"

using namespace Vectormath::Aos;

struct PhongSpotlight {
  /* 4 (pad 12)
     4 (pad 12)
     16
     16
     12 (pad 4)
     48
  */

  PhongSpotlight(
    Vector4 position,
    Vector4 direction,
    Vector3 attenuationParameters,
    float cutoffNear,
    float cutoffFar,
    PhongLightParameters parameters
  ) : cutoffNear(cutoffNear), cutoffFar(cutoffFar), direction(direction), position(position), attenuationParameters(attenuationParameters), parameters(parameters) {}

  float cutoffNear;
  float cutoffFar;
  Vector4 direction;
  Vector4 position;
  Vector3 attenuationParameters;
  PhongLightParameters parameters;
};
#endif //__PHELSUMA_PHONG_SPOTLIGHT_H__
