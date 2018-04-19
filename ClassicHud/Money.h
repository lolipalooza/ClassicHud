#pragma once
#include <plugin.h>
#include "Settings.h"

#include "CWorld.h"
#include "CFont.h"

class Money {
public:
	static void InstallPatches() {
		plugin::patch::RedirectCall(0x58F607, Draw);
	}

	static void Draw() {
		int displayedScore = CWorld::Players[CWorld::PlayerInFocus].m_nDisplayMoney;
		const char* displayScore;
		char str[16];

		if (displayedScore < 0)
		{
			CFont::SetColor(CRGBA(255, 38, 41, 255));
			displayedScore = -displayedScore;
			displayScore = "-$%07d";
		}
		else
		{
			CFont::SetColor(CRGBA(settings.MONEY_R, settings.MONEY_G, settings.MONEY_B, 255));
			displayScore = "$%08d";
		}

		_snprintf(str, sizeof(str), displayScore, displayedScore);

		CFont::SetBackground(0, 0);
		CFont::SetProp(false);
		CFont::SetAlignment(ALIGN_RIGHT);
		CFont::SetFontStyle(settings.MONEY_FONTSTYLE);
		CFont::SetRightJustifyWrap(0.0);
		CFont::SetScale(SCREEN_MULTIPLIER(settings.MONEY_WIDTH), SCREEN_MULTIPLIER(settings.MONEY_HEIGHT));
		CFont::SetDropShadowPosition(settings.MONEY_SHADOW);
		if (settings.MONEY_OUTLINE != 0)
			CFont::SetOutlinePosition(settings.MONEY_OUTLINE);
		CFont::SetDropColor(CRGBA(0, 0, 0, 255));
		CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.MONEY_X), SCREEN_COORD(settings.MONEY_Y), str);
	}
};