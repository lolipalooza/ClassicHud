#pragma once
#include <plugin.h>
#include "IniReader.h"
#include "CRGBA.h"

#define CLASSICHUD_TXD_PATH "models\\ClassicHud\\classichud.txd"
#define DEFAULT_WEAPONS_TXD "models\\ClassicHud\\weapons.txd"
#define CLASSICHUD_DAT_PATH ".\\models\\ClassicHud\\classichud.dat"

class Settings {
public:
	// files
	char* HUD_TXD;
	char* FONTS_TXD;
	char* FONTS_DAT;
	char* WEAPONS_TXD;

	// Money
	int MONEY_R, MONEY_G, MONEY_B, MONEY_A, MONEY_SHADOW, MONEY_OUTLINE, MONEY_FONTSTYLE;
	float MONEY_X, MONEY_Y, MONEY_WIDTH, MONEY_HEIGHT;

	// Clock
	float CLOCK_X, CLOCK_Y, CLOCK_WIDTH, CLOCK_HEIGHT;
	int CLOCK_R, CLOCK_G, CLOCK_B, CLOCK_A, CLOCK_FONTSTYLE;

	// Health
	float HEALTHICON_X, HEALTHICON_Y, HEALTHICON_WIDTH, HEALTHICON_HEIGHT;
	float HEALTH_X, HEALTH_Y, HEALTH_WIDTH, HEALTH_HEIGHT;
	float HEALTHBAR_X, HEALTHBAR_Y, HEALTHBAR_SIZE_X, HEALTHBAR_SIZE_Y;
	int HEALTH_DISPLAY, HEALTH_R, HEALTH_G, HEALTH_B, HEALTH_A, HEALTHBAR_BORDER, HEALTH_TYPE;

	// Armour
	float ARMOUR_X, ARMOUR_Y, ARMOUR_SIZE_X, ARMOUR_SIZE_Y;
	float ARMOURBAR_X, ARMOURBAR_Y, ARMOURBAR_SIZE_X, ARMOURBAR_SIZE_Y;
	float ARMOURICON_X, ARMOURICON_Y, ARMOURICON_SIZE_X, ARMOURICON_SIZE_Y;
	int ARMOUR_R, ARMOUR_G, ARMOUR_B, ARMOUR_A, ARMOURBAR_BORDER, ARMOUR_TYPE;

	// Breath
	float BREATH_X, BREATH_Y, BREATH_SIZE_X, BREATH_SIZE_Y;
	float BREATHICON_X, BREATHICON_Y, BREATHICON_SIZE_X, BREATHICON_SIZE_Y;
	float BREATHBAR_X, BREATHBAR_Y, BREATHBAR_SIZE_X, BREATHBAR_SIZE_Y;
	int BREATH_R, BREATH_G, BREATH_B, BREATH_A, BREATHBAR_BORDER, BREATH_TYPE;

	// Ammo
	int AMMO_SHADOW, AMMO_OUTLINE, D_AMMO_R, D_AMMO_G, D_AMMO_B, AMMO_R, AMMO_G, AMMO_B;
	float AMMO_SIZE_X, AMMO_SIZE_Y, AMMO_X, AMMO_Y;

	// Weapon
	int WEAPON_A;
	float WEAPON_X, WEAPON_Y, WEAPON_SIZE_X, WEAPON_SIZE_Y;
	int STAT_WEP_ALPHA;
	float stat3_2;

	// Wanted Level
	float STAR_X, STAR_Y, STAR_SIZE_X, STAR_SIZE_Y, STAR_SPACE, STAR_X_OFFSET, STAR_Y_OFFSET;
	int STAR_R, STAR_G, STAR_B, STARBACK_R, STARBACK_G, STARBACK_B, SHADOWSTAR_A;
	int FLASHSTAR_R, FLASHSTAR_G, FLASHSTAR_B, STAR_A2, STAR_A3, SHADOWSTAR_A2, SHADOWSTAR_A3, STAR_STYLE;

	// Area
	int AREA_FONTSTYLE, AREA_R, AREA_G, AREA_B, AREA_SHADOW, AREA_OUTLINE;
	float AREA_SIZE_X, AREA_SIZE_Y, AREA_X, AREA_Y, AREA_SLANT;

