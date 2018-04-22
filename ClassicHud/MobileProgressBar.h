#pragma once
#include "Utility.h"
#include "plugin.h"

#include "game_sa\CRGBA.h"
#include "game_sa\CSprite2d.h"
#include "game_sa\CFont.h"

class MobileProgressBar {
public:
    static void InstallPatches();
	static void MyDrawProgressBar(float x, float y, unsigned short width, unsigned char height, float progress, signed char progressAdd,
		unsigned char drawPercentage, unsigned char drawBlackBorder, CRGBA color, CRGBA addColor);
	static void MyDrawProgressBar2(float x, float y, unsigned short width, unsigned char height,
		float progress, signed char progressAdd, unsigned char drawPercentage, unsigned char drawBlackBorder,
		float drawShadow, CRGBA color, CRGBA addColor, CRGBA color2);
};
