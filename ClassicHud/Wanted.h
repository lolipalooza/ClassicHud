#pragma once
#include <plugin.h>
#include "Settings.h"
#include "Utility.h"

#include "CSprite2d.h"
#include "CTimer.h"

class Wanted {
public:
	static void InstallPatches();
	static void Draw();
	static void PrintStar(float x, float y, float width, float height, CRGBA color);
};

void Wanted::InstallPatches() {
	plugin::patch::RedirectCall(0x58FBDB, Draw);
}

void Wanted::PrintStar(float x, float y, float width, float height, CRGBA color) {
	int id = (settings.STAR_STYLE < 0 || settings.STAR_STYLE > 2) ? 0 : settings.STAR_STYLE;
	int star[3] = { 8, 3, 9 };
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
	hudIcons[star[id]].Draw((x), (y), (width), (height), CRGBA(color));
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
}

void Wanted::Draw() {
	int nWantedLevel = FindPlayerWanted(-1)->m_nWantedLevel;
	int nTimeOfWLChange = FindPlayerWanted(-1)->m_nLastTimeWantedLevelChanged;
	int nWantedLevelBeforeParole = FindPlayerWanted(-1)->m_nWantedLevelBeforeParole;

	float fCurrentPos = RsGlobal.maximumWidth - SCREEN_COORD(settings.STAR_X);
	float off_x1, off_x2, off_y1, off_y2, off_w1, off_w2, off_h1, off_h2;
	if (settings.STAR_STYLE == 0) {
		off_x1 = -SCREEN_COORD(settings.STAR_X_OFFSET), off_x2 = -off_x1;
		off_y1 = -SCREEN_COORD(settings.STAR_Y_OFFSET), off_y2 = -off_y1;
		off_w1 = -off_x1*2.0f, off_w2 = off_x1*2.0f;
		off_h1 = -off_y1*2.0f, off_h2 = off_y1*2.0f;
	}
	else {
		off_x1 = 2.0f, off_x2 = 0.0f;
		off_y1 = SCREEN_COORD(2.0f), off_y2 = 0.0f;
		off_w1 = 0.0f, off_w2 = 0.0f;
		off_h1 = 0.0f, off_h2 = 0.0f;
	}

	if (nWantedLevel) { // Active Stars
		for (int i = 0; i < 6; ++i, fCurrentPos -= SCREEN_MULTIPLIER(settings.STAR_SPACE)) {
			if (nWantedLevel > i && (CTimer::m_snTimeInMilliseconds > nTimeOfWLChange + 2000 || ShowFlashingItem(150, 150))) {
				PrintStar(
					fCurrentPos + off_x1, SCREEN_COORD(settings.STAR_Y) + off_y1,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X) + off_w1,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_Y) + off_h1,
					CRGBA(0, 0, 0, settings.SHADOWSTAR_A)); // Shadow
				PrintStar(
					fCurrentPos + off_x2, SCREEN_COORD(settings.STAR_Y) + off_y2,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X) + off_w2,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_Y) + off_h2,
					CRGBA(settings.STAR_R, settings.STAR_G, settings.STAR_B, 255));
			}
			else { // Inactive Stars during wanted level > 0
				PrintStar(
					fCurrentPos + 2.0f, SCREEN_COORD(settings.STAR_Y + 2.0f),
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X),
					SCREEN_MULTIPLIER(settings.STAR_SIZE_Y),
					CRGBA(0, 0, 0, settings.SHADOWSTAR_A2)); // Shadow
				PrintStar(fCurrentPos, SCREEN_COORD(settings.STAR_Y),
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X), SCREEN_MULTIPLIER(settings.STAR_SIZE_Y),
					CRGBA(settings.STARBACK_R, settings.STARBACK_G, settings.STARBACK_B, settings.STAR_A2));
			}
		}
	}
	else if (nWantedLevelBeforeParole) { // Flashing stars during suspended wanted level
		for (int i = 0; i < 6; ++i, fCurrentPos -= SCREEN_MULTIPLIER(settings.STAR_SPACE)) {
			if (nWantedLevelBeforeParole > i && CTimer::m_FrameCounter & 4) {
				PrintStar(
					fCurrentPos + off_x1, SCREEN_COORD(settings.STAR_Y) + off_y1,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X) + off_w1,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_Y) + off_h1,
					CRGBA(0, 0, 0, settings.SHADOWSTAR_A)); // Shadow
				PrintStar(
					fCurrentPos + off_x2, SCREEN_COORD(settings.STAR_Y) + off_y2,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X) + off_w2,
					SCREEN_MULTIPLIER(settings.STAR_SIZE_Y) + off_h2,
					CRGBA(settings.FLASHSTAR_R, settings.FLASHSTAR_G, settings.FLASHSTAR_B, 255));
			}
			else {
				PrintStar(
					fCurrentPos + 2.0f, SCREEN_COORD(settings.STAR_Y + 2.0f),
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X),
					SCREEN_MULTIPLIER(settings.STAR_SIZE_Y),
					CRGBA(0, 0, 0, settings.SHADOWSTAR_A2)); // Shadow
				PrintStar(fCurrentPos, SCREEN_COORD(settings.STAR_Y),
					SCREEN_MULTIPLIER(settings.STAR_SIZE_X), SCREEN_MULTIPLIER(settings.STAR_SIZE_Y),
					CRGBA(settings.STARBACK_R, settings.STARBACK_G, settings.STARBACK_B, settings.STAR_A2));
			}
		}
	}
	else { // Inactive stars
		float fCurrentPos = RsGlobal.maximumWidth - SCREEN_COORD(settings.STAR_X);
		for (int i = 0; i < 6; ++i, fCurrentPos -= SCREEN_MULTIPLIER(settings.STAR_SPACE)) {
			PrintStar(fCurrentPos + 2.0f, SCREEN_COORD(settings.STAR_Y + 2.0f),
				SCREEN_MULTIPLIER(settings.STAR_SIZE_X),
				SCREEN_MULTIPLIER(settings.STAR_SIZE_Y),
				CRGBA(0, 0, 0, settings.SHADOWSTAR_A3)); // Shadow
			PrintStar(fCurrentPos, SCREEN_COORD(settings.STAR_Y),
				SCREEN_MULTIPLIER(settings.STAR_SIZE_X),
				SCREEN_MULTIPLIER(settings.STAR_SIZE_Y),
				CRGBA(settings.STARBACK_R, settings.STARBACK_G, settings.STARBACK_B, settings.STAR_A3));
		}
	}
}