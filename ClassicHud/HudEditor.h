#pragma once

#include <plugin.h>
#include "IniReader.h"

#include "Money.h"
#include "Clock.h"
#include "HudIcons.h"
#include "Weapon.h"
#include "Wanted.h"
#include "AreaName.h"
#include "VehicleName.h"
#include "Subtitles.h"
#include "HelpText.h"
#include "Radar.h"
#include "StyledTexts.h"
#include "MissionTimers.h"
#include "RadioStation.h"
#include "GarageMessages.h"
#include "TestMessage.h"

#include "MobileProgressBar.h"
#include "MobileMenuSystem.h"
#include "MobileLoadingScreen.h"
#include "MobileTextures.h"
#include "MobileFrontEnd.h"

extern int STYLE;

using namespace plugin;

struct Data {
	std::string label;
	std::string section;
	std::string key;
	float incr;
};

Data edit_data[] = {
	{ "Money Pos X", "MONEY", "POS_X", 1.0f },
	{ "Money Pos Y", "MONEY", "POS_Y", 1.0f },
	{ "Money Size X", "MONEY", "SIZE_X", 0.01f },
	{ "Money Size Y", "MONEY", "SIZE_Y", 0.01f },

	{ "Clock Pos X", "CLOCK", "POS_X", 1.0f },
	{ "Clock Pos Y", "CLOCK", "POS_Y", 1.0f },
	{ "Clock Size X", "CLOCK", "SIZE_X", 0.01f },
	{ "Clock Size Y", "CLOCK", "SIZE_Y", 0.01f },

	{ "Health Pos X", "HEALTH", "POS_X", 1.0f },
	{ "Health Pos Y", "HEALTH", "POS_Y", 1.0f },
	{ "Health Size X", "HEALTH", "SIZE_X", 0.01f },
	{ "Health Size Y", "HEALTH", "SIZE_Y", 0.01f },
	{ "Health Bar Pos X", "HEALTH", "BAR_X", 2.0f },
	{ "Health Bar Pos Y", "HEALTH", "BAR_Y", 2.0f },
	{ "Health Bar Size X", "HEALTH", "BAR_SIZE_X", 1.0f },
	{ "Health Bar Size Y", "HEALTH", "BAR_SIZE_Y", 1.0f },
	{ "Health Icon Pos X", "HEALTH", "ICON_X", 2.0f },
	{ "Health Icon Pos Y", "HEALTH", "ICON_Y", 2.0f },
	{ "Health Icon Size X", "HEALTH", "ICON_SIZE_X", 0.5f },
	{ "Health Icon Size Y", "HEALTH", "ICON_SIZE_Y", 0.5f },

	{ "Armour Pos X", "ARMOUR", "POS_X", 1.0f },
	{ "Armour Pos Y", "ARMOUR", "POS_Y", 1.0f },
	{ "Armour Size X", "ARMOUR", "SIZE_X", 0.01f },
	{ "Armour Size Y", "ARMOUR", "SIZE_Y", 0.01f },
	{ "Armour Icon Pos X", "ARMOUR", "ICON_X", 2.0f },
	{ "Armour Icon Pos Y", "ARMOUR", "ICON_Y", 2.0f },
	{ "Armour Icon Size X", "ARMOUR", "ICON_SIZE_X", 0.5f },
	{ "Armour Icon Size Y", "ARMOUR", "ICON_SIZE_Y", 0.5f },
	{ "Armour Bar Pos X", "ARMOUR", "BAR_X", 2.0f },
	{ "Armour Bar Pos Y", "ARMOUR", "BAR_Y", 2.0f },
	{ "Armour Bar Size X", "ARMOUR", "BAR_SIZE_X", 1.0f },
	{ "Armour Bar Size Y", "ARMOUR", "BAR_SIZE_Y", 1.0f },

	{ "Breath Pos X", "BREATH", "POS_X", 1.0f },
	{ "Breath Pos Y", "BREATH", "POS_Y", 1.0f },
	{ "Breath Size X", "BREATH", "SIZE_X", 0.01f },
	{ "Breath Size Y", "BREATH", "SIZE_Y", 0.01f },
	{ "Breath Bar Pos X", "BREATH", "BAR_X", 2.0f },
	{ "Breath Bar Pos Y", "BREATH", "BAR_Y", 2.0f },
	{ "Breath Bar Size X", "BREATH", "BAR_SIZE_X", 1.0f },
	{ "Breath Bar Size Y", "BREATH", "BAR_SIZE_Y", 1.0f },
	{ "Breath Icon Pos X", "BREATH", "ICON_X", 2.0f },
	{ "Breath Icon Pos Y", "BREATH", "ICON_Y", 2.0f },
	{ "Breath Icon Size X", "BREATH", "ICON_SIZE_X", 0.5f },
	{ "Breath Icon Size Y", "BREATH", "ICON_SIZE_Y", 0.5f },

	{ "Weapon Pos X", "WEAPON", "POS_X", 1.0f },
	{ "Weapon Pos Y", "WEAPON", "POS_Y", 1.0f },
	{ "Weapon Size X", "WEAPON", "SIZE_X", 1.0f },
	{ "Weapon Size Y", "WEAPON", "SIZE_Y", 1.0f },

	{ "Ammo Pos X", "AMMO", "POS_X", 1.0f },
	{ "Ammo Pos Y", "AMMO", "POS_Y", 1.0f },
	{ "Ammo Size X", "AMMO", "SIZE_X", 0.01f },
	{ "Ammo Size Y", "AMMO", "SIZE_Y", 0.01f },

	{ "Wanted Stars Pos X", "WANTED", "POS_X", 2.0f },
	{ "Wanted Stars Pos Y", "WANTED", "POS_Y", 2.0f },
	{ "Wanted Stars Size X", "WANTED", "SIZE_X", 1.0f },
	{ "Wanted Stars Size Y", "WANTED", "SIZE_Y", 1.0f },
	{ "Wanted Stars Space Between", "WANTED", "SPACE", 1.0f },

	{ "Area Pos X", "AREA", "POS_X", 1.0f },
	{ "Area Pos Y", "AREA", "POS_Y", 1.0f },
	{ "Area Size X", "AREA", "SIZE_X", 0.01f },
	{ "Area Size Y", "AREA", "SIZE_Y", 0.01f },
	{ "Area Slant", "AREA", "SLANT", 0.01f },

	{ "Vehicle Pos X", "VEHICLE", "POS_X", 1.0f },
	{ "Vehicle Pos Y", "VEHICLE", "POS_Y", 1.0f },
	{ "Vehicle Size X", "VEHICLE", "SIZE_X", 0.01f },
	{ "Vehicle Size Y", "VEHICLE", "SIZE_Y", 0.01f },
	{ "Vehicle Slant", "VEHICLE", "SLANT", 0.01f },

	{ "Subtitles Pos X", "SUBTITLES", "POS_X", 1.0f },
	{ "Subtitles Pos Y", "SUBTITLES", "POS_Y", 1.0f },
	{ "Subtitles Size X", "SUBTITLES", "SIZE_X", 0.01f },
	{ "Subtitles Size Y", "SUBTITLES", "SIZE_Y", 0.01f },

	{ "Subtitles Linewidth", "SUBTITLES", "LINEWIDTH", 5.0f },
	{ "Subtitles Vitalstats Offset X", "SUBTITLES_VITALSTATS", "POS_X1", 1.0f },
	{ "Subtitles Vitalstats Size X Factor", "SUBTITLES_VITALSTATS", "SIZE_X1", 0.01f },

	{ "Help Text Pos X", "HELP_TEXT", "POS_X", 1.0f },
	{ "Help Text Pos Y", "HELP_TEXT", "POS_Y", 1.0f },
	{ "Help Text Size X", "HELP_TEXT", "SIZE_X", 0.01f },
	{ "Help Text Size Y", "HELP_TEXT", "SIZE_Y", 0.01f },
	{ "Help Text Width", "HELP_TEXT", "WIDTH", 1.0f },
	{ "Help Text Border Size", "HELP_TEXT", "BORDER_SIZE", 1.0f },

	{ "Radar Pos X", "RADAR", "POS_X", 1.0f },
	{ "Radar Pos Y", "RADAR", "POS_Y", 1.0f },
	{ "Radar Size X", "RADAR", "SIZE_X", 1.0f },
	{ "Radar Size Y", "RADAR", "SIZE_Y", 1.0f },

	{ "Styled Text 1 Pos Y", "STYLED1", "POS_Y", 2.0f },
	{ "Styled Text 1 Offset Y1", "STYLED1", "POS_Y1", 1.0f },
	{ "Styled Text 1 Offset Y2", "STYLED1", "POS_Y2", 1.0f },
	{ "Styled Text 1 Size X", "STYLED1", "SIZE_X", 0.01f },
	{ "Styled Text 1 Size Y", "STYLED1", "SIZE_Y", 0.01f },

	{ "Mission Title Pos X", "STYLED2", "POS_X", 2.0f },
	{ "Mission Title Pos Y", "STYLED2", "POS_Y", 2.0f },
	{ "Mission Title Size X", "STYLED2", "SIZE_X", 0.01f },
	{ "Mission Title Size Y", "STYLED2", "SIZE_Y", 0.01f },

	{ "Wasted Busted Pos X", "STYLED3", "POS_X", 2.0f },
	{ "Wasted Busted Pos Y", "STYLED3", "POS_Y", 2.0f },
	{ "Wasted Busted Size X", "STYLED3", "SIZE_X", 0.01f },
	{ "Wasted Busted Size Y", "STYLED3", "SIZE_Y", 0.01f },

	{ "Styled Text 4 Pos X", "STYLED4", "POS_X", 2.0f },
	{ "Styled Text 4 Pos Y", "STYLED4", "POS_Y", 2.0f },
	{ "Styled Text 4 Size X", "STYLED4", "SIZE_X", 0.01f },
	{ "Styled Text 4 Size Y", "STYLED4", "SIZE_Y", 0.01f },

	{ "Styled Text 5 Pos Y", "STYLED5", "POS_Y", 2.0f },
	{ "Styled Text 5 Size X", "STYLED5", "SIZE_X", 0.01f },
	{ "Styled Text 5 Size Y", "STYLED5", "SIZE_Y", 0.01f },

	{ "Styled Text 6 Pos Y", "STYLED6", "POS_Y", 2.0f },
	{ "Styled Text 6 Size X", "STYLED6", "SIZE_X", 0.01f },
	{ "Styled Text 6 Size Y", "STYLED6", "SIZE_Y", 0.01f },

	{ "Styled Text 7 Pos Y", "STYLED7", "POS_Y", 2.0f },
	{ "Styled Text 7 Size X", "STYLED7", "SIZE_X", 0.01f },
	{ "Styled Text 7 Size Y", "STYLED7", "SIZE_Y", 0.01f },

	{ "Mission Timers (Timer Desc) Pos X", "MISSION_TIMERS", "POS_X1", 2.0f },
	{ "Mission Timers (Timer) Pos X", "MISSION_TIMERS", "POS_X2", 2.0f },
	{ "Mission Timers Pos Y", "MISSION_TIMERS", "POS_Y", 2.0f },
	{ "Mission Timers Size X", "MISSION_TIMERS", "SIZE_X", 0.01f },
	{ "Mission Timers Size Y", "MISSION_TIMERS", "SIZE_Y", 0.02f },

	{ "Status Text (Desc) Pos X", "STATUS_TEXT", "POS_X1", 1.0f },
	{ "Status Text (Value) Pos X", "STATUS_TEXT", "POS_X2", 1.0f },
	{ "Status Text Pos Y", "STATUS_TEXT", "POS_Y", 1.0f },
	{ "Status Text Space Between", "STATUS_TEXT", "SPACE", 0.01f },

	{ "Status Text Bar Pos X", "STATUS_TEXT_BAR", "POS_X", 1.0f },
	{ "Status Text Bar Pos Y", "STATUS_TEXT_BAR", "POS_Y", 1.0f },
	{ "Status Text Bar Size X", "STATUS_TEXT_BAR", "SIZE_X", 0.5f },
	{ "Status Text Bar Size Y", "STATUS_TEXT_BAR", "SIZE_Y", 1.0f },

	{ "Radio Station Pos Y", "RADIO_STATION", "POS_Y", 1.0f },
	{ "Radio Station Size X", "RADIO_STATION", "SIZE_X", 0.01f },
	{ "Radio Station Size Y", "RADIO_STATION", "SIZE_Y", 0.02f },

	{ "Garage Pos Y", "GARAGE_MESSAGES", "POS_Y", 1.0f },
	{ "Garage Size X", "GARAGE_MESSAGES", "SIZE_X", 0.01f },
	{ "Garage Size Y", "GARAGE_MESSAGES", "SIZE_Y", 0.02f },
	{ "Garage Linewidth", "GARAGE_MESSAGES", "LINEWIDTH", 10.0f },

	{ "Custom Text Pos X", "CUSTOM_TEXT", "POS_X", 1.0f },
	{ "Custom Text Pos Y", "CUSTOM_TEXT", "POS_Y", 1.0f },
	{ "Custom Text Size X", "CUSTOM_TEXT", "SIZE_X", 0.01f },
	{ "Custom Text Size Y", "CUSTOM_TEXT", "SIZE_Y", 0.02f },
	{ "Custom Text Linewidth", "CUSTOM_TEXT", "LINEWIDTH", 10.0f },

	{ "Legal Text 1", "LEGAL_TEXT1", "DUMMY", 0.0f },
	{ "Legal Text 2", "LEGAL_TEXT2", "DUMMY", 0.0f },

	{ "Loading Screen Bar Pos X", "LOADING_SCREEN_BAR", "POS_X", 0.5f },
	{ "Loading Screen Bar Pos Y", "LOADING_SCREEN_BAR", "POS_Y", 0.5f },
	{ "Loading Screen Bar Size X", "LOADING_SCREEN_BAR", "SIZE_X", 0.5f },
	{ "Loading Screen Bar Size Y", "LOADING_SCREEN_BAR", "SIZE_Y", 0.5f },
	{ "Loading Screen Bar Shadow Distance", "LOADING_SCREEN_BAR", "SHADOW", 0.1f },

	{ "Menu Title Pos X", "MENU_TITLE", "POS_X", 1.0f },
	{ "Menu Title Pos Y", "MENU_TITLE", "POS_Y", 1.0f },
	{ "Menu Title Size X", "MENU_TITLE", "SIZE_X", 0.01f },
	{ "Menu Title Size Y", "MENU_TITLE", "SIZE_Y", 0.01f },
	{ "Menu Title (Stats) Pos X", "MENU_TITLE_STATS", "STATS_X", 1.0f },
	{ "Menu Title (Stats) Pos Y", "MENU_TITLE_STATS", "STATS_Y", 1.0f },

	{ "Menu Ask Pos X", "MENU_ASK", "POS_X", 1.0f },
	{ "Menu Ask Pos Y", "MENU_ASK", "POS_Y", 1.0f },
	{ "Menu Ask Size X", "MENU_ASK", "SIZE_X", 0.01f },
	{ "Menu Ask Size Y", "MENU_ASK", "SIZE_Y", 0.01f },
	{ "Menu Ask (Opt YES) Pos Y", "MENU_ASK", "POS_YY", 1.0f },
	{ "Menu Ask (Opt NO) Pos Y", "MENU_ASK", "POS_YN", 1.0f },

	{ "Menu Options Pos X", "MENU_OPTIONS", "POS_X", 1.0f },
	{ "Menu Options Size X", "MENU_OPTIONS", "SIZE_X", 0.01f },
	{ "Menu Options Size Y", "MENU_OPTIONS", "SIZE_Y", 0.01f },
	{ "Menu Options Pos Y0", "MENU_OPTIONS", "POS_Y0", 1.0f },
	{ "Menu Options Pos Y1", "MENU_OPTIONS", "POS_Y1", 1.0f },
	{ "Menu Options Pos Y1 Offset", "MENU_OPTIONS", "OFFSET_Y1", 1.0f },
	{ "Menu Options Y Space", "MENU_OPTIONS", "Y_SPACE", 1.0f },
	{ "Menu Options Selection Rectangle Pos X", "MENU_OPTIONS", "RECT_X", 1.0f },
	{ "Menu Options Selection Rectangle Pos Y", "MENU_OPTIONS", "RECT_Y", 1.0f },
	{ "Menu Options Selection Rectangle Width", "MENU_OPTIONS", "RECT_WIDTH", 1.0f },
	{ "Menu Options Selection Rectangle Height", "MENU_OPTIONS", "RECT_HEIGHT", 1.0f },

	{ "Menu Options (Stats) Pos X", "MENU_OPTIONS_STATS", "STATS_X", 1.0f },
	{ "Menu Options (Stats) Pos Y Offset", "MENU_OPTIONS_STATS", "OFFSET_STATS_Y", 1.0f },
	{ "Menu Options (Stats) Y Space Offset", "MENU_OPTIONS_STATS", "SPACE", 1.0f },
	{ "Menu Options (Stats) Size X", "MENU_OPTIONS_STATS", "SIZE_X", 0.01f },
	{ "Menu Options (Stats) Size Y", "MENU_OPTIONS_STATS", "SIZE_Y", 0.01f },
	{ "Menu Options Selection Rectangle Width", "MENU_OPTIONS_STATS", "RECT_WIDTH", 1.0f },

	{ "Menu Options (Right) Pos X", "MENU_OPTIONS_RIGHT", "RIGHT_X", 1.0f },
	{ "Menu Options (Right) Size X", "MENU_OPTIONS_RIGHT", "R_SIZE_X", 0.01f },
	{ "Menu Options (Right) Size Y", "MENU_OPTIONS_RIGHT", "R_SIZE_Y", 0.01f },
	{ "Menu Options (Stats) Sliders Pos X", "MENU_OPTIONS_RIGHT", "SLIDERS_X", 1.0f },
	{ "Menu Options (Stats) Sliders Pos Y Offset", "MENU_OPTIONS_RIGHT", "SLIDERS_Y", 1.0f },
	{ "Menu Options (Stats) Sliders Size X", "MENU_OPTIONS_RIGHT", "SLIDERS_SIZE_X", 1.0f },
	{ "Menu Options (Stats) Sliders Size Y", "MENU_OPTIONS_RIGHT", "SLIDERS_SIZE_Y", 0.02f },
	{ "Menu Options (Opt NO) Pos Y", "MENU_OPTIONS_OK", "POS_YN", 1.0f },
};

