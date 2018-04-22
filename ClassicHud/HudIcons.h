#pragma once

#include <plugin.h>
#include "Settings.h"
#include "Utility.h"

#include "CFont.h"
#include "CWorld.h"
#include "CTimer.h"
#include "CTxdStore.h"
#include "CFileMgr.h"

short& m_ItemToFlash = *(short*)0xBAB1DC;

CSprite2d hudIcons[10];

class HudIcons {
public:
	static void InstallPatches();

	static void HudTextures(int index);
	static void FontTextures(int index);
	static void FontData();
	static void ClassicHudTextures();
	static void ClassicHudTextureShutdown();

	static void PrintHealthString(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void PrintArmourString(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void PrintBreathString(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void PrintHealthBar(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void PrintArmourBar(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void PrintBreathBar(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void DrawHealth(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void DrawArmour(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
	static void DrawBreath(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine, BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor);
};

void HudIcons::InstallPatches() {
	plugin::patch::RedirectCall(0x589395, DrawHealth);
	plugin::patch::RedirectCall(0x58917A, DrawArmour);
	plugin::patch::RedirectCall(0x589252, DrawBreath);
}

void HudIcons::HudTextures(int index) {
	CTxdStore::LoadTxd(index, settings.HUD_TXD);
}

void HudIcons::FontTextures(int index) {
	CTxdStore::LoadTxd(index, settings.FONTS_TXD);
}

void HudIcons::FontData() {
	CFileMgr::OpenFile(settings.FONTS_DAT, "rb");
}

void HudIcons::ClassicHudTextures() {
	int v0 = CTxdStore::AddTxdSlot("classichud");
	CTxdStore::LoadTxd(v0, CLASSICHUD_TXD_PATH);
	CTxdStore::AddRef(v0);
	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(v0);
	hudIcons[0].SetTexture("health");
	hudIcons[1].SetTexture("armour");
	hudIcons[2].SetTexture("breath");
	hudIcons[3].SetTexture("star");
	hudIcons[4].SetTexture("arrow");
	hudIcons[5].SetTexture("bar_squareOutline");
	hudIcons[6].SetTexture("bar_roundOutline");
	hudIcons[7].SetTexture("star_Outline");
	hudIcons[8].SetTexture("sa_star");
	hudIcons[9].SetTexture("stories_star");
	CTxdStore::PopCurrentTxd();
}

void HudIcons::ClassicHudTextureShutdown() {
	hudIcons[0].Delete();
	hudIcons[1].Delete();
	hudIcons[2].Delete();
	hudIcons[3].Delete();
	hudIcons[4].Delete();
	hudIcons[5].Delete();
	hudIcons[6].Delete();
	hudIcons[7].Delete();
	hudIcons[8].Delete();
	hudIcons[9].Delete();
	int v0 = CTxdStore::FindTxdSlot("classichud");
	CTxdStore::RemoveTxdSlot(v0);
}

void HudIcons::PrintHealthString(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor) {
	int Percentage = 0;

	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.HEALTH_WIDTH), SCREEN_MULTIPLIER(settings.HEALTH_HEIGHT));
	CFont::SetColor(CRGBA(settings.HEALTH_R, settings.HEALTH_G, settings.HEALTH_B, settings.HEALTH_A));
	CFont::SetDropColor(CRGBA(0, 0, 0, settings.HEALTH_A));
	CFont::SetDropShadowPosition(1);
	//CFont::SetOutlinePosition(HUD_GLOBAL_OUTLINE);
	char str[10];
	CPed *playa = FindPlayerPed(0);

	if (Percentage == 1)
		sprintf(str, "%03d", (int)fPercentage);
	else
		sprintf(str, "%03d", (int)playa->m_fHealth);

	if (m_ItemToFlash != 3 || ShowFlashingItem(300, 300)) {
		if (CWorld::Players[0].m_nLastTimeArmourLost == CWorld::Players[0].m_nLastTimeEnergyLost || CWorld::Players[0].m_nLastTimeEnergyLost + 1000 < CTimer::m_snTimeInMilliseconds || ShowFlashingItem(150, 150))
		{
			CFont::PrintString(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTH_X),
				SCREEN_COORD(settings.HEALTH_Y),
				str);

			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
			hudIcons[0].Draw(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHICON_X + -2.0f),
				SCREEN_COORD(settings.HEALTHICON_Y + 2.0f),
				SCREEN_MULTIPLIER(settings.HEALTHICON_WIDTH), SCREEN_MULTIPLIER(settings.HEALTHICON_HEIGHT),
				CRGBA(0, 0, 0, settings.HEALTH_A));
			hudIcons[0].Draw(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHICON_X),
				SCREEN_COORD(settings.HEALTHICON_Y),
				SCREEN_MULTIPLIER(settings.HEALTHICON_WIDTH), SCREEN_MULTIPLIER(settings.HEALTHICON_HEIGHT),
				CRGBA(settings.HEALTH_R, settings.HEALTH_G, settings.HEALTH_B, settings.HEALTH_A));
			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
		}
	}
}

void HudIcons::PrintArmourString(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor) {
	int Percentage = 0;
	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.ARMOUR_SIZE_X), SCREEN_MULTIPLIER(settings.ARMOUR_SIZE_Y));
	CFont::SetColor(CRGBA(settings.ARMOUR_R, settings.ARMOUR_G, settings.ARMOUR_B, settings.ARMOUR_A));
	CFont::SetDropColor(CRGBA(0, 0, 0, settings.ARMOUR_A));
	CFont::SetDropShadowPosition(1);
	//CFont::SetOutlinePosition(HUD_GLOBAL_OUTLINE);
	char str[10];
	CPed *playa = FindPlayerPed(0);
	if (Percentage == 1)
		sprintf(str, "%03d", (int)fPercentage);
	else
		sprintf(str, "%03d", (int)playa->m_fArmour);

	if (m_ItemToFlash != 4 || ShowFlashingItem(300, 300)) {
		if (CWorld::Players[0].m_nLastTimeArmourLost == 0 || CWorld::Players[0].m_nLastTimeArmourLost + 1000 < CTimer::m_snTimeInMilliseconds || ShowFlashingItem(150, 150))
		{
			CFont::PrintString(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOUR_X),
				SCREEN_COORD(settings.ARMOUR_Y), str);

			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
			hudIcons[1].Draw(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURICON_X + -2.0f),
				SCREEN_COORD(settings.ARMOURICON_Y + 2.0f),
				SCREEN_MULTIPLIER(settings.ARMOURICON_SIZE_X),
				SCREEN_MULTIPLIER(settings.ARMOURICON_SIZE_Y),
				CRGBA(0, 0, 0, settings.ARMOUR_A));
			hudIcons[1].Draw(
				RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURICON_X),
				SCREEN_COORD(settings.ARMOURICON_Y),
				SCREEN_MULTIPLIER(settings.ARMOURICON_SIZE_X),
				SCREEN_MULTIPLIER(settings.ARMOURICON_SIZE_Y),
				CRGBA(settings.ARMOUR_R, settings.ARMOUR_G, settings.ARMOUR_B, settings.ARMOUR_A));
			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
		}
	}
}