	// Vehicle
	int VEHICLE_FONTSTYLE, VEHICLE_R, VEHICLE_G, VEHICLE_B, VEHICLE_SHADOW, VEHICLE_OUTLINE;
	float VEHICLE_SIZE_X, VEHICLE_SIZE_Y, VEHICLE_X, VEHICLE_Y, VEHICLE_SLANT;

	// Subtitles
	int SUBTITLES_SHADOW, SUBTITLES_OUTLINE, SUBTITLES_R, SUBTITLES_G, SUBTITLES_B;
	float SUBTITLES_X, SUBTITLES_Y, SUBTITLES_SIZE_X, SUBTITLES_SIZE_Y;
	float SUBTITLES_VITALSTATS_X, SUBTITLES_VITALSTATS_SIZE_X, SUBTITLES_LINEWIDTH;

	// Text box (Help Message)
	float fTextBoxPosnX;
	float fTextBoxPosnXWithRadar;
	float fTextBoxPosnXWithRadarAndPlane;
	float fTextBoxPosnY;
	float fTextBoxFontScaleX;
	float fTextBoxFontScaleY;
	float fTextBoxWidth;
	float fTextBoxBorderSize;

	// Radar
	float RADAR_RANGE, RADAR_X, RADAR_Y, RADAR_SIZE_X, RADAR_SIZE_Y;
	int RADAR_A;

	// Success Failed Message (Styled Text 1)
	int STYLED1_SHADOW, STYLED1_OUTLINE, STYLED1_R, STYLED1_G, STYLED1_B;
	float STYLED1_Y, STYLED1_Y1, STYLED1_Y2, STYLED1_SIZE_X, STYLED1_SIZE_Y;

	// Mission Title (Styled Text 2)
	int MT_R, MT_G, MT_B, MT_SHADOW, MT_OUTLINE, MT_FONTSTYLE;
	float MT_POS_X, MT_POS_Y, MT_SIZE_X, MT_SIZE_Y;

	// Wasted Busted Message (Styled Text 3)
	int WB_R, WB_G, WB_B, WB_SHADOW, WB_OUTLINE, WB_FONTSTYLE, WB_ALIGN;
	float WB_POS_X, WB_POS_Y, WB_SIZE_X, WB_SIZE_Y;

	// Odd Job Messages 1 (Styled Text 4)
	int STYLED4_FONTSTYLE, STYLED4_SHADOW, STYLED4_OUTLINE, STYLED4_R, STYLED4_G, STYLED4_B, STYLED4_ALIGN;
	float STYLED4_X, STYLED4_Y, STYLED4_SIZE_X, STYLED4_SIZE_Y;

	// Odd Job Messages 2 (Styled Text 5)
	int STYLED5_FONTSTYLE, STYLED5_SHADOW, STYLED5_OUTLINE, STYLED5_R, STYLED5_G, STYLED5_B;
	float STYLED5_Y, STYLED5_SIZE_X, STYLED5_SIZE_Y;

	// Odd Job Messages 3 (Styled Text 6)
	int STYLED6_FONTSTYLE, STYLED6_SHADOW, STYLED6_OUTLINE, STYLED6_R, STYLED6_G, STYLED6_B;
	float STYLED6_Y, STYLED6_SIZE_X, STYLED6_SIZE_Y;

	// Odd Job Messages 4 (Styled Text 7)
	int STYLED7_FONTSTYLE, STYLED7_SHADOW, STYLED7_OUTLINE, STYLED7_R, STYLED7_G, STYLED7_B;
	float STYLED7_Y, STYLED7_SIZE_X, STYLED7_SIZE_Y;

