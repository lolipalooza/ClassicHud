#pragma once

#include <plugin.h>
#include "Settings.h"

#include "CMessages.h"
#include "CHud.h"
#include "CFont.h"
#include "CTimer.h"
#include "CCamera.h"
#include "CText.h"

#define g_pHelpMessage ((char *)0xBAA7A0)
#define g_HelpMessageState (*(__int32 *)0xBAA474)
#define g_HelpMessageTimer (*(signed __int32 *)0xBAA47C)
#define g_HelpMessageFadeTimer (*(signed __int32 *)0xBAA478)
#define g_pHelpMessageToPrint ((char *)0xBAA480)
#define g_fTextBoxNumLines (*(float *)0xBAA460)
#define PLAYONESHOT(id, volume) ((void (__thiscall *)(unsigned int, unsigned short, float, float))0x506EA0)(0xB6BC90, id, volume, 1.0)
#define Camera_WidescreenOn (*(unsigned __int8 *)0xB6F065)
#define bTextBoxPermanent2 (*(__int8 *)0xBAA464)
#define m_HelpMessageQuick (*(unsigned __int8 *)0xBAA472)
#define Cutscene_Running (*(unsigned __int8 *)0xB5F851)
#define g_HelpMessageStatId (*(unsigned __int16 *)0xBAA470)
#define g_filenameBuffer ((char *)0xB71670)
#define flt_8D0938 (*(float *)0x8D0938)
#define GetGroupMembersCount(groupId) ((unsigned int (__thiscall *)(unsigned int))0x5F6AA0)(groupId * 0x2D4 + 0xC09928)
#define GetPlayerStat(statid) ((float (__cdecl *)(unsigned short))0x558E40)(statid)
#define dword_BAA468 (*(float *)0xBAA468)
#define g_fScriptTextBoxesWidth (*(float *)0x8D0934)
#define StatMax (*(unsigned __int16 *)0xBAA46C)
#define g_BigMessage0 ((char *)0xBAACC0)
#define g_BigMessage4 ((char *)0xBAAEC0)
#define byte_96C014 ((char *)0x96C014)
#define Menu_WidescreenOn (*(unsigned __int8 *)0xBA6793)
#define ZoneToPrint ((char *)0xBAB1D0)

class HelpText {
public:
	static void InstallPatches();
	static float GetHelpBoxXShift();
	static void DrawHelpText();
	static void TestHelpText();
	static void TestHelpText_WithStats(int stat_id, bool inc_flag);
};

void HelpText::InstallPatches() {
	plugin::patch::RedirectCall(0x58FCFA, DrawHelpText);
}

float HelpText::GetHelpBoxXShift() {
	// if radar drawn
	if ((*(unsigned __int8 *)0xBA676C) != 2)
	{
		if (FindPlayerVehicle(-1, 0) && FindPlayerVehicle(-1, 0)->m_nModelIndex != 0x21B &&
			((*(unsigned __int32 *)((unsigned int)FindPlayerVehicle(-1, 0) + 0x594)) == 4 ||
			(*(unsigned __int32 *)((unsigned int)FindPlayerVehicle(-1, 0) + 0x594)) == 3))
			return settings.fTextBoxPosnXWithRadarAndPlane;
		else if (FindPlayerPed(-1) && FindPlayerPed(-1)->m_aWeapons[FindPlayerPed(-1)->m_nActiveWeaponSlot].m_nType == WEAPON_PARACHUTE)
			return settings.fTextBoxPosnXWithRadarAndPlane;
		else return settings.fTextBoxPosnXWithRadar;
	}
	else return settings.fTextBoxPosnX;
}

