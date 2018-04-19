#include <plugin.h>
#include "Utility.h"

#include "CTimer.h"

bool ShowFlashingItem(signed int nOnDuration, signed int nOffDuration)
{
	return CTimer::m_snTimeInMillisecondsPauseMode % (nOnDuration + nOffDuration) < nOnDuration;
}

void RotateVertices(CVector2D *rect, unsigned int numVerts, float x, float y, float angle) {
	float xold, yold;
	// angle /= 57.2957795;
	float _cos = cosf(angle);
	float _sin = sinf(angle);
	for (unsigned int i = 0; i < numVerts; i++) {
		xold = rect[i].x;
		yold = rect[i].y;
		rect[i].x = x + (xold - x) * _cos + (yold - y) * _sin;
		rect[i].y = y - (xold - x) * _sin + (yold - y) * _cos;
	}
}

float BilinearOffset(float coord) {
	return static_cast<float>(static_cast<int>(coord)) - 0.5f;
}