	// Mission Timers (Timer and Status Text)
	int M_TIMERS_FONTSTYLE, M_TIMERS_SHADOW, M_TIMERS_OUTLINE, M_TIMERS_R, M_TIMERS_G, M_TIMERS_B;
	float M_TIMERS_SIZE_X, M_TIMERS_SIZE_Y, M_TIMER_X, M_TIMER_Y, M_TIMER_DESC_X;
	int M_STATUSBAR_BORDER, M_STATUSBAR_R, M_STATUSBAR_G, M_STATUSBAR_B, M_STATUSBAR_A;
	float M_STATUSBAR_X, M_STATUSBAR_Y, M_STATUSBAR_SIZE_X, M_STATUSBAR_SIZE_Y;
	float M_STATUSTEXT_X, M_STATUSTEXT_Y, M_STATUSTEXT_DESC_X, M_STATUSTEXT_SPACE;

	// Radio Station Text
	int RS_FONTSTYLE, RS_SHADOW, RS_OUTLINE, RS_RED1, RS_GREEN1, RS_BLUE1, RS_RED2, RS_GREEN2, RS_BLUE2;
	float RS_POS_Y, RS_SIZE_X, RS_SIZE_Y;

	// Garage Messages
	int GARAGES_R, GARAGES_G, GARAGES_B, GARAGES_FONTSTYLE, GARAGES_SHADOW, GARAGES_OUTLINE;
	float GARAGES_Y, GARAGES_SIZE_X, GARAGES_SIZE_Y, GARAGES_LINEWIDTH;

	// Custom text (for Hud Editor)
	int CUSTOM_ALIGN, CUSTOM_SHADOW, CUSTOM_OUTLINE, CUSTOM_FONTSTYLE, CUSTOM_R, CUSTOM_G, CUSTOM_B, CUSTOM_A;
	float CUSTOM_X, CUSTOM_Y, CUSTOM_SIZE_X, CUSTOM_SIZE_Y, CUSTOM_LINEWIDTH;
	
public:
	void Init(int style);
} settings;

