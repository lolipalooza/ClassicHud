#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CText.h"

static CRGBA AreaCRGBA;

class AreaName {
public:
	static void InstallPatches();
	static void Draw(float x, float y, char* str);
	static void AreaNameColor(CRGBA value);
	static void Test();
};

void AreaName::InstallPatches() {
	plugin::patch::RedirectCall(0x58AE5D, Draw);
	plugin::patch::RedirectCall(0x58AE02, AreaNameColor);
}

void AreaName::Draw(float x, float y, char* str) {
	CFont::SetFontStyle(settings.AREA_FONTSTYLE);
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.AREA_SIZE_X), SCREEN_MULTIPLIER(settings.AREA_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetDropShadowPosition(settings.AREA_SHADOW);
	if (settings.AREA_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.AREA_OUTLINE);
	CFont::SetSlantRefPoint(RsGlobal.maximumWidth - SCREEN_COORD(settings.AREA_X), SCREEN_COORD_BOTTOM(settings.AREA_Y));
	CFont::SetSlant(settings.AREA_SLANT);
	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.AREA_X),
		SCREEN_COORD_BOTTOM(settings.AREA_Y), str);
}

void AreaName::AreaNameColor(CRGBA value)
{
	CFont::SetColor(CRGBA(settings.AREA_R, settings.AREA_G, settings.AREA_B, value.alpha));
	AreaCRGBA = value;
}

void AreaName::Test()
{
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.AREA_SIZE_X), SCREEN_MULTIPLIER(settings.AREA_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
	CFont::SetFontStyle(settings.AREA_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetSlantRefPoint(RsGlobal.maximumWidth - SCREEN_COORD(settings.AREA_X), SCREEN_COORD_BOTTOM(settings.AREA_Y));
	CFont::SetSlant(settings.AREA_SLANT);
	CFont::SetDropShadowPosition(settings.AREA_SHADOW);
	if (settings.AREA_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.AREA_OUTLINE);
	CFont::SetColor(CRGBA(settings.AREA_R, settings.AREA_G, settings.AREA_B, 255));
	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.AREA_X),
		SCREEN_COORD_BOTTOM(settings.AREA_Y), (char *)TheText.Get("GAN")); // Ganton
}

