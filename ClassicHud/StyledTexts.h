#pragma once

#include <plugin.h>
#include "Settings.h"
#include "TestMessage.h"

#include "CFont.h"
#include "CHud.h"

class StyledTexts {
public:
	static void InstallPatches();
	static void DrawSuccessFailedMessage(float x, float y, char* str);
	static void DrawMissionTitle(float x, float y, char* str);
	static void DrawBustedWastedMessage(float x, float y, char *str);
	void static DrawOddJobMessage4(float x, float y, char* str);
	void static DrawOddJobMessage5(float x, float y, char* str);
	void static DrawOddJobMessage6(float x, float y, char* str);
	void static DrawOddJobMessage7(float x, float y, char* str);
	
	static void TestSuccessFailedMessage();
	static void TestMissionTitle();
	static void TestBustedWastedMessage();
	static void TestOddJobMessage4();
	static void TestOddJobMessage5();
	static void TestOddJobMessage6();
	static void TestOddJobMessage7();

	static void TestStyled1_2Lines_And_NotSt3();
	static void TestStyled1_And_St4OrSt6(int st4or6_id);
};

void StyledTexts::InstallPatches() {
	plugin::patch::RedirectCall(0x58CA30, DrawSuccessFailedMessage);
	plugin::patch::RedirectCall(0x58D470, DrawMissionTitle);
	plugin::patch::RedirectCall(0x58CC6A, DrawBustedWastedMessage);
	plugin::patch::RedirectCall(0x58CFA0, DrawOddJobMessage4);
	plugin::patch::RedirectCall(0x58CD99, DrawOddJobMessage5);
	plugin::patch::RedirectCall(0x58D21A, DrawOddJobMessage6);
	plugin::patch::RedirectCall(0x58CE9E, DrawOddJobMessage7);
}

void StyledTexts::DrawSuccessFailedMessage(float x, float y, char* str)
{
	float pos_y = SCREEN_COORD(settings.STYLED1_Y),
		pos_x = (float)(RsGlobal.maximumWidth / 2);

	if (CHud::m_BigMessage[3][0] || CHud::m_BigMessage[5][0]) // Styled 4 or 6
		pos_y += settings.STYLED1_Y1;
	else if (!CHud::m_BigMessage[2][0] && CFont::GetNumberLinesNoPrint(pos_x, pos_y, str) > 1) // Styled 3
		pos_y += settings.STYLED1_Y2;
	CFont::SetScale(SCREEN_MULTIPLIER(settings.STYLED1_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED1_SIZE_Y));
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 590.0f);
	CFont::SetFontStyle(FONT_PRICEDOWN);
	CFont::SetDropShadowPosition(settings.STYLED1_SHADOW);
	if (settings.STYLED1_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED1_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED1_R, settings.STYLED1_G, settings.STYLED1_B, (unsigned char)BigMessageAlpha[0]));
	CFont::PrintString(pos_x, pos_y, str);
}

void StyledTexts::DrawMissionTitle(float x, float y, char* str)
{
	CFont::SetAlignment(ALIGN_RIGHT);
	CFont::SetFontStyle(settings.MT_FONTSTYLE);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.MT_SIZE_X), SCREEN_MULTIPLIER(settings.MT_SIZE_Y));
	CFont::SetDropShadowPosition(settings.MT_SHADOW);
	if (settings.MT_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.MT_OUTLINE);
	CFont::SetColor(CRGBA(settings.MT_R, settings.MT_G, settings.MT_B, (unsigned char)BigMessageAlpha[1]));
	CFont::PrintStringFromBottom(RsGlobal.maximumWidth - SCREEN_COORD(settings.MT_POS_X), SCREEN_COORD(settings.MT_POS_Y), str);
}

void StyledTexts::DrawBustedWastedMessage(float x, float y, char *str) {
	CFont::SetAlignment((eFontAlignment)settings.WB_ALIGN);
	CFont::SetDropShadowPosition(settings.WB_SHADOW);
	if (settings.WB_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.WB_OUTLINE);
	CFont::SetFontStyle(settings.WB_FONTSTYLE);
	CFont::SetScale(SCREEN_MULTIPLIER(settings.WB_SIZE_X), SCREEN_MULTIPLIER(settings.WB_SIZE_Y));
	CFont::SetColor(CRGBA(settings.WB_R, settings.WB_G, settings.WB_B, (unsigned char)BigMessageAlpha[2]));
	CFont::PrintStringFromBottom(RsGlobal.maximumWidth - SCREEN_COORD(settings.WB_POS_X), SCREEN_COORD(settings.WB_POS_Y), str);
}