void HelpText::DrawHelpText() {
	char baseY;
	float alpha;
	float posX;
	float progress;
	if (g_pHelpMessage[0])
	{
		if (!CMessages::StringCompare(g_pHelpMessage, CHud::m_pLastHelpMessage, 400))
		{
			switch (g_HelpMessageState)
			{
			case 0: // STATE_FREE_TO_USE
				g_HelpMessageState = 2; // STATE_FADE_OUT
				g_HelpMessageTimer = 0;
				g_HelpMessageFadeTimer = 0;
				CMessages::StringCopy(g_pHelpMessageToPrint, g_pHelpMessage, 400);
				CFont::SetAlignment(ALIGN_LEFT);
				CFont::SetJustify(false);
				CFont::SetWrapx(SCREEN_MULTIPLIER(28 + 350 - 16));
				CFont::SetFontStyle(FONT_SUBTITLES);
				CFont::SetBackground(true, true);
				CFont::SetDropShadowPosition(0);
				g_fTextBoxNumLines = (float)CFont::GetNumberLinesNoPrint(SCREEN_COORD(34.0f), SCREEN_COORD(28.0f), g_pHelpMessageToPrint) + 3.0f;
				CFont::SetWrapx((float)RsGlobal.maximumWidth);
				PLAYONESHOT(32, 0.0);
				break;
			case 1:
			case 2:
			case 3:
			case 4:
				g_HelpMessageState = 4; // STATE_REPLACE
				g_HelpMessageTimer = 5;
				break;
			default:
				break;
			}
			CMessages::StringCopy(CHud::m_pLastHelpMessage, g_pHelpMessage, 400);
		}
		alpha = 170.0;
		if (g_HelpMessageState)
		{
			switch (g_HelpMessageState)
			{
			case 2: // FADE_OUT
				if (!Camera_WidescreenOn)
				{
					g_HelpMessageFadeTimer += 2 * (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
					if (g_HelpMessageFadeTimer > 0)
					{
						g_HelpMessageFadeTimer = 0;
						g_HelpMessageState = 1; // STATE_IDLE
					}
					alpha = g_HelpMessageFadeTimer * 0.001f * 200.0f;
				}
				break;
			case 3: // FADE_IN
				g_HelpMessageFadeTimer -= 2 * (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
				if (g_HelpMessageFadeTimer < 0 || Camera_WidescreenOn)
				{
					g_HelpMessageFadeTimer = 0;
					g_HelpMessageState = 0; // STATE_FREE_TO_USE
				}
				alpha = g_HelpMessageFadeTimer * 0.001f * 200.0f;
				break;
			case 4: // REPLACE
				g_HelpMessageFadeTimer -= 2 * (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
				if (g_HelpMessageFadeTimer < 0)
				{
					g_HelpMessageFadeTimer = 0;
					g_HelpMessageState = 2; // FADE_OUT
					CMessages::StringCopy(g_pHelpMessageToPrint, CHud::m_pLastHelpMessage, 400);
				}
				alpha = g_HelpMessageFadeTimer * 0.001f * 200.0f;
				break;
			case 1: // IDLE
				alpha = 200.0;
				g_HelpMessageFadeTimer = 600;
				if (!bTextBoxPermanent2)
				{
					if (g_HelpMessageTimer > g_fTextBoxNumLines * 1000.0 || m_HelpMessageQuick && g_HelpMessageTimer > 3000)
					{
						g_HelpMessageState = 3; // FADE_IN
						g_HelpMessageFadeTimer = 600;
					}
				}
				break;
			default:
				break;
			}
			if (!Cutscene_Running)
			{
				g_HelpMessageTimer += (int)(CTimer::ms_fTimeStep * 0.02f * 1000.0f);
				CFont::SetAlphaFade(alpha);
				CFont::SetProp(true);
				CFont::SetScale(SCREEN_MULTIPLIER(settings.fTextBoxFontScaleX), SCREEN_MULTIPLIER(settings.fTextBoxFontScaleY));
				if (g_HelpMessageStatId)
				{
					if (Camera_WidescreenOn)
					{
						CFont::SetAlphaFade(255.0);
						return;
					}
					if (g_HelpMessageStatId >= 10)
					{
						if (g_HelpMessageStatId >= 100)
							sprintf(g_filenameBuffer, "STAT%d", g_HelpMessageStatId);
						else
							sprintf(g_filenameBuffer, "STAT0%d", g_HelpMessageStatId);
					}
					else
						sprintf(g_filenameBuffer, "STAT00%d", g_HelpMessageStatId);
					CFont::SetAlignment(ALIGN_LEFT);
					CFont::SetJustify(false);
					CFont::SetWrapx((float)RsGlobal.maximumWidth);
					CFont::SetFontStyle(FONT_SUBTITLES);
					CFont::SetBackground(true, true);
					CFont::SetDropShadowPosition(0);
					CFont::SetBackgroundColor(CRGBA(0, 0, 0, (unsigned char)alpha));
					CFont::SetColor(CRGBA(255, 255, 255, 255));
					posX = CFont::GetStringWidth((char *)TheText.Get(g_filenameBuffer), 1, 0) + SCREEN_MULTIPLIER(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f;
					CFont::SetWrapx(SCREEN_MULTIPLIER(164.0f) + posX + 4.0f + settings.TEXTBOX_STAT_BORDER);
					CFont::PrintString(
						SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f,
						SCREEN_COORD((150.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY),
						(char *)TheText.Get(g_filenameBuffer));
					if (g_HelpMessageStatId == 336)
						progress = (float)GetGroupMembersCount(FindPlayerPed(-1)->m_pPlayerData->m_nPlayerGroup);
					else
						progress = GetPlayerStat(g_HelpMessageStatId);

					CSprite2d::DrawBarChart(
						posX + SCREEN_COORD(15.0),
						SCREEN_COORD((157.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY + 4.0f + settings.TEXTBOX_STATBAR_Y),
						(unsigned short)SCREEN_MULTIPLIER(settings.TEXTBOX_STATBAR_SIZE_X),
						(unsigned char)SCREEN_MULTIPLIER(settings.TEXTBOX_STATBAR_SIZE_Y),
						fmax(1.0f / StatMax * progress * 100.0f, 2.0f),
						(unsigned char)fmax((1.0f / StatMax) * dword_BAA468 * 100.0f, 3.0f),
						0, 0, CRGBA(settings.TEXTBOX_STATBAR_R, settings.TEXTBOX_STATBAR_G, settings.TEXTBOX_STATBAR_B, 255),
						(g_pHelpMessageToPrint[0] == '+')
						? CRGBA(settings.TEXTBOX_STATBAR_ADD_R, settings.TEXTBOX_STATBAR_ADD_G, settings.TEXTBOX_STATBAR_ADD_B, 255)
						: CRGBA(settings.TEXTBOX_STATBAR_SUBS_R, settings.TEXTBOX_STATBAR_SUBS_G, settings.TEXTBOX_STATBAR_SUBS_B, 255));
					CFont::SetColor(CRGBA(255, 255, 255, 255));
					CFont::PrintString(
						posX + SCREEN_COORD(25.0f + settings.TEXTBOX_STATBAR_SIZE_X),
						SCREEN_COORD((153.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY),
						g_pHelpMessageToPrint);
				}
				else
				{
					if (g_BigMessage0[0] || g_BigMessage4[0] || byte_96C014[0])
					{
						CFont::SetAlphaFade(255.0);
						return;
					}
					CFont::SetAlignment(ALIGN_LEFT);
					CFont::SetJustify(false);
					if (g_fScriptTextBoxesWidth == 200.0)
					{
						CFont::SetWrapx(SCREEN_MULTIPLIER(GetHelpBoxXShift() + settings.fTextBoxWidth - settings.fTextBoxBorderSize) - 4.0f);
					}
					else
						CFont::SetWrapx(SCREEN_MULTIPLIER(GetHelpBoxXShift() + (g_fScriptTextBoxesWidth - settings.fTextBoxBorderSize)) - 4.0f);
					CFont::SetFontStyle(FONT_SUBTITLES);
					CFont::SetBackground(true, true);
					CFont::SetDropShadowPosition(0);
					CFont::SetBackgroundColor(CRGBA(0, 0, 0, (unsigned char)alpha));
					CFont::SetColor(CRGBA(255, 255, 255, 255));
					baseY = 0;
					if (Camera_WidescreenOn && !Menu_WidescreenOn)
						baseY = 56;
					CFont::PrintString(
						SCREEN_COORD(GetHelpBoxXShift() + settings.fTextBoxBorderSize) + 4.0f,
						SCREEN_COORD(((float)baseY + 150.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY),
						g_pHelpMessageToPrint);
				}
				CFont::SetWrapx((float)RsGlobal.maximumWidth);
				CFont::SetAlphaFade(255.0);
				return;
			}
		}
	}
	else
		g_HelpMessageState = 0;
}

void HelpText::TestHelpText() {
	float alpha = 200.0f;

	CFont::SetProp(true);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.fTextBoxFontScaleX), SCREEN_MULTIPLIER(settings.fTextBoxFontScaleY));
	
	CFont::SetAlignment(ALIGN_LEFT);
	CFont::SetJustify(false);
	if (g_fScriptTextBoxesWidth == 200.0)
	{
		CFont::SetWrapx(SCREEN_MULTIPLIER(settings.fTextBoxPosnX + settings.fTextBoxWidth - settings.fTextBoxBorderSize) - 4.0f);
	}
	else
		CFont::SetWrapx(SCREEN_MULTIPLIER(settings.fTextBoxPosnX + (g_fScriptTextBoxesWidth - settings.fTextBoxBorderSize)) - 4.0f);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetBackground(true, true);
	CFont::SetDropShadowPosition(0);
	CFont::SetBackgroundColor(CRGBA(0, 0, 0, (unsigned char)alpha));
	CFont::SetColor(CRGBA(255, 255, 255, 255));
	float baseY = 0;
	if (Camera_WidescreenOn && !Menu_WidescreenOn)
		baseY = 56;
	CFont::PrintString(
		SCREEN_COORD(settings.fTextBoxPosnX + settings.fTextBoxBorderSize) + 4.0f,
		SCREEN_COORD(((float)baseY + 150.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY),
		(char *)TheText.Get("IE23")); // ~s~This vehicle is not required for export.
}

void HelpText::TestHelpText_WithStats(int stat_id, bool inc_flag) {
	char stat_gxt[100];
	float alpha = 200.0f;
	float posX;
	float progress = inc_flag ? 50.0f : 40.0f;
	float progressAdd = inc_flag ? 25.0f : 35.0f;

	CFont::SetProp(true);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.fTextBoxFontScaleX), SCREEN_MULTIPLIER(settings.fTextBoxFontScaleY));
	if (stat_id >= 10)
	{
		if (stat_id >= 100)
			sprintf(stat_gxt, "STAT%d", stat_id);
		else
			sprintf(stat_gxt, "STAT0%d", stat_id);
	}
	CFont::SetAlignment(ALIGN_LEFT);
	CFont::SetJustify(false);
	CFont::SetWrapx((float)RsGlobal.maximumWidth);
	CFont::SetFontStyle(FONT_SUBTITLES);
	CFont::SetBackground(true, true);
	CFont::SetDropShadowPosition(0);
	CFont::SetBackgroundColor(CRGBA(0, 0, 0, (unsigned char)alpha));
	CFont::SetColor(CRGBA(255, 255, 255, 255));
	posX = CFont::GetStringWidth((char *)TheText.Get(stat_gxt), 1, 0) + SCREEN_MULTIPLIER(settings.fTextBoxPosnX + settings.fTextBoxBorderSize) + 4.0f;
	CFont::SetWrapx(SCREEN_MULTIPLIER(164.0f) + posX + 4.0f + settings.TEXTBOX_STAT_BORDER);
	CFont::PrintString(
		SCREEN_COORD(settings.fTextBoxPosnX + settings.fTextBoxBorderSize) + 4.0f,
		SCREEN_COORD((150.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY),
		(char *)TheText.Get(stat_gxt));
	CSprite2d::DrawBarChart(
		posX + SCREEN_COORD(15.0),
		SCREEN_COORD((157.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY + 4.0f + settings.TEXTBOX_STATBAR_Y),
		(unsigned short)SCREEN_MULTIPLIER(settings.TEXTBOX_STATBAR_SIZE_X),
		(unsigned char)SCREEN_MULTIPLIER(settings.TEXTBOX_STATBAR_SIZE_Y),
		progress, progressAdd,
		0, 0, CRGBA(settings.TEXTBOX_STATBAR_R, settings.TEXTBOX_STATBAR_G, settings.TEXTBOX_STATBAR_B, 255),
		inc_flag
		? CRGBA(settings.TEXTBOX_STATBAR_ADD_R, settings.TEXTBOX_STATBAR_ADD_G, settings.TEXTBOX_STATBAR_ADD_B, 255)
		: CRGBA(settings.TEXTBOX_STATBAR_SUBS_R, settings.TEXTBOX_STATBAR_SUBS_G, settings.TEXTBOX_STATBAR_SUBS_B, 255));
	CFont::SetColor(CRGBA(255, 255, 255, 255));
	CFont::PrintString(
		posX + SCREEN_COORD(25.0f + settings.TEXTBOX_STATBAR_SIZE_X),
		SCREEN_COORD((153.0f - flt_8D0938) * 0.6f) + SCREEN_COORD(settings.fTextBoxPosnY),
		inc_flag ? "+" : "-");
}