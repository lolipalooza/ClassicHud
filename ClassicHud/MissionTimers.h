#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CText.h"

class MissionTimers {
public:
	static void InstallPatches();
	static void DrawMissionTimers_Timer(float x, float y, char* str);
	static void DrawMissionTimers_TimerText(float x, float y, char* str);
	static void DrawMissionTimers_StatusTextChartBar(float x, float y, WORD width, WORD height, float fPercentage,
		BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void DrawMissionTimers_StatusTextValue(float x, float y, char* str);
	static void DrawMissionTimers_StatusTextDescription(float x, float y, char* str);
	static void Test();
};

void MissionTimers::InstallPatches() {
	plugin::patch::RedirectCall(0x58B420, DrawMissionTimers_TimerText);
	plugin::patch::RedirectCall(0x58B3D2, DrawMissionTimers_Timer);
	plugin::patch::RedirectCall(0x58B657, DrawMissionTimers_StatusTextChartBar);
	plugin::patch::RedirectCall(0x58B58D, DrawMissionTimers_StatusTextValue);
	plugin::patch::RedirectCall(0x58B6A6, DrawMissionTimers_StatusTextDescription);
}

void MissionTimers::DrawMissionTimers_Timer(float x, float y, char* str)
{
	CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE); // default FONT_MENU: 2
	CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
	if (settings.M_TIMERS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
	CFont::SetColor(CRGBA(settings.M_TIMERS_R, settings.M_TIMERS_G, settings.M_TIMERS_B, 255));
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.M_TIMER_X), SCREEN_COORD(settings.M_TIMER_Y), str);
}

void MissionTimers::DrawMissionTimers_TimerText(float x, float y, char* str)
{
	CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE); // default FONT_MENU: 2
	CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
	if (settings.M_TIMERS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
	CFont::SetColor(CRGBA(settings.M_TIMERS_R, settings.M_TIMERS_G, settings.M_TIMERS_B, 255));
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.M_TIMER_DESC_X), SCREEN_COORD(settings.M_TIMER_Y), str);
}

void MissionTimers::DrawMissionTimers_StatusTextChartBar(float x, float y, WORD width, WORD height, float fPercentage,
	BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	float OFFSET_Y = y * settings.M_STATUSTEXT_SPACE;
	CSprite2d::DrawBarChart(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.M_STATUSBAR_X),
		SCREEN_COORD(settings.M_STATUSBAR_Y + OFFSET_Y),
		(unsigned short)SCREEN_MULTIPLIER(settings.M_STATUSBAR_SIZE_X),
		(unsigned char)SCREEN_MULTIPLIER(settings.M_STATUSBAR_SIZE_Y),
		(unsigned char)fPercentage, 0, 0, settings.M_STATUSBAR_BORDER,
		CRGBA(settings.M_STATUSBAR_R, settings.M_STATUSBAR_G, settings.M_STATUSBAR_B, settings.M_STATUSBAR_A),
		CRGBA(0, 0, 0, settings.M_STATUSBAR_A));
}

void MissionTimers::DrawMissionTimers_StatusTextValue(float x, float y, char* str)
{
	float OFFSET_Y = y * settings.M_STATUSTEXT_SPACE;
	CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE); // default FONT_MENU: 2
	CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
	if (settings.M_TIMERS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
	CFont::SetColor(CRGBA(settings.M_STATUSBAR_R, settings.M_STATUSBAR_G, settings.M_STATUSBAR_B, 255));
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.M_STATUSTEXT_X),
		SCREEN_COORD(settings.M_STATUSTEXT_Y + OFFSET_Y), str);
}

void MissionTimers::DrawMissionTimers_StatusTextDescription(float x, float y, char* str)
{
	float OFFSET_Y = y * settings.M_STATUSTEXT_SPACE;
	CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE); // default FONT_MENU: 2
	CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
	if (settings.M_TIMERS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
	CFont::SetColor(CRGBA(settings.M_STATUSBAR_R, settings.M_STATUSBAR_G, settings.M_STATUSBAR_B, 255));
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.M_STATUSTEXT_DESC_X),
		SCREEN_COORD(settings.M_STATUSTEXT_Y + OFFSET_Y), str);
}

