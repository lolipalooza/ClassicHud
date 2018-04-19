#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CText.h"
#include "CAERadioTrackManager.h"

class RadioStation {
public:
	static void InstallPatches();
	static void DisplayRadioStationName(float x, float y, char* str);
	static void Test();
};

void RadioStation::InstallPatches() {
	plugin::patch::RedirectCall(0x4E9FF1, DisplayRadioStationName);
}

void RadioStation::DisplayRadioStationName(float x, float y, char* str)
{
	auto &trackMgr = *reinterpret_cast<CAERadioTrackManager *>(0x8CB6F8);

	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
	CFont::SetFontStyle(settings.RS_FONTSTYLE); // default FONT_MENU: 2
	CFont::SetScale(SCREEN_MULTIPLIER(settings.RS_SIZE_X), SCREEN_MULTIPLIER(settings.RS_SIZE_Y));
	CFont::SetDropShadowPosition(settings.RS_SHADOW);
	if (settings.RS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.RS_OUTLINE);
	if (trackMgr.m_nStationsListed || trackMgr.m_nStationsListDown)
		CFont::SetColor(CRGBA(settings.RS_RED1, settings.RS_GREEN1, settings.RS_BLUE1, 255));
	else
		CFont::SetColor(CRGBA(settings.RS_RED2, settings.RS_GREEN2, settings.RS_BLUE2, 255));
	CFont::PrintString((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.RS_POS_Y), str);
}

void RadioStation::Test()
{
	CRGBA color1 = CRGBA(settings.RS_RED1, settings.RS_GREEN1, settings.RS_BLUE1, 255);
	CRGBA color2 = CRGBA(settings.RS_RED2, settings.RS_GREEN2, settings.RS_BLUE2, 255);
	TestMessage::Draw((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.RS_POS_Y),
		settings.RS_SIZE_X, settings.RS_SIZE_Y, ALIGN_CENTER,
		RsGlobal.maximumWidth * 0.0015625f * 590.0f,
		settings.RS_SHADOW, settings.RS_OUTLINE, settings.RS_FONTSTYLE, color1,
		(char *)TheText.Get("FEA_R0")); // Playback FM
}
