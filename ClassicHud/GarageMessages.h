#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CText.h"

class GarageMessages {
public:
	static void InstallPatches();
	static void Draw(float x, float y, char* str);
	static void Test();
};

void GarageMessages::InstallPatches() {
	plugin::patch::RedirectCall(0x4478D6, Draw);
	plugin::patch::RedirectCall(0x447940, Draw);
	plugin::patch::RedirectCall(0x44797E, Draw);
}

void GarageMessages::Draw(float x, float y, char* str)
{
	CFont::SetScale(SCREEN_MULTIPLIER(settings.GARAGES_SIZE_X), SCREEN_MULTIPLIER(settings.GARAGES_SIZE_Y));
	CFont::SetCentreSize(RsGlobal.maximumWidth * (1.0f - 0.0015625f * settings.GARAGES_LINEWIDTH));	// defaulf: 230.0f
	CFont::SetFontStyle(settings.GARAGES_FONTSTYLE); // default FONT_MENU: 2
	CFont::SetColor(CRGBA(settings.GARAGES_R, settings.GARAGES_G, settings.GARAGES_B, 255));
	CFont::SetDropShadowPosition(settings.GARAGES_SHADOW);
	if (settings.GARAGES_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.GARAGES_OUTLINE);
	CFont::PrintString((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.GARAGES_Y), str);
}

void GarageMessages::Test()
{
	TestMessage::Draw((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.GARAGES_Y),
		settings.GARAGES_SIZE_X, settings.GARAGES_SIZE_Y, ALIGN_CENTER,
		RsGlobal.maximumWidth * (1.0f - 0.0015625f * settings.GARAGES_LINEWIDTH),
		settings.GARAGES_SHADOW, settings.GARAGES_OUTLINE, settings.GARAGES_FONTSTYLE,
		CRGBA(settings.GARAGES_R, settings.GARAGES_G, settings.GARAGES_B, 255),
		(char *)TheText.Get("GA_15")); // Hope you like the new color
}
