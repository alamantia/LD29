#include "defines.h"
#include "AVector2D.h"

float AVector2D::interp_1d(float v1, float v2, float t)
{
  return v1 + (v2-v1) * t;
}

void AVector2D::interp_2d(float x1, float y1, float x2, float y2, float t)
{
  return;
}



