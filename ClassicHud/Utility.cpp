#include <plugin.h>
#include "Utility.h"

#include "CTimer.h"
#include "CFont.h"

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

void DrawTestString(float x, float y, float w, float h, eFontAlignment align,
	float linewidth, int shadow, int outline, int fontstyle, CRGBA color, char* str)
{
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(w), SCREEN_MULTIPLIER(h));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(align);
	CFont::SetCentreSize(linewidth);
	CFont::SetFontStyle(fontstyle);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(shadow);
	if (outline != 0) CFont::SetOutlinePosition(outline);
	CFont::SetSlantRefPoint(x, y);
	CFont::SetSlant(0.0);
	CFont::SetColor(color);
	CFont::PrintString(x, y, str);
}
