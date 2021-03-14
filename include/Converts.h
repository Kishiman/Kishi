#pragma once

#include "KishiAPI.h"

class KishiConverts {
public:
  inline static const float Kfloat(float floa) { return floa; };
  // inline static const float Kfloat(FVector vect) { return vect.Size(); };
  // inline static const float Kfloat(FVector2D vect) { return vect.Size(); };
  // inline static const float Kfloat(FVector4 vect) { return vect.Size(); };
  // inline static const float Kfloat(FQuat quat) { return quat.GetAngle(); };
};