void StyledTexts::DrawOddJobMessage4(float x, float y, char* str)
{
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED4_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED4_SIZE_Y));
	CFont::SetAlignment((eFontAlignment)settings.STYLED4_ALIGN);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 500.0f);
	CFont::SetFontStyle(settings.STYLED4_FONTSTYLE);
	CFont::SetDropShadowPosition(settings.STYLED4_SHADOW);
	if (settings.STYLED4_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED4_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED4_R, settings.STYLED4_G, settings.STYLED4_B, 255));
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.STYLED4_X), SCREEN_COORD(settings.STYLED4_Y), str);
}

void StyledTexts::DrawOddJobMessage5(float x, float y, char* str)
{
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED5_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED5_SIZE_Y));
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 600.0f);
	CFont::SetFontStyle(settings.STYLED5_FONTSTYLE);
	CFont::SetDropShadowPosition(settings.STYLED5_SHADOW);
	if (settings.STYLED5_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED5_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED5_R, settings.STYLED5_G, settings.STYLED5_B, 255));
	CFont::PrintStringFromBottom((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.STYLED5_Y), str);
}

void StyledTexts::DrawOddJobMessage6(float x, float y, char* str)
{
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED6_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED6_SIZE_Y));
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 500.0f);
	CFont::SetFontStyle(settings.STYLED6_FONTSTYLE);
	CFont::SetDropShadowPosition(settings.STYLED6_SHADOW);
	if (settings.STYLED6_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED6_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED6_R, settings.STYLED6_G, settings.STYLED6_B, 255));
	CFont::PrintString((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.STYLED6_Y), str);
}

void StyledTexts::DrawOddJobMessage7(float x, float y, char* str)
{
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED7_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED7_SIZE_Y));
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 500.0f);
	CFont::SetFontStyle(settings.STYLED7_FONTSTYLE);
	CFont::SetDropShadowPosition(settings.STYLED7_SHADOW);
	if (settings.STYLED7_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED7_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED7_R, settings.STYLED7_G, settings.STYLED7_B, 255));
	CFont::PrintString((float)(RsGlobal.maximumWidth / 2), SCREEN_COORD(settings.STYLED7_Y), str);
}

void StyledTexts::TestSuccessFailedMessage()
{
	float pos_y = SCREEN_COORD(settings.STYLED1_Y),
		pos_x = (float)(RsGlobal.maximumWidth / 2);
	TestMessage::Draw(pos_x, pos_y, settings.STYLED1_SIZE_X, settings.STYLED1_SIZE_Y, ALIGN_CENTER,
		RsGlobal.maximumWidth * 0.0015625f * 590.0f,
		settings.STYLED1_SHADOW, settings.STYLED1_OUTLINE, FONT_PRICEDOWN,
		CRGBA(settings.STYLED1_R, settings.STYLED1_G, settings.STYLED1_B, 255), (char *)TheText.Get("M_FAIL")); // MISSION FAILED!
}

void StyledTexts::TestStyled1_2Lines_And_NotSt3() {
	float pos_y = SCREEN_COORD(settings.STYLED1_Y) + settings.STYLED1_Y2,
		pos_x = (float)(RsGlobal.maximumWidth / 2);
	TestMessage::Draw(pos_x, pos_y, settings.STYLED1_SIZE_X, settings.STYLED1_SIZE_Y, ALIGN_CENTER,
		RsGlobal.maximumWidth * 0.0015625f * 590.0f,
		settings.STYLED1_SHADOW, settings.STYLED1_OUTLINE, FONT_PRICEDOWN,
		CRGBA(settings.STYLED1_R, settings.STYLED1_G, settings.STYLED1_B, 255), "This is 2 lines~n~message!");
}

void StyledTexts::TestStyled1_And_St4OrSt6(int st4or6_id) {
	float pos_y = SCREEN_COORD(settings.STYLED1_Y) + settings.STYLED1_Y1,
		pos_x = (float)(RsGlobal.maximumWidth / 2);
	TestMessage::Draw(pos_x, pos_y, settings.STYLED1_SIZE_X, settings.STYLED1_SIZE_Y, ALIGN_CENTER,
		RsGlobal.maximumWidth * 0.0015625f * 590.0f,
		settings.STYLED1_SHADOW, settings.STYLED1_OUTLINE, FONT_PRICEDOWN,
		CRGBA(settings.STYLED1_R, settings.STYLED1_G, settings.STYLED1_B, 255), (char *)TheText.Get("M_FAIL")); // MISSION FAILED!

	if (st4or6_id == 4)
		StyledTexts::TestOddJobMessage4();
	else StyledTexts::TestOddJobMessage6();
}

