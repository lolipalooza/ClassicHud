#include <plugin.h>

#include "Settings.h"
#include "IniReader.h"

Settings settings;

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