class HudEditor
{
public:
	static char* ModifyValueInIni(char* section, char* key, float incr, float incr_multiplier)
	{
		std::string prefix[5] = { "SA_", "III_", "VC_", "LCS_", "VCS_" };
		std::string s_section = prefix[STYLE] + (std::string)section;

		if ((std::string)section == "CUSTOM_TEXT") s_section = section;

		CIniReader iniReader(CLASSICHUD_DAT_PATH);
		float value = iniReader.ReadFloat((char*)s_section.c_str(), key, 0.0f);

		if (KeyPressed(VK_ADD)) {
			value += incr * incr_multiplier;
		}
		if (KeyPressed(VK_SUBTRACT)) {
			value -= incr * incr_multiplier;
		}
		iniReader.WriteFloat((char*)s_section.c_str(), key, value);

		settings.Init(STYLE);
		if ((std::string)section == "MONEY")			Money::InstallPatches();
		else if ((std::string)section == "CLOCK")		Clock::InstallPatches();
		else if ((std::string)section == "HEALTH")		HudIcons::InstallPatches();
		else if ((std::string)section == "ARMOUR")		HudIcons::InstallPatches();
		else if ((std::string)section == "BREATH")		HudIcons::InstallPatches();
		else if ((std::string)section == "WEAPON")		Weapon::InstallPatches();
		else if ((std::string)section == "AMMO")		Weapon::InstallPatches();
		else if ((std::string)section == "WANTED")		Wanted::InstallPatches();
		else if ((std::string)section == "HELP_TEXT")	HelpText::InstallPatches();
		else if ((std::string)section == "RADAR")		Radar::InstallPatches();

		char str[200];
		_snprintf(str, sizeof(str), "section: %s ~n~key: %s ~n~value: %f ~n~incr: %f",
			section, key, value, incr);
		return str;
	}

