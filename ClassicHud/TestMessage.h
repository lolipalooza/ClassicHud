#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CText.h"

class TestMessage {
public:
	static void Draw(float x, float y, float w, float h, eFontAlignment align,
		float linewidth, int shadow, int outline, int fontstyle, CRGBA color, char* str);
};

void TestMessage::Draw(float x, float y, float w, float h, eFontAlignment align,
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
