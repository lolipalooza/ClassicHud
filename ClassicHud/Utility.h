#pragma once

#include "CFont.h"

bool ShowFlashingItem(signed int nOnDuration, signed int nOffDuration);
void RotateVertices(CVector2D *rect, unsigned int numVerts, float x, float y, float angle);
float BilinearOffset(float coord);
