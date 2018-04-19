#pragma once

#include "CFont.h"

bool ShowFlashingItem(signed int nOnDuration, signed int nOffDuration);
void RotateVertices(CVector2D *rect, unsigned int numVerts, float x, float y, float angle);
float BilinearOffset(float coord);
void DrawTestString(float x, float y, float w, float h, eFontAlignment align, float linewidth, int shadow, int outline, int fontstyle, CRGBA color, char* str);