void Settings::Init(int style)
{
	char section[20];
	char* prefix[5] = { "SA", "III", "VC", "LCS", "VCS" };
	CIniReader iniReader(CLASSICHUD_DAT_PATH);

	sprintf(section, "CUSTOM_TEXT");
	CUSTOM_ALIGN = iniReader.ReadInt(section, "ALIGN", 0);
	CUSTOM_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	CUSTOM_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	CUSTOM_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	CUSTOM_R = iniReader.ReadInt(section, "RED", 0);
	CUSTOM_G = iniReader.ReadInt(section, "GREEN", 0);
	CUSTOM_B = iniReader.ReadInt(section, "BLUE", 0);
	CUSTOM_A = iniReader.ReadInt(section, "ALPHA", 0);
	CUSTOM_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	CUSTOM_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	CUSTOM_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	CUSTOM_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	CUSTOM_LINEWIDTH = iniReader.ReadFloat(section, "LINEWIDTH", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "FILES");
	HUD_TXD = iniReader.ReadString(section, "HUD_TXD", "404");
	FONTS_TXD = iniReader.ReadString(section, "FONTS_TXD", "404");
	FONTS_DAT = iniReader.ReadString(section, "FONTS_DAT", "404");
	WEAPONS_TXD = iniReader.ReadString(section, "WEAPONS_TXD", "404");

	sprintf(section, "%s_%s", prefix[style], "MONEY");
	MONEY_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	MONEY_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	MONEY_WIDTH = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	MONEY_HEIGHT = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	MONEY_R = iniReader.ReadInt(section, "RED", 47);
	MONEY_G = iniReader.ReadInt(section, "GREEN", 90);
	MONEY_B = iniReader.ReadInt(section, "BLUE", 38);
	MONEY_A = iniReader.ReadInt(section, "ALPHA", 255);
	MONEY_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 2);
	MONEY_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	MONEY_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);

	sprintf(section, "%s_%s", prefix[style], "CLOCK");
	CLOCK_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	CLOCK_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	CLOCK_WIDTH = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	CLOCK_HEIGHT = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	CLOCK_R = iniReader.ReadInt(section, "RED", 194);
	CLOCK_G = iniReader.ReadInt(section, "GREEN", 165);
	CLOCK_B = iniReader.ReadInt(section, "BLUE", 120);
	CLOCK_A = iniReader.ReadInt(section, "ALPHA", 255);
	CLOCK_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);

	sprintf(section, "%s_%s", prefix[style], "HEALTH");
	HEALTH_DISPLAY = iniReader.ReadInt(section, "DISPLAY", 0);
	HEALTH_R = iniReader.ReadInt(section, "RED", 180);
	HEALTH_G = iniReader.ReadInt(section, "GREEN", 100);
	HEALTH_B = iniReader.ReadInt(section, "BLUE", 50);
	HEALTH_A = iniReader.ReadInt(section, "ALPHA", 255);
	HEALTHICON_X = iniReader.ReadFloat(section, "ICON_X", 0.0f);
	HEALTHICON_Y = iniReader.ReadFloat(section, "ICON_Y", 0.0f);
	HEALTHICON_WIDTH = iniReader.ReadFloat(section, "ICON_SIZE_X", 0.0f);
	HEALTHICON_HEIGHT = iniReader.ReadFloat(section, "ICON_SIZE_Y", 0.0f);
	HEALTH_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	HEALTH_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	HEALTH_WIDTH = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	HEALTH_HEIGHT = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	HEALTHBAR_X = iniReader.ReadFloat(section, "BAR_X", 0.0f);
	HEALTHBAR_Y = iniReader.ReadFloat(section, "BAR_Y", 0.0f);
	HEALTHBAR_SIZE_X = iniReader.ReadFloat(section, "BAR_SIZE_X", 0.0f);
	HEALTHBAR_SIZE_Y = iniReader.ReadFloat(section, "BAR_SIZE_Y", 0.0f);
	HEALTHBAR_BORDER = iniReader.ReadInt(section, "BORDER", 0);
	HEALTH_TYPE = iniReader.ReadInt(section, "TYPE", 0);

	sprintf(section, "%s_%s", prefix[style], "ARMOUR");
	ARMOUR_R = iniReader.ReadInt(section, "RED", 121);
	ARMOUR_G = iniReader.ReadInt(section, "GREEN", 136);
	ARMOUR_B = iniReader.ReadInt(section, "BLUE", 93);
	ARMOUR_A = iniReader.ReadInt(section, "ALPHA", 255);
	ARMOUR_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	ARMOUR_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	ARMOUR_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	ARMOUR_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	ARMOURBAR_X = iniReader.ReadFloat(section, "BAR_X", 0.0f);
	ARMOURBAR_Y = iniReader.ReadFloat(section, "BAR_Y", 0.0f);
	ARMOURBAR_SIZE_X = iniReader.ReadFloat(section, "BAR_SIZE_X", 0.0f);
	ARMOURBAR_SIZE_Y = iniReader.ReadFloat(section, "BAR_SIZE_Y", 0.0f);
	ARMOURICON_X = iniReader.ReadFloat(section, "ICON_X", 0.0f);
	ARMOURICON_Y = iniReader.ReadFloat(section, "ICON_Y", 0.0f);
	ARMOURICON_SIZE_X = iniReader.ReadFloat(section, "ICON_SIZE_X", 0.0f);
	ARMOURICON_SIZE_Y = iniReader.ReadFloat(section, "ICON_SIZE_Y", 0.0f);
	ARMOURBAR_BORDER = iniReader.ReadInt(section, "BORDER", 0);
	ARMOUR_TYPE = iniReader.ReadInt(section, "TYPE", 0);

	sprintf(section, "%s_%s", prefix[style], "BREATH");
	BREATH_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	BREATH_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	BREATH_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	BREATH_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	BREATHICON_X = iniReader.ReadFloat(section, "ICON_X", 0.0f);
	BREATHICON_Y = iniReader.ReadFloat(section, "ICON_Y", 0.0f);
	BREATHICON_SIZE_X = iniReader.ReadFloat(section, "ICON_SIZE_X", 0.0f);
	BREATHICON_SIZE_Y = iniReader.ReadFloat(section, "ICON_SIZE_Y", 0.0f);
	BREATHBAR_X = iniReader.ReadFloat(section, "BAR_X", 0.0f);
	BREATHBAR_Y = iniReader.ReadFloat(section, "BAR_Y", 0.0f);
	BREATHBAR_SIZE_X = iniReader.ReadFloat(section, "BAR_SIZE_X", 0.0f);
	BREATHBAR_SIZE_Y = iniReader.ReadFloat(section, "BAR_SIZE_Y", 0.0f);
	BREATH_R = iniReader.ReadInt(section, "RED", 121);
	BREATH_G = iniReader.ReadInt(section, "GREEN", 136);
	BREATH_B = iniReader.ReadInt(section, "BLUE", 93);
	BREATH_A = iniReader.ReadInt(section, "ALPHA", 255);
	BREATHBAR_BORDER = iniReader.ReadInt(section, "BORDER", 0);
	BREATH_TYPE = iniReader.ReadInt(section, "TYPE", 0);

	sprintf(section, "%s_%s", prefix[style], "AMMO");
	AMMO_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	AMMO_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	D_AMMO_R = iniReader.ReadInt(section, "D_RED", 0);
	D_AMMO_G = iniReader.ReadInt(section, "D_GREEN", 0);
	D_AMMO_B = iniReader.ReadInt(section, "D_BLUE", 0);
	AMMO_R = iniReader.ReadInt(section, "RED", 0);
	AMMO_G = iniReader.ReadInt(section, "GREEN", 0);
	AMMO_B = iniReader.ReadInt(section, "BLUE", 0);
	AMMO_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	AMMO_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	AMMO_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	AMMO_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "WEAPON");
	WEAPON_A = iniReader.ReadInt(section, "ALPHA", 0);
	WEAPON_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	WEAPON_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	WEAPON_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	WEAPON_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "WANTED");
	STAR_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	STAR_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	STAR_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	STAR_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	STAR_SPACE = iniReader.ReadFloat(section, "SPACE", 0.0f);
	STAR_R = iniReader.ReadInt(section, "ACTIVE_R", 0);
	STAR_G = iniReader.ReadInt(section, "ACTIVE_G", 0);
	STAR_B = iniReader.ReadInt(section, "ACTIVE_B", 0);
	STARBACK_R = iniReader.ReadInt(section, "INACTIVE_R", 0);
	STARBACK_G = iniReader.ReadInt(section, "INACTIVE_G", 0);
	STARBACK_B = iniReader.ReadInt(section, "INACTIVE_B", 0);
	FLASHSTAR_R = iniReader.ReadInt(section, "FLASH_R", 0);
	FLASHSTAR_G = iniReader.ReadInt(section, "FLASH_G", 0);
	FLASHSTAR_B = iniReader.ReadInt(section, "FLASH_B", 0);
	SHADOWSTAR_A = iniReader.ReadInt(section, "SHADOW_A1", 0);
	SHADOWSTAR_A2 = iniReader.ReadInt(section, "SHADOW_A2", 0);
	SHADOWSTAR_A3 = iniReader.ReadInt(section, "SHADOW_A3", 0);
	STAR_A2 = iniReader.ReadInt(section, "STAR_A2", 0);
	STAR_A3 = iniReader.ReadInt(section, "STAR_A3", 0);
	STAR_STYLE = iniReader.ReadInt(section, "STYLE", 0);
	STAR_X_OFFSET = iniReader.ReadFloat(section, "OFFSET_X", 0.0f);
	STAR_Y_OFFSET = iniReader.ReadFloat(section, "OFFSET_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "AREA");
	AREA_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	AREA_R = iniReader.ReadInt(section, "RED", 0);
	AREA_G = iniReader.ReadInt(section, "GREEN", 0);
	AREA_B = iniReader.ReadInt(section, "BLUE", 0);
	AREA_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	AREA_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	AREA_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	AREA_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	AREA_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	AREA_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	AREA_SLANT = iniReader.ReadFloat(section, "SLANT", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "VEHICLE");
	VEHICLE_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	VEHICLE_R = iniReader.ReadInt(section, "RED", 0);
	VEHICLE_G = iniReader.ReadInt(section, "GREEN", 0);
	VEHICLE_B = iniReader.ReadInt(section, "BLUE", 0);
	VEHICLE_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	VEHICLE_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	VEHICLE_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	VEHICLE_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	VEHICLE_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	VEHICLE_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	VEHICLE_SLANT = iniReader.ReadFloat(section, "SLANT", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "SUBTITLES");
	SUBTITLES_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	SUBTITLES_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	SUBTITLES_R = iniReader.ReadInt(section, "RED", 0);
	SUBTITLES_G = iniReader.ReadInt(section, "GREEN", 0);
	SUBTITLES_B = iniReader.ReadInt(section, "BLUE", 0);
	SUBTITLES_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	SUBTITLES_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	SUBTITLES_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	SUBTITLES_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	SUBTITLES_LINEWIDTH = iniReader.ReadFloat(section, "LINEWIDTH", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "SUBTITLES_VITALSTATS");
	SUBTITLES_VITALSTATS_X = iniReader.ReadFloat(section, "POS_X1", 0.0f);
	SUBTITLES_VITALSTATS_SIZE_X = iniReader.ReadFloat(section, "SIZE_X1", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "HELP_TEXT");
	fTextBoxPosnX = iniReader.ReadFloat(section, "POS_X", 0.0f);
	fTextBoxPosnXWithRadar = iniReader.ReadFloat(section, "POS_X", 0.0f);
	fTextBoxPosnXWithRadarAndPlane = iniReader.ReadFloat(section, "POS_X", 0.0f);
	fTextBoxPosnY = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	fTextBoxFontScaleX = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	fTextBoxFontScaleY = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	fTextBoxWidth = iniReader.ReadFloat(section, "WIDTH", 0.0f);
	fTextBoxBorderSize = iniReader.ReadFloat(section, "BORDER_SIZE", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "RADAR");
	RADAR_A = iniReader.ReadInt(section, "ALPHA", 0);
	RADAR_RANGE = iniReader.ReadFloat(section, "RANGE", 0.0f);
	RADAR_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	RADAR_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	RADAR_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	RADAR_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED1");
	STYLED1_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	STYLED1_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	STYLED1_R = iniReader.ReadInt(section, "RED", 0);
	STYLED1_G = iniReader.ReadInt(section, "GREEN", 0);
	STYLED1_B = iniReader.ReadInt(section, "BLUE", 0);
	STYLED1_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	STYLED1_Y1 = iniReader.ReadFloat(section, "POS_Y1", 0.0f);
	STYLED1_Y2 = iniReader.ReadFloat(section, "POS_Y2", 0.0f);
	STYLED1_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	STYLED1_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED2");
	MT_R = iniReader.ReadInt(section, "RED", 0);
	MT_G = iniReader.ReadInt(section, "GREEN", 0);
	MT_B = iniReader.ReadInt(section, "BLUE", 0);
	MT_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	MT_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	MT_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	MT_POS_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	MT_POS_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	MT_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	MT_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED3");
	WB_R = iniReader.ReadInt(section, "RED", 0);
	WB_G = iniReader.ReadInt(section, "GREEN", 0);
	WB_B = iniReader.ReadInt(section, "BLUE", 0);
	WB_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	WB_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	WB_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	WB_ALIGN = iniReader.ReadInt(section, "ALIGN", 0);
	WB_POS_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	WB_POS_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	WB_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	WB_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED4");
	STYLED4_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	STYLED4_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	STYLED4_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	STYLED4_ALIGN = iniReader.ReadInt(section, "ALIGN", 0);
	STYLED4_R = iniReader.ReadInt(section, "RED", 0);
	STYLED4_G = iniReader.ReadInt(section, "GREEN", 0);
	STYLED4_B = iniReader.ReadInt(section, "BLUE", 0);
	STYLED4_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	STYLED4_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	STYLED4_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	STYLED4_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED5");
	STYLED5_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	STYLED5_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	STYLED5_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	STYLED5_R = iniReader.ReadInt(section, "RED", 0);
	STYLED5_G = iniReader.ReadInt(section, "GREEN", 0);
	STYLED5_B = iniReader.ReadInt(section, "BLUE", 0);
	STYLED5_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	STYLED5_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	STYLED5_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED6");
	STYLED6_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	STYLED6_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	STYLED6_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	STYLED6_R = iniReader.ReadInt(section, "RED", 0);
	STYLED6_G = iniReader.ReadInt(section, "GREEN", 0);
	STYLED6_B = iniReader.ReadInt(section, "BLUE", 0);
	STYLED6_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	STYLED6_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	STYLED6_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STYLED7");
	STYLED7_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	STYLED7_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	STYLED7_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	STYLED7_R = iniReader.ReadInt(section, "RED", 0);
	STYLED7_G = iniReader.ReadInt(section, "GREEN", 0);
	STYLED7_B = iniReader.ReadInt(section, "BLUE", 0);
	STYLED7_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	STYLED7_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	STYLED7_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "MISSION_TIMERS");
	M_TIMERS_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	M_TIMERS_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	M_TIMERS_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	M_TIMERS_R = iniReader.ReadInt(section, "RED", 0);
	M_TIMERS_G = iniReader.ReadInt(section, "GREEN", 0);
	M_TIMERS_B = iniReader.ReadInt(section, "BLUE", 0);
	M_TIMERS_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	M_TIMERS_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	M_TIMER_X = iniReader.ReadFloat(section, "POS_X2", 0.0f);
	M_TIMER_DESC_X = iniReader.ReadFloat(section, "POS_X1", 0.0f);
	M_TIMER_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STATUS_TEXT");
	M_STATUSTEXT_X = iniReader.ReadFloat(section, "POS_X2", 0.0f);
	M_STATUSTEXT_DESC_X = iniReader.ReadFloat(section, "POS_X1", 0.0f);
	M_STATUSTEXT_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	M_STATUSTEXT_SPACE = iniReader.ReadFloat(section, "SPACE", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "STATUS_TEXT_BAR");
	M_STATUSBAR_BORDER = iniReader.ReadInt(section, "BORDER", 0);
	M_STATUSBAR_R = iniReader.ReadInt(section, "RED", 0);
	M_STATUSBAR_G = iniReader.ReadInt(section, "GREEN", 0);
	M_STATUSBAR_B = iniReader.ReadInt(section, "BLUE", 0);
	M_STATUSBAR_A = iniReader.ReadInt(section, "ALPHA", 0);
	M_STATUSBAR_X = iniReader.ReadFloat(section, "POS_X", 0.0f);
	M_STATUSBAR_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	M_STATUSBAR_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	M_STATUSBAR_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "RADIO_STATION");
	RS_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	RS_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	RS_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	RS_RED1 = iniReader.ReadInt(section, "RED1", 0);
	RS_GREEN1 = iniReader.ReadInt(section, "GREEN1", 0);
	RS_BLUE1 = iniReader.ReadInt(section, "BLUE1", 0);
	RS_RED2 = iniReader.ReadInt(section, "RED2", 0);
	RS_GREEN2 = iniReader.ReadInt(section, "GREEN2", 0);
	RS_BLUE2 = iniReader.ReadInt(section, "BLUE2", 0);
	RS_POS_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	RS_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	RS_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);

	sprintf(section, "%s_%s", prefix[style], "GARAGE_MESSAGES");
	GARAGES_R = iniReader.ReadInt(section, "RED", 0);
	GARAGES_G = iniReader.ReadInt(section, "GREEN", 0);
	GARAGES_B = iniReader.ReadInt(section, "BLUE", 0);
	GARAGES_FONTSTYLE = iniReader.ReadInt(section, "FONTSTYLE", 0);
	GARAGES_SHADOW = iniReader.ReadInt(section, "SHADOW", 0);
	GARAGES_OUTLINE = iniReader.ReadInt(section, "OUTLINE", 0);
	GARAGES_Y = iniReader.ReadFloat(section, "POS_Y", 0.0f);
	GARAGES_SIZE_X = iniReader.ReadFloat(section, "SIZE_X", 0.0f);
	GARAGES_SIZE_Y = iniReader.ReadFloat(section, "SIZE_Y", 0.0f);
	GARAGES_LINEWIDTH = iniReader.ReadFloat(section, "LINEWIDTH", 0.0f);
}