	HudEditor()
	{
		static bool enable = false;
		static int keyPressTime = 0;
		static int menu_level = 0, chosen = 0;
		static bool showStyled1 = false;
		static char edit_mode_text[200] = "Edit mode";
		static char custom_text[200];
		static std::string section;
		static float incr_multiplier = 1.0f;

		static int data_size = 0;
		for each (Data d in edit_data)
			data_size++;
		//sprintf(edit_mode_text, "Edit mode");


		Events::drawingEvent += []
		{
			if (enable) {
				if (section == "AREA")							AreaName::Test();
				else if (section == "VEHICLE")					VehicleName::Test();
				else if (section == "SUBTITLES")				Subtitles::Test();
				else if (section == "SUBTITLES_VITALSTATS")		Subtitles::Test_VitalStats();
				else if (section == "STYLED1")					StyledTexts::TestSuccessFailedMessage();
				else if (section == "STYLED2")					StyledTexts::TestMissionTitle();
				else if (section == "STYLED3")					StyledTexts::TestBustedWastedMessage();
				else if (section == "STYLED4")					StyledTexts::TestOddJobMessage4();
				else if (section == "STYLED5")					StyledTexts::TestOddJobMessage5();
				else if (section == "STYLED6")					StyledTexts::TestOddJobMessage6();
				else if (section == "STYLED7")					StyledTexts::TestOddJobMessage7();
				else if (section == "RADIO_STATION")			RadioStation::Test();
				else if (section == "GARAGE_MESSAGES")			GarageMessages::Test();
				else if (section == "MISSION_TIMERS"
					|| section == "STATUS_TEXT"
					|| section == "STATUS_TEXT_BAR")			MissionTimers::Test();
				else if (section == "LOADING_SCREEN_BAR")		MobileLoadingScreen::TestLoadingBar();
				else if (section == "LEGAL_TEXT1")				MobileLoadingScreen::TestLegalText(true);
				else if (section == "LEGAL_TEXT2")				MobileLoadingScreen::TestLegalText(false);
				else if (section == "MENU_TITLE")				MobileFrontEnd::TestMenuStandard(MENUPAGE_START_GAME);
				else if (section == "MENU_TITLE_STATS")			MobileFrontEnd::TestMenuStandard(MENUPAGE_STATS);
				else if (section == "MENU_ASK")					MobileFrontEnd::TestMenuStandard(MENUPAGE_NEW_GAME_ASK);
				else if (section == "MENU_OPTIONS")				MobileFrontEnd::TestMenuStandard(MENUPAGE_MAIN_MENU);
				else if (section == "MENU_OPTIONS_STATS")		MobileFrontEnd::TestMenuStandard(MENUPAGE_STATS);
				else if (section == "MENU_OPTIONS_RIGHT")		MobileFrontEnd::TestMenuStandard(MENUPAGE_DISPLAY_SETTINGS);
				else if (section == "MENU_OPTIONS_OK")			MobileFrontEnd::TestMenuStandard(MENUPAGE_SAVE_DONE_2);
				
				TestMessage::Draw(SCREEN_COORD(settings.CUSTOM_X),
					SCREEN_COORD(settings.CUSTOM_Y), settings.CUSTOM_SIZE_X, settings.CUSTOM_SIZE_Y,
					(eFontAlignment)settings.CUSTOM_ALIGN, settings.CUSTOM_LINEWIDTH,
					settings.CUSTOM_SHADOW, settings.CUSTOM_OUTLINE, settings.CUSTOM_FONTSTYLE,
					CRGBA(settings.CUSTOM_R, settings.CUSTOM_G, settings.CUSTOM_B, settings.CUSTOM_A),
					custom_text);

				if (menu_level == 1)
					TestMessage::Draw(SCREEN_COORD(settings.CUSTOM_X),
						SCREEN_COORD(settings.CUSTOM_Y - 30.0f), settings.CUSTOM_SIZE_X,
						settings.CUSTOM_SIZE_Y, (eFontAlignment)settings.CUSTOM_ALIGN,
						settings.CUSTOM_LINEWIDTH, settings.CUSTOM_SHADOW, settings.CUSTOM_OUTLINE,
						settings.CUSTOM_FONTSTYLE,
						CRGBA(255, 255, 255, settings.CUSTOM_A), edit_mode_text);
			}
		};

		Events::gameProcessEvent += [] {

			if (FindPlayerPed() && KeyPressed(VK_F10) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;
				enable = !enable;
				menu_level = 0; chosen = 0; menu_level = 0;
				sprintf(custom_text, "Money Pos X");
				CHud::SetHelpMessage(enable ? "Hud Editor enabled!" : "Hud Editor disabled!", true, false, false);
			}

			if (enable && FindPlayerPed() && KeyPressed(VK_DIVIDE) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;
				if (incr_multiplier == 1.0f) {
					incr_multiplier = 10.0f;
					sprintf(edit_mode_text, "Edit mode (X10)");
				}
				else {
					incr_multiplier = 1.0f;
					sprintf(edit_mode_text, "Edit mode");
				}
			}

			if (enable && FindPlayerPed() && KeyPressed(VK_MULTIPLY) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;
				menu_level = (menu_level == 0) ? 1 : 0;
			}

			if (enable && FindPlayerPed() && (KeyPressed(VK_ADD) || KeyPressed(VK_SUBTRACT)) && CTimer::m_snTimeInMilliseconds - keyPressTime > 50) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;

				switch (menu_level)
				{
				default:
				case 0:
					if (KeyPressed(VK_ADD))
						chosen = (chosen == data_size - 1) ? 0 : chosen + 1;
					if (KeyPressed(VK_SUBTRACT))
						chosen = (chosen == 0) ? data_size - 1 : chosen - 1;
					sprintf(custom_text, edit_data[chosen].label.c_str());
					break;
				case 1:
					HudEditor::ModifyValueInIni((char*)edit_data[chosen].section.c_str(),
						(char*)edit_data[chosen].key.c_str(), edit_data[chosen].incr, incr_multiplier);
					break;
				}

				section = edit_data[chosen].section;
			}

		};
	}
} editMyHud;
