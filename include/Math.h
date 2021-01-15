#pragma once

#include <cmath>
#include <stdlib.h>

#define pow2(a) (a * a)
#define pow3(a) (a * a * a)
#define sign(a) (a < 0 ? -1 : 1)
class KishiMath {
public:
  /// <summary>solve a.x²+b.x+c=0</summary>
  static bool SolveQuadraulicEquation(float a, float b, float c, float &x1,
                                      float &x2) {
    x1 = NAN;
    x2 = NAN;
    if (a == 0) {
      return SolveLinearEquation(b, c, x1);
    }
    float delta = (b * b - 4 * a * c);
    if (delta < 0)
      return false;
    delta = sqrtf(delta);
    x1 = (-b - delta * sign(a)) / (2 * a);
    x2 = (-b + delta * sign(a)) / (2 * a);
    return true;
  }
  static bool SolveLinearEquation(float a, float b, float &x) {
    x = 0;
    if (a == 0) {
      if (b == 0)
        return true;
      return false;
    }
    x = -b / a;
    return true;
  }

  static float ModInRange(float x, float min, float max) {
    return Mod(x - min, max - min) + min;
  }
  static float ModInPI(float x) { return ModInRange(x, -M_PI, M_PI); }

  static float Mod(float x, float y) {
    int div = floorf(x / y);
    return x - y * div;
  }
  static float ForwardAndBackward(float x, float min, float max) {
    return ForwardAndBackward(x - min, max - min) + min;
  }

  static float ForwardAndBackward(float x, float min, float max,
                                  bool &forward) {
    return ForwardAndBackward(x - min, max - min, forward) + min;
  }
  static float ForwardAndBackward(float x, float y) {
    bool forward;
    return ForwardAndBackward(x, y, forward);
  }
  static float ForwardAndBackward(float x, float y, bool &forward) {
    int div = floorf(x / y);
    if (div % 2 == 0) {
      forward = true;
      return x - y * div;
    } else {
      forward = false;
      return y * (div + 1) - x;
    }
  }

  static float RelativeAngleInRad(float angle) {
    while (angle < -M_PI || angle > M_PI) {

      if (angle > 0)
        angle -= M_PI * 2;
      else
        angle += M_PI * 2;
    }
    return angle;
  }
  static float EulerInDeg(float angle) {
    while (angle < 0) {
      angle += 360;
    }
    return angle;
  }
  static float EulerInRad(float angle) {
    while (angle < 0) {
      angle += M_PI * 2;
    }
    return angle;
  };
};