void HudIcons::PrintBreathString(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetBackground(0, 0);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.BREATH_SIZE_X), SCREEN_MULTIPLIER(settings.BREATH_SIZE_Y));
	CFont::SetColor(CRGBA(settings.BREATH_R, settings.BREATH_G, settings.BREATH_B, settings.BREATH_A));
	CFont::SetDropColor(CRGBA(0, 0, 0, settings.BREATH_A));
	CFont::SetDropShadowPosition(1);
	char str[10];
	sprintf(str, "%03d", (int)fPercentage);

	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATH_X),
		SCREEN_COORD(settings.BREATH_Y), str);

	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
	hudIcons[2].Draw(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHICON_X + -2.0f),
		SCREEN_COORD(settings.BREATHICON_Y + 2.0f), SCREEN_MULTIPLIER(settings.BREATHICON_SIZE_X),
		SCREEN_MULTIPLIER(settings.BREATHICON_SIZE_Y), CRGBA(0, 0, 0, 255));
	hudIcons[2].Draw(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHICON_X),
		SCREEN_COORD(settings.BREATHICON_Y), SCREEN_MULTIPLIER(settings.BREATHICON_SIZE_X),
		SCREEN_MULTIPLIER(settings.BREATHICON_SIZE_Y),
		CRGBA(settings.BREATH_R, settings.BREATH_G, settings.BREATH_B, 255));
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
}

