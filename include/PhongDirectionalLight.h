#ifndef __PHELSUMA_PHONG_DIRECTIONAL_LIGHT_H__
#define __PHELSUMA_PHONG_DIRECTIONAL_LIGHT_H__
#include <vectormath/SSE/cpp/vectormath_aos.h>

#include "PhongLightParameters.h"

using namespace Vectormath::Aos;

struct PhongDirectionalLight {
  /* 16
     48 parameters
   */
  PhongDirectionalLight(Vector4 direction, PhongLightParameters parameters) : direction(direction), parameters(parameters) {};
  Vector4 direction;
  PhongLightParameters parameters;
};
#endif //__PHELSUMA_PHONG_DIRECTIONAL_LIGHT_H__
