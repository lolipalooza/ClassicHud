#pragma once
#include "Utility.h"
#include "plugin.h"

#include "game_sa\CRGBA.h"
#include "game_sa\CSprite2d.h"
#include "game_sa\CFont.h"

class MobileProgressBar {
public:
    static void InstallPatches();
    static void MyDrawProgressBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd,
        unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor);
};


void MobileProgressBar::InstallPatches() {
	plugin::patch::RedirectJump(0x728640, MyDrawProgressBar);
	/*plugin::patch::Set<unsigned char>(0x728640, 0xA1);
	plugin::patch::Set<unsigned char>(0x728641, 0x24);
	plugin::patch::Set<unsigned char>(0x728642, 0x7B);
	plugin::patch::Set<unsigned char>(0x728643, 0xC9);
	plugin::patch::Set<unsigned char>(0x728644, 0x00);*/
}

void MobileProgressBar::MyDrawProgressBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd,
	unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor)
{
	if (drawBlackBorder) {
		CSprite2d::DrawRect(CRect((int)(x - 1) - 0.5f, (int)(y - 1) - 0.5f, (int)(x + width + 1) - 0.5f,
			(int)(y + height + 1) - 0.5f), CRGBA(0, 0, 0, 255));
	}
	DrawProgressBarWithProgressDelta_BilinearOffset(x, y, width, height, progress, color, progressAdd, addColor);
	if (drawPercentage) {
		static char text[12];
		sprintf(text, "%d%%", (int)progress);
		CFont::SetWrapx(SCREEN_WIDTH);
		CFont::SetRightJustifyWrap(0.0f);
		CFont::SetColor(CRGBA(0, 0, 0, color.alpha));
		CFont::SetOutlinePosition(0);
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetScale(height * 0.035f, height * 0.05f);
		float text_x = x + width * progress / 100.0f;
		if (progress > 50.0)
			CFont::SetAlignment(ALIGN_RIGHT);
		else {
			CFont::SetAlignment(ALIGN_LEFT);
			text_x += 5.0f;
		}
		CFont::PrintString(text_x, y, text);
	}
}