void MissionTimers::Test()
{
	// Timer Counter
	CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
	CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE);
	CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
	if (settings.M_TIMERS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
	CFont::SetColor(CRGBA(settings.M_TIMERS_R, settings.M_TIMERS_G, settings.M_TIMERS_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.M_TIMER_X),
		SCREEN_COORD(settings.M_TIMER_Y), "00:00");

	// Timer Desc
	CText text;
	CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
	CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE);
	CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
	if (settings.M_TIMERS_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
	CFont::SetColor(CRGBA(settings.M_TIMERS_R, settings.M_TIMERS_G, settings.M_TIMERS_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.M_TIMER_DESC_X),
		SCREEN_COORD(settings.M_TIMER_Y), (char *)TheText.Get("BB_19")); // Time

	std::string gxt[3] = { "ZER2_43", "BB_18", "TX_ADDS" };
	bool type[3] = { false, true, true };

	for (int i = 0; i < 3; i++) {
		float OFFSET_Y = (329.0f + (float)i*105.0f) * settings.M_STATUSTEXT_SPACE;

		// Status Text Desc
		CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
		CFont::SetAlignment(ALIGN_RIGHT);
		CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
		CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE);
		CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
		if (settings.M_TIMERS_OUTLINE != 0)
			CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
		CFont::SetColor(CRGBA(settings.M_STATUSBAR_R, settings.M_STATUSBAR_G, settings.M_STATUSBAR_B, 255));
		CFont::SetSlantRefPoint(0.0, 0.0);
		CFont::SetSlant(0.0);
		CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.M_STATUSTEXT_DESC_X),
			SCREEN_COORD(settings.M_STATUSTEXT_Y + OFFSET_Y), (char *)TheText.Get((char*)gxt[i].c_str()));

		if (!type[i]) {
			// Status Text Value
			CFont::SetScale(SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_X), SCREEN_MULTIPLIER(settings.M_TIMERS_SIZE_Y));
			CFont::SetAlignment(ALIGN_RIGHT);
			CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
			CFont::SetFontStyle(settings.M_TIMERS_FONTSTYLE);
			CFont::SetDropShadowPosition(settings.M_TIMERS_SHADOW);
			if (settings.M_TIMERS_OUTLINE != 0)
				CFont::SetOutlinePosition(settings.M_TIMERS_OUTLINE);
			CFont::SetColor(CRGBA(settings.M_STATUSBAR_R, settings.M_STATUSBAR_G, settings.M_STATUSBAR_B, 255));
			CFont::SetSlantRefPoint(0.0, 0.0);
			CFont::SetSlant(0.0);
			CFont::PrintString(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.M_STATUSTEXT_X),
				SCREEN_COORD(settings.M_STATUSTEXT_Y + OFFSET_Y), "50");
		}
		else {
			// Status Text Progressbar
			CSprite2d::DrawBarChart(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.M_STATUSBAR_X),
				SCREEN_COORD(settings.M_STATUSBAR_Y + OFFSET_Y + 14.0f*settings.M_STATUSTEXT_SPACE),
				(unsigned short)SCREEN_MULTIPLIER(settings.M_STATUSBAR_SIZE_X),
				(unsigned char)SCREEN_MULTIPLIER(settings.M_STATUSBAR_SIZE_Y),
				(unsigned char)50.0, 0, 0, settings.M_STATUSBAR_BORDER,
				CRGBA(settings.M_STATUSBAR_R, settings.M_STATUSBAR_G, settings.M_STATUSBAR_B, settings.M_STATUSBAR_A),
				CRGBA(0, 0, 0, settings.M_STATUSBAR_A));
		}
	}
}