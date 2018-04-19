#pragma once
#include <plugin.h>
#include "Settings.h"

#include "CClock.h"
#include "CFont.h"

class Clock {
public:
	static void InstallPatches();
	static void Draw(float posX, float posY);
};

void Clock::InstallPatches() {
	plugin::patch::RedirectCall(0x58EC21, Draw);
}

void Clock::Draw(float posX, float posY) {
	char str[16];
	CClock* CClock;

	CFont::SetProp(0);
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.CLOCK_WIDTH), SCREEN_MULTIPLIER(settings.CLOCK_HEIGHT));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetRightJustifyWrap(0.0);
	CFont::SetFontStyle(settings.CLOCK_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetColor(CRGBA(settings.CLOCK_R, settings.CLOCK_G, settings.CLOCK_B, 255));
	CFont::SetDropShadowPosition(settings.MONEY_SHADOW);
	if (settings.MONEY_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.MONEY_OUTLINE);

	_snprintf(str, sizeof(str), "%02d:%02d", CClock->ms_nGameClockHours, CClock->ms_nGameClockMinutes);

	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.CLOCK_X),
		SCREEN_COORD(settings.CLOCK_Y), str);
}