void HudIcons::PrintHealthBar(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	int SquareBar = 1;
	if (m_ItemToFlash != 3 || ShowFlashingItem(300, 300)) {
		if (CWorld::Players[0].m_nLastTimeArmourLost == CWorld::Players[0].m_nLastTimeEnergyLost || CWorld::Players[0].m_nLastTimeEnergyLost + 1000 < CTimer::m_snTimeInMilliseconds || ShowFlashingItem(150, 150))
		{
			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
			switch (settings.HEALTH_TYPE) {
			case 0: default: // Default Bar
				CSprite2d::DrawBarChart(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHBAR_X),
					SCREEN_COORD(settings.HEALTHBAR_Y),
					(unsigned short)SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_X),
					(unsigned char)SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_Y),
					(unsigned char)fPercentage, 0, 0, settings.HEALTHBAR_BORDER,
					CRGBA(settings.HEALTH_R, settings.HEALTH_G, settings.HEALTH_B, settings.HEALTH_A),
					CRGBA(0, 0, 0, settings.HEALTH_A));
				break;
			case 1: // Square Bar
				CSprite2d::DrawBarChart(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHBAR_X),
					SCREEN_COORD(settings.HEALTHBAR_Y),
					(unsigned short)SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_X),
					(unsigned char)SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_Y),
					(unsigned char)fPercentage, 0, 0, settings.HEALTHBAR_BORDER,
					CRGBA(settings.HEALTH_R, settings.HEALTH_G, settings.HEALTH_B, settings.HEALTH_A),
					CRGBA(0, 0, 0, settings.HEALTH_A));
				hudIcons[5].Draw(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHBAR_X),
					SCREEN_COORD(settings.HEALTHBAR_Y),
					SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_X),
					SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_Y),
					CRGBA(0, 0, 0, 255));
				break;
			case 2: // Rounded Bar
				CSprite2d::DrawBarChart(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHBAR_X + -5.0f),
					SCREEN_COORD(settings.HEALTHBAR_Y + 6.0f),
					(unsigned short)SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_X + -9.0f),
					(unsigned char)SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_Y + -11.0f),
					(unsigned char)fPercentage, 0, 0, 0,
					CRGBA(settings.HEALTH_R, settings.HEALTH_G, settings.HEALTH_B, settings.HEALTH_A),
					CRGBA(0, 0, 0, settings.HEALTH_A));
				hudIcons[6].Draw(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.HEALTHBAR_X),
					SCREEN_COORD(settings.HEALTHBAR_Y),
					SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_X),
					SCREEN_MULTIPLIER(settings.HEALTHBAR_SIZE_Y),
					CRGBA(0, 0, 0, 255));
				break;
			}
			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
		}
	}
}

void HudIcons::PrintArmourBar(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	int SquareBar = 1;
	if (m_ItemToFlash != 4 || ShowFlashingItem(300, 300)) {
		if (CWorld::Players[0].m_nLastTimeArmourLost == 0 || CWorld::Players[0].m_nLastTimeArmourLost + 1000 < CTimer::m_snTimeInMilliseconds || ShowFlashingItem(150, 150))
		{
			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
			switch (settings.ARMOUR_TYPE) {
			default: case 0: // Default Bar
				CSprite2d::DrawBarChart(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURBAR_X),
					SCREEN_COORD(settings.ARMOURBAR_Y),
					(unsigned short)SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_X),
					(unsigned char)SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_Y),
					(unsigned char)fPercentage, 0, 0, settings.ARMOURBAR_BORDER,
					CRGBA(settings.ARMOUR_R, settings.ARMOUR_G, settings.ARMOUR_B, settings.ARMOUR_A),
					CRGBA(0, 0, 0, settings.ARMOUR_A));
				break;
			case 1: // Square Bar
				CSprite2d::DrawBarChart(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURBAR_X),
					SCREEN_COORD(settings.ARMOURBAR_Y),
					(unsigned short)SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_X),
					(unsigned char)SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_Y),
					(unsigned char)fPercentage, 0, 0, settings.ARMOURBAR_BORDER,
					CRGBA(settings.ARMOUR_R, settings.ARMOUR_G, settings.ARMOUR_B, settings.ARMOUR_A),
					CRGBA(0, 0, 0, settings.ARMOUR_A));
				hudIcons[5].Draw(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURBAR_X),
					SCREEN_COORD(settings.ARMOURBAR_Y),
					SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_X),
					SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_Y),
					CRGBA(0, 0, 0, 255));
				break;
			case 2: // Rounded Bar
				CSprite2d::DrawBarChart(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURBAR_X + -5.0f),
					SCREEN_COORD(settings.ARMOURBAR_Y + 6.0f),
					(unsigned short)SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_X + -9.0f),
					(unsigned char)SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_Y + -11.0f),
					(unsigned char)fPercentage, 0, 0, 0,
					CRGBA(settings.ARMOUR_R, settings.ARMOUR_G, settings.ARMOUR_B, settings.ARMOUR_A),
					CRGBA(0, 0, 0, settings.ARMOUR_A));
				hudIcons[6].Draw(
					RsGlobal.maximumWidth - SCREEN_COORD(settings.ARMOURBAR_X),
					SCREEN_COORD(settings.ARMOURBAR_Y),
					SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_X),
					SCREEN_MULTIPLIER(settings.ARMOURBAR_SIZE_Y),
					CRGBA(0, 0, 0, 255));
				break;
			}
			RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
		}
	}
}

