#pragma once
#include <plugin.h>
#include "CSprite2d.h"

class LoadingScreen {
public:
	static void TestLoadingBar();
};

void LoadingScreen::TestLoadingBar() {
	float x, y, w, h;

	x = SCREEN_COORD_LEFT(settings.LOADBAR_X);
	y = SCREEN_COORD_BOTTOM(settings.LOADBAR_Y);
	h = SCREEN_MULTIPLIER(settings.LOADBAR_SIZE_Y);
	switch (settings.LOADBAR_STYLE) {
	default: case 0: // Free style bar
		w = SCREEN_MULTIPLIER(settings.LOADBAR_SIZE_X);
		break;
	case 1: // Centered Symetric Bar
		w = SCREEN_COORD_MAX_X - SCREEN_COORD(settings.LOADBAR_SIZE_X * 2);
		break;
	}

	MobileProgressBar::MyDrawProgressBar2(x, y, w, h, 50.0, 0.0f, 0, settings.LOADBAR_BORDER, settings.LOADBAR_SHADOW,
		CRGBA(settings.LOADBAR_R1, settings.LOADBAR_G1, settings.LOADBAR_B1, 255),
		CRGBA(0,0,0, 255),
		CRGBA(settings.LOADBAR_R2, settings.LOADBAR_G2, settings.LOADBAR_B2, 255));
}