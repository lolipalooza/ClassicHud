#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CText.h"

class VehicleName {
public:
	static void InstallPatches();
	static void Draw(float x, float y, char* str);
	static void VehicleNameColor(CRGBA value);
	static void Test();
};

void VehicleName::InstallPatches() {
	plugin::patch::RedirectCall(0x58B156, Draw);
	plugin::patch::RedirectCall(0x58B0ED, VehicleNameColor);
}

void VehicleName::Draw(float x, float y, char* str) {
	CFont::SetFontStyle(settings.VEHICLE_FONTSTYLE);
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.VEHICLE_SIZE_X), SCREEN_MULTIPLIER(settings.VEHICLE_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetDropShadowPosition(settings.VEHICLE_SHADOW);
	if (settings.VEHICLE_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.VEHICLE_OUTLINE);
	CFont::SetSlantRefPoint(RsGlobal.maximumWidth - SCREEN_COORD(settings.VEHICLE_X), SCREEN_COORD_BOTTOM(settings.VEHICLE_Y));
	CFont::SetSlant(settings.VEHICLE_SLANT);
	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.VEHICLE_X),
		SCREEN_COORD_BOTTOM(settings.VEHICLE_Y), str);
}

void VehicleName::VehicleNameColor(CRGBA value)
{
	CFont::SetColor(CRGBA(settings.VEHICLE_R, settings.VEHICLE_G, settings.VEHICLE_B, value.alpha));
	AreaCRGBA = value;
}

void VehicleName::Test()
{
	CText text;
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.VEHICLE_SIZE_X), SCREEN_MULTIPLIER(settings.VEHICLE_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
	CFont::SetFontStyle(settings.VEHICLE_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetSlantRefPoint(RsGlobal.maximumWidth - SCREEN_COORD(settings.VEHICLE_X), SCREEN_COORD_BOTTOM(settings.VEHICLE_Y));
	CFont::SetSlant(settings.VEHICLE_SLANT);
	CFont::SetDropShadowPosition(settings.VEHICLE_SHADOW);
	if (settings.VEHICLE_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.VEHICLE_OUTLINE);
	CFont::SetColor(CRGBA(settings.VEHICLE_R, settings.VEHICLE_G, settings.VEHICLE_B, 255));
	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.VEHICLE_X),
		SCREEN_COORD_BOTTOM(settings.VEHICLE_Y), (char *)TheText.Get("BMX")); // BMX
}