void HudIcons::PrintBreathBar(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	CPed *playa = FindPlayerPed(0);
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
	switch (settings.BREATH_TYPE) {
	default: case 0: // Default Bar
		CSprite2d::DrawBarChart(
			RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHBAR_X),
			SCREEN_COORD(settings.BREATHBAR_Y),
			(unsigned short)SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_X),
			(unsigned char)SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_Y),
			(unsigned char)fPercentage, 0, 0, settings.BREATHBAR_BORDER,
			CRGBA(settings.BREATH_R, settings.BREATH_G, settings.BREATH_B, settings.BREATH_A),
			CRGBA(0, 0, 0, settings.BREATH_A));
		break;
	case 1: // Square Bar
		CSprite2d::DrawBarChart(
			RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHBAR_X),
			SCREEN_COORD(settings.BREATHBAR_Y),
			(unsigned short)SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_X),
			(unsigned char)SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_Y),
			(unsigned char)fPercentage, 0, 0, settings.BREATHBAR_BORDER,
			CRGBA(settings.BREATH_R, settings.BREATH_G, settings.BREATH_B, settings.BREATH_A),
			CRGBA(0, 0, 0, settings.BREATH_A));
		hudIcons[5].Draw(
			RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHBAR_X),
			SCREEN_COORD(settings.BREATHBAR_Y),
			SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_X),
			SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_Y), CRGBA(0, 0, 0, 255));
		break;
	case 2: // Rounded Bar
		CSprite2d::DrawBarChart(
			RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHBAR_X + -5.0f),
			SCREEN_COORD(settings.BREATHBAR_Y + 6.0f),
			(unsigned short)SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_X + -9.0f),
			(unsigned char)SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_Y + -11.0f),
			(unsigned char)fPercentage, 0, 0, 0,
			CRGBA(settings.BREATH_R, settings.BREATH_G, settings.BREATH_B, settings.BREATH_A),
			CRGBA(0, 0, 0, settings.BREATH_A));
		hudIcons[6].Draw(
			RsGlobal.maximumWidth - SCREEN_COORD(settings.BREATHBAR_X),
			SCREEN_COORD(settings.BREATHBAR_Y),
			SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_X), SCREEN_MULTIPLIER(settings.BREATHBAR_SIZE_Y),
			CRGBA(0, 0, 0, 255));
		break;
	}
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
}

void HudIcons::DrawHealth(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	switch (settings.HEALTH_TYPE)
	{
	default: case 0: case 1: case 2:
		PrintHealthBar(posX, posY, wWidth, wHeight, fPercentage, drawBlueLine,
			drawPercentage, drawBorder, dwColor, dwForeColor);
		break;
	case 3:
		PrintHealthString(posX, posY, wWidth, wHeight, fPercentage, drawBlueLine,
			drawPercentage, drawBorder, dwColor, dwForeColor);
		break;
	}
}

void HudIcons::DrawArmour(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	switch (settings.ARMOUR_TYPE) {
	default: case 0: case 1: case 2:
		PrintArmourBar(posX, posY, wWidth, wHeight, fPercentage, drawBlueLine,
			drawPercentage, drawBorder, dwColor, dwForeColor);
		break;
	case 3:
		PrintArmourString(posX, posY, wWidth, wHeight, fPercentage, drawBlueLine,
			drawPercentage, drawBorder, dwColor, dwForeColor);
		break;
	}
}

void HudIcons::DrawBreath(float posX, float posY, WORD wWidth, WORD wHeight, float fPercentage, BYTE drawBlueLine,
	BYTE drawPercentage, BYTE drawBorder, CRGBA dwColor, CRGBA dwForeColor)
{
	switch (settings.BREATH_TYPE) {
	default: case 0: case 1: case 2:
		PrintBreathBar(posX, posY, wWidth, wHeight, fPercentage, drawBlueLine,
			drawPercentage, drawBorder, dwColor, dwForeColor);
		break;
	case 3:
		PrintBreathString(posX, posY, wWidth, wHeight, fPercentage, drawBlueLine,
			drawPercentage, drawBorder, dwColor, dwForeColor);
		break;
	}
}

