#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CHud.h"
#include "CCamera.h"
#include "CText.h"

class Subtitles {
public:
	static void InstallPatches();
	static void DrawSubtitlesUnused(float x, float y, char *str);
	static void DrawSubtitles(float x, float y, char *str);
	static void TestSubtitles();
	static void TestSubtitlesVitalstats();
};

void Subtitles::InstallPatches() {
	plugin::patch::RedirectCall(0x58C68A, DrawSubtitles);
}

void Subtitles::DrawSubtitlesUnused(float x, float y, char *str)
{
	CFont::SetBackground(0, 0);
	CFont::SetColor(CRGBA(255, 255, 255, 255));
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetDropShadowPosition(settings.SUBTITLES_SHADOW);
	if (settings.SUBTITLES_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.SUBTITLES_OUTLINE);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_X), SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_Y));
	CFont::PrintString(SCREEN_COORD_CENTER_LEFT(settings.SUBTITLES_X), SCREEN_COORD_BOTTOM(settings.SUBTITLES_Y), str);
}

void Subtitles::DrawSubtitles(float x, float y, char *str)
{
	float subtitles_x[5] = { 20.0f, 151.0f, 22.0f, 0.0f, 0.0f },
		subtitles_y[5] = { 105.0f, 62.0f, 105.0f, 0.0f, 0.0f },
		subtitles_size_x[5] = { 0.58f, 0.472f, 0.621f, 0.0f, 0.0f },
		subtitles_size_y[5] = { 1.22f, 1.08f, 1.22f, 0.0f, 0.0f },
		subtitles_linewidth[5] = { 20.0f, -45.0f, 20.0f, 0.0f, 0.0f },
		subtitles_vitalstats_x = 0.0f,
		subtitles_vitalstats_y[5] = { 105.0f, 62.0f, 105.0f, 0.0f, 0.0f },
		subtitles_vitalstats_size_x[5] = { 0.58f, 0.472f, 0.621f, 0.0f, 0.0f },
		subtitles_vitalstats_size_y[5] = { 1.22f, 1.08f, 1.22f, 0.0f, 0.0f },
		subtitles_vitalstats_linewidth[5] = { 20.0f, -45.0f, 20.0f, 0.0f, 0.0f },
		subtitles_widescreen_x = 0.0f,
		subtitles_widescreen_y = 0.0f,
		subtitles_widescreen_size_x = 0.0f,
		subtitles_widescreen_size_y = 0.0f,
		subtitles_widescreen_linewidth = 0.0f;
	int shadow[5] = { 2, 1, 0, 0, 0 },
		outline[5] = { 0, 0, 0, 0, 0 };
	int subt_r = 225, subt_g = 225, subt_b = 225;

	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetColor(CRGBA(settings.SUBTITLES_R, settings.SUBTITLES_G, settings.SUBTITLES_B, 255));
	CFont::SetDropShadowPosition(settings.SUBTITLES_SHADOW);
	if (settings.SUBTITLES_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.SUBTITLES_OUTLINE);
	if (!TheCamera.m_bWideScreenOn)
	{
		CFont::SetScaleForCurrentlanguage(
			SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_X),
			SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_Y));
		if (CHud::bDrawingVitalStats)
		{
			CFont::SetScaleForCurrentlanguage(
				SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_X * settings.SUBTITLES_VITALSTATS_SIZE_X),
				SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_Y));
			CFont::SetCentreSize((RsGlobal.maximumWidth
				- 0.0015625f * RsGlobal.maximumWidth * settings.SUBTITLES_LINEWIDTH
				- 8.0f * (0.0015625f * RsGlobal.maximumWidth)
				- (0.0015625f * RsGlobal.maximumWidth * 140.0f
					+ 8.0f * (0.0015625f * RsGlobal.maximumWidth))) * settings.SUBTITLES_VITALSTATS_SIZE_X);
			y = SCREEN_COORD_BOTTOM(settings.SUBTITLES_Y);
			x = SCREEN_COORD_CENTER_LEFT(settings.SUBTITLES_X + settings.SUBTITLES_VITALSTATS_X);
		}
		else
		{
			CFont::SetCentreSize(RsGlobal.maximumWidth
				- 0.0015625f * RsGlobal.maximumWidth * settings.SUBTITLES_LINEWIDTH
				- 8.0f * (0.0015625f * RsGlobal.maximumWidth)
				- (0.0015625f * RsGlobal.maximumWidth * 140.0f
					+ 8.0f * (0.0015625f * RsGlobal.maximumWidth)));
			y = SCREEN_COORD_BOTTOM(settings.SUBTITLES_Y);
			x = SCREEN_COORD_CENTER_LEFT(settings.SUBTITLES_X);
		}
	}
	CFont::PrintString(x, y, CHud::m_Message);
}

void Subtitles::TestSubtitles()
{
	CFont::SetBackground(0, 0);
	CFont::SetScaleForCurrentlanguage(
		SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_X),
		SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth
		- 0.0015625f * RsGlobal.maximumWidth * settings.SUBTITLES_LINEWIDTH
		- 8.0f * (0.0015625f * RsGlobal.maximumWidth)
		- (0.0015625f * RsGlobal.maximumWidth * 140.0f
			+ 8.0f * (0.0015625f * RsGlobal.maximumWidth)));
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(settings.SUBTITLES_SHADOW);
	if (settings.SUBTITLES_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.SUBTITLES_OUTLINE);
	CFont::SetColor(CRGBA(settings.SUBTITLES_R, settings.SUBTITLES_G, settings.SUBTITLES_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString(
		SCREEN_COORD_CENTER_LEFT(settings.SUBTITLES_X),
		SCREEN_COORD_BOTTOM(settings.SUBTITLES_Y),
		(char *)TheText.Get("IE23")); // ~s~This vehicle is not required for export.
}

void Subtitles::TestSubtitlesVitalstats()
{
	CFont::SetBackground(0, 0);
	CFont::SetScaleForCurrentlanguage(
		SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_X * settings.SUBTITLES_VITALSTATS_SIZE_X),
		SCREEN_MULTIPLIER(settings.SUBTITLES_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize((RsGlobal.maximumWidth
		- 0.0015625f * RsGlobal.maximumWidth * settings.SUBTITLES_LINEWIDTH
		- 8.0f * (0.0015625f * RsGlobal.maximumWidth)
		- (0.0015625f * RsGlobal.maximumWidth * 140.0f
			+ 8.0f * (0.0015625f * RsGlobal.maximumWidth))) * settings.SUBTITLES_VITALSTATS_SIZE_X);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(settings.SUBTITLES_SHADOW);
	if (settings.SUBTITLES_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.SUBTITLES_OUTLINE);
	CFont::SetColor(CRGBA(settings.SUBTITLES_R, settings.SUBTITLES_G, settings.SUBTITLES_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString(
		SCREEN_COORD_CENTER_LEFT(settings.SUBTITLES_X + settings.SUBTITLES_VITALSTATS_X),
		SCREEN_COORD_BOTTOM(settings.SUBTITLES_Y),
		(char *)TheText.Get("IE23")); // ~s~This vehicle is not required for export.
}