void StyledTexts::TestMissionTitle()
{
	TestMessage::Draw(RsGlobal.maximumWidth - SCREEN_COORD(settings.MT_POS_X),
		SCREEN_COORD(settings.MT_POS_Y), settings.MT_SIZE_X, settings.MT_SIZE_Y, ALIGN_RIGHT,
		RsGlobal.maximumWidth * 0.0015625f * 590.0f,
		settings.MT_SHADOW, settings.MT_OUTLINE, settings.MT_FONTSTYLE,
		CRGBA(settings.MT_R, settings.MT_G, settings.MT_B, 255), (char *)TheText.Get("BEEFY")); // Beefy Baron
}

void StyledTexts::TestBustedWastedMessage()
{
	TestMessage::Draw(RsGlobal.maximumWidth - SCREEN_COORD(settings.WB_POS_X),
		SCREEN_COORD(settings.WB_POS_Y), settings.WB_SIZE_X, settings.WB_SIZE_Y, (eFontAlignment)settings.WB_ALIGN,
		RsGlobal.maximumWidth * 0.0015625f * 590.0f,
		settings.WB_SHADOW, settings.WB_OUTLINE, settings.WB_FONTSTYLE,
		CRGBA(settings.WB_R, settings.WB_G, settings.WB_B, 255), (char *)TheText.Get("DEAD")); // Wasted
}

void StyledTexts::TestOddJobMessage4()
{
	CFont::SetBackground(0, 0);
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED4_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED4_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment((eFontAlignment)settings.STYLED4_ALIGN);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 500.0f);
	CFont::SetFontStyle(settings.STYLED4_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(settings.STYLED4_SHADOW);
	if (settings.STYLED4_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED4_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED4_R, settings.STYLED4_G, settings.STYLED4_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString(RsGlobal.maximumWidth - SCREEN_COORD(settings.STYLED4_X),
		SCREEN_COORD(settings.STYLED4_Y), (char *)TheText.Get("TAXI_M")); // ~y~'TAXI DRIVER'
}

void StyledTexts::TestOddJobMessage5()
{
	CFont::SetBackground(0, 0);
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED5_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED5_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 600.0f);
	CFont::SetFontStyle(settings.STYLED5_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(settings.STYLED5_SHADOW);
	if (settings.STYLED5_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED5_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED5_R, settings.STYLED5_G, settings.STYLED5_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintStringFromBottom((float)(RsGlobal.maximumWidth / 2),
		SCREEN_COORD(settings.STYLED5_Y), (char *)TheText.Get("RACES_7")); // GO!
}

void StyledTexts::TestOddJobMessage6()
{
	CFont::SetBackground(0, 0);
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED6_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED6_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 500.0f);
	CFont::SetFontStyle(settings.STYLED6_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(settings.STYLED6_SHADOW);
	if (settings.STYLED6_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED6_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED6_R, settings.STYLED6_G, settings.STYLED6_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString((float)(RsGlobal.maximumWidth / 2),
		SCREEN_COORD(settings.STYLED6_Y), (char *)TheText.Get("ASS_ACQ")); // Asset acquired!
}

void StyledTexts::TestOddJobMessage7()
{
	CFont::SetBackground(0, 0);
	CFont::SetScaleForCurrentlanguage(SCREEN_MULTIPLIER(settings.STYLED7_SIZE_X), SCREEN_MULTIPLIER(settings.STYLED7_SIZE_Y));
	CFont::SetProp(1);
	CFont::SetJustify(0);
	CFont::SetAlignment(ALIGN_CENTER);
	CFont::SetCentreSize(RsGlobal.maximumWidth * 0.0015625f * 500.0f);
	CFont::SetFontStyle(settings.STYLED7_FONTSTYLE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetDropShadowPosition(settings.STYLED7_SHADOW);
	if (settings.STYLED7_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.STYLED7_OUTLINE);
	CFont::SetColor(CRGBA(settings.STYLED7_R, settings.STYLED7_G, settings.STYLED7_B, 255));
	CFont::SetSlantRefPoint(0.0, 0.0);
	CFont::SetSlant(0.0);
	CFont::PrintString((float)(RsGlobal.maximumWidth / 2),
		SCREEN_COORD(settings.STYLED7_Y), (char *)TheText.Get("DNC_002")); // ~y~PERFECT
}
