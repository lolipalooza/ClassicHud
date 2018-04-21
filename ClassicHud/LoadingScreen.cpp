#include "LoadingScreen.h"
#include "Settings.h"

void LoadingScreen::TestLoadingBar() {
	float distance = 18.0f;
	float x, y, w, h;
	unsigned char border = (settings.LOADBAR_BORDER == 0) ? 1 : 0;

	switch (settings.LOADBAR_STYLE) {
	default: case 0: // Free style bar
		x = SCREEN_COORD_LEFT(settings.LOADBAR_X);
		y = SCREEN_COORD_BOTTOM(settings.LOADBAR_Y);
		w = SCREEN_MULTIPLIER(settings.LOADBAR_SIZE_X);
		h = SCREEN_MULTIPLIER(settings.LOADBAR_SIZE_Y);
		break;
	case 1: // Centered Symetric Bar
		x = SCREEN_COORD_LEFT(settings.LOADBAR_X);
		y = SCREEN_COORD_BOTTOM(settings.LOADBAR_Y);
		w = SCREEN_COORD_MAX_X - SCREEN_COORD(settings.LOADBAR_X * 2);
		h = SCREEN_MULTIPLIER(settings.LOADBAR_SIZE_Y);
		break;
	}
	CSprite2d::DrawBarChart(x, y, w, h, 50.0, 0.0, 0, border,
		CRGBA(settings.LOADBAR_R1, settings.LOADBAR_G1, settings.LOADBAR_B1, 255),
		CRGBA(settings.LOADBAR_R2, settings.LOADBAR_G2, settings.LOADBAR_B2, 255));
}