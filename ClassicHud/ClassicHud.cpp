#include <plugin.h>

#include "Settings.h"
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

#include "MobileLoadingScreen.h"

#include "CFileMgr.h"

using namespace plugin;

static int STYLE;

class ClassicHud {
public:
	static void HudTextures(int index) {
		CTxdStore::LoadTxd(index, settings.HUD_TXD);
	}

	static void FontTextures(int index) {
		CTxdStore::LoadTxd(index, settings.FONTS_TXD);
	}

	static void FontData() {
		CFileMgr::OpenFile(settings.FONTS_DAT, "rb");
	}

	static void ClassicHudTextures() {
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

	static void ClassicHudTextureShutdown() {
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

	ClassicHud() {

		static int keyPressTime = 0;

		CIniReader iniReader(CLASSICHUD_DAT_PATH);
		settings.WEAPONS_TXD = iniReader.ReadString("SA_FILES", "WEAPONS_TXD", DEFAULT_WEAPONS_TXD);

		Events::initRwEvent += ClassicHud::ClassicHudTextures;
		Events::shutdownRwEvent += ClassicHud::ClassicHudTextureShutdown;

		Events::initRwEvent += Weapon::WeaponTextures;
		Events::shutdownRwEvent += Weapon::WeaponTexturesShutdown;

		/*Events::initRwEvent += [] {
			MobileMenuSystem::InstallPatches();
			MobileLoadingScreen::InstallPatches();
		};*/

		Events::gameProcessEvent += [] {

			if (FindPlayerPed() && KeyPressed(VK_F9) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;

				STYLE = (STYLE >= 3) ? 0 : STYLE + 1;
				settings.Init(STYLE);

				Weapon::WeaponTexturesShutdown();
				Weapon::WeaponTextures();

				patch::RedirectCall(0x5BA8AF, ClassicHud::HudTextures);
				patch::RedirectCall(0x5BA6A4, ClassicHud::FontTextures);
				patch::RedirectCall(0x7187DB, ClassicHud::FontData);
				
				CFont::Initialise();

				//CHud::Shutdown();
				//CHud::Initialise();

				Money::InstallPatches();
				Clock::InstallPatches();
				HudIcons::InstallPatches();

				Weapon::InstallPatches();
				Wanted::InstallPatches();

				AreaName::InstallPatches();
				VehicleName::InstallPatches();

				Subtitles::InstallPatches();
				HelpText::InstallPatches();

				/*
				// Set Radar Range
				patch::SetFloat(0x586C9B, RADAR_RANGE);
				patch::Set<const void*>(0x586C66, &RADAR_RANGE);

				// Transparent Radar
				patch::Set<DWORD>(0x5864BD, RADAR_A);
				plugin::patch::RedirectJump(0x58641A, RadarAlpha);
				*/

				Radar::InstallPatches();
				
				StyledTexts::InstallPatches();
				MissionTimers::InstallPatches();
				RadioStation::InstallPatches();
				GarageMessages::InstallPatches();
			}
		};
	}
} classicHud;




class HudEditor
{
public:
	static char* ModifyValueInIni(char* section, char* key, float incr)
	{
		std::string prefix[5] = { "SA_", "III_", "VC_", "LCS_", "VCS_" };
		std::string s_section = prefix[STYLE] + (std::string)section;

		if ((std::string)section == "CUSTOM_TEXT") s_section = section;

		CIniReader iniReader(CLASSICHUD_DAT_PATH);
		float value = iniReader.ReadFloat((char*)s_section.c_str(), key, 0.0f);

		if (KeyPressed(VK_ADD)) {
			value += incr;
		}
		if (KeyPressed(VK_SUBTRACT)) {
			value -= incr;
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
		static char custom_text[200];
		static std::string section;

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
						CRGBA(255, 255, 255, settings.CUSTOM_A), "Edit mode");
			}
		};

		Events::gameProcessEvent += [] {

			if (FindPlayerPed() && KeyPressed(VK_F10) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;
				enable = !enable;
				menu_level = 0; chosen = 0; menu_level = 0;
				sprintf(custom_text, "Money Pos X");
				CHud::SetHelpMessage(enable?"Hud Editor enabled!":"Hud Editor disabled!", true, false, false);
			}
			
			if (enable && FindPlayerPed() && KeyPressed(VK_MULTIPLY) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;
				menu_level = (menu_level == 0) ? 1 : 0;
			}

			if (enable && FindPlayerPed() && (KeyPressed(VK_ADD) || KeyPressed(VK_SUBTRACT)) && CTimer::m_snTimeInMilliseconds - keyPressTime > 50) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;

				std::string labels[] =			{ "Money Pos X",	"Money Pos Y",	"Money Size X",	"Money Size Y",	"Clock Pos X",	"Clock Pos Y",	"Clock Size X",	"Clock Size Y",	"Health Pos X",	"Health Pos Y",	"Health Size X",	"Health Size Y",	"Health Bar Pos X",	"Health Bar Pos Y",	"Health Bar Size X",	"Health Bar Size Y",	"Health Icon Pos X",	"Health Icon Pos Y",	"Health Icon Size X",	"Health Icon Size Y",	"Armour Pos X",	"Armour Pos Y",	"Armour Size X",	"Armour Size Y",	"Armour Icon Pos X",	"Armour Icon Pos Y",	"Armour Icon Size X",	"Armour Icon Size Y",	"Armour Bar Pos X",	"Armour Bar Pos Y",	"Armour Bar Size X",	"Armour Bar Size Y",	"Breath Pos X",	"Breath Pos Y",	"Breath Size X",	"Breath Size Y",	"Breath Bar Pos X",	"Breath Bar Pos Y",	"Breath Bar Size X",	"Breath Bar Size Y",	"Breath Icon Pos X",	"Breath Icon Pos Y",	"Breath Icon Size X",	"Breath Icon Size Y",	"Weapon Pos X",	"Weapon Pos Y",	"Weapon Size X",	"Weapon Size Y",	"Ammo Pos X",	"Ammo Pos Y",	"Ammo Size X",	"Ammo Size Y",	"Wanted Stars Pos X",	"Wanted Stars Pos Y",	"Wanted Stars Size X",	"Wanted Stars Size Y",	"Wanted Stars Space Between",	"Area Pos X",	"Area Pos Y",	"Area Size X",	"Area Size Y",	"Area Slant",	"Vehicle Pos X",	"Vehicle Pos Y",	"Vehicle Size X",	"Vehicle Size Y",	"Vehicle Slant",	"Subtitles Pos X",	"Subtitles Pos Y",	"Subtitles Size X",	"Subtitles Size Y",	"Subtitles Linewidth",	"Subtitles Vitalstats Offset X",	"Subtitles Vitalstats Size X Factor",	"Help Text Pos X",	"Help Text Pos Y",	"Help Text Size X",	"Help Text Size Y",	"Help Text Width",	"Help Text Border Size",	"Radar Pos X",	"Radar Pos Y",	"Radar Size X",	"Radar Size Y",	"Styled Text 1 Pos Y",	"Styled Text 1 Offset Y1",	"Styled Text 1 Offset Y2",	"Styled Text 1 Size X",	"Styled Text 1 Size Y",	"Mission Title Pos X",	"Mission Title Pos Y",	"Mission Title Size X",	"Mission Title Size Y",	"Wasted Busted Pos X",	"Wasted Busted Pos Y",	"Wasted Busted Size X",	"Wasted Busted Size Y",	"Styled Text 4 Pos X",	"Styled Text 4 Pos Y",	"Styled Text 4 Size X",	"Styled Text 4 Size Y",	"Styled Text 5 Pos Y",	"Styled Text 5 Size X",	"Styled Text 5 Size Y",	"Styled Text 6 Pos Y",	"Styled Text 6 Size X",	"Styled Text 6 Size Y",	"Styled Text 7 Pos Y",	"Styled Text 7 Size X",	"Styled Text 7 Size Y",	"Mission Timers (Timer Desc) Pos X",	"Mission Timers (Timer) Pos X",	"Mission Timers Pos Y",	"Mission Timers Size X",	"Mission Timers Size Y",	"Status Text (Desc) Pos X",	"Status Text (Value) Pos X",	"Status Text Pos Y",	"Status Text Space Between",	"Status Text Bar Pos X",	"Status Text Bar Pos Y",	"Status Text Bar Size X",	"Status Text Bar Size Y",	"Radio Station Pos Y",	"Radio Station Size X",	"Radio Station Size Y",	"Garage Pos Y",		"Garage Size X",	"Garage Size Y",	"Garage Linewidth",	"Custom Text Pos X",	"Custom Text Pos Y",	"Custom Text Size X",	"Custom Text Size Y",	"Custom Text Linewidth" };
				std::string sections[] =		{ "MONEY",			"MONEY",		"MONEY",		"MONEY",		"CLOCK",		"CLOCK",		"CLOCK",		"CLOCK",		"HEALTH",		"HEALTH",		"HEALTH",			"HEALTH",			"HEALTH",			"HEALTH",			"HEALTH",				"HEALTH",				"HEALTH",				"HEALTH",				"HEALTH",				"HEALTH",				"ARMOUR",		"ARMOUR",		"ARMOUR",			"ARMOUR",			"ARMOUR",				"ARMOUR",				"ARMOUR",				"ARMOUR",				"ARMOUR",			"ARMOUR",			"ARMOUR",				"ARMOUR",				"BREATH",		"BREATH",		"BREATH",			"BREATH",			"BREATH",			"BREATH",			"BREATH",				"BREATH",				"BREATH",				"BREATH",				"BREATH",				"BREATH",				"WEAPON",		"WEAPON",		"WEAPON",			"WEAPON",			"AMMO",			"AMMO",			"AMMO",			"AMMO",			"WANTED",				"WANTED",				"WANTED",				"WANTED",				"WANTED",						"AREA",			"AREA",			"AREA",			"AREA",			"AREA",			"VEHICLE",			"VEHICLE",			"VEHICLE",			"VEHICLE",			"VEHICLE",			"SUBTITLES",		"SUBTITLES",		"SUBTITLES",		"SUBTITLES",		"SUBTITLES",			"SUBTITLES_VITALSTATS",				"SUBTITLES_VITALSTATS",					"HELP_TEXT",		"HELP_TEXT",		"HELP_TEXT",		"HELP_TEXT",		"HELP_TEXT",		"HELP_TEXT",				"RADAR",		"RADAR",		"RADAR",		"RADAR",		"STYLED1",				"STYLED1",					"STYLED1",					"STYLED1",				"STYLED1",				"STYLED2",				"STYLED2",				"STYLED2",				"STYLED2",				"STYLED3",				"STYLED3",				"STYLED3",				"STYLED3",				"STYLED4",				"STYLED4",				"STYLED4",				"STYLED4",				"STYLED5",				"STYLED5",				"STYLED5",				"STYLED6",				"STYLED6",				"STYLED6",				"STYLED7",				"STYLED7",				"STYLED7",				"MISSION_TIMERS",						"MISSION_TIMERS",				"MISSION_TIMERS",		"MISSION_TIMERS",			"MISSION_TIMERS",			"STATUS_TEXT",				"STATUS_TEXT",					"STATUS_TEXT",			"STATUS_TEXT",					"STATUS_TEXT_BAR",			"STATUS_TEXT_BAR",			"STATUS_TEXT_BAR",			"STATUS_TEXT_BAR",			"RADIO_STATION",		"RADIO_STATION",		"RADIO_STATION",		"GARAGE_MESSAGES",	"GARAGE_MESSAGES",	"GARAGE_MESSAGES",	"GARAGE_MESSAGES",	"CUSTOM_TEXT",			"CUSTOM_TEXT",			"CUSTOM_TEXT",			"CUSTOM_TEXT",			"CUSTOM_TEXT" };
				std::string keys[] =			{ "POS_X",			"POS_Y",		"SIZE_X",		"SIZE_Y",		"POS_X",		"POS_Y",		"SIZE_X",		"SIZE_Y",		"POS_X",		"POS_Y",		"SIZE_X",			"SIZE_Y",			"BAR_X",			"BAR_Y",			"BAR_SIZE_X",			"BAR_SIZE_Y",			"ICON_X",				"ICON_Y",				"ICON_SIZE_X",			"ICON_SIZE_Y",			"POS_X",		"POS_Y",		"SIZE_X",			"SIZE_Y",			"ICON_X",				"ICON_Y",				"ICON_SIZE_X",			"ICON_SIZE_Y",			"BAR_X",			"BAR_Y",			"BAR_SIZE_X",			"BAR_SIZE_Y",			"POS_X",		"POS_Y",		"SIZE_X",			"SIZE_Y",			"BAR_X",			"BAR_Y",			"BAR_SIZE_X",			"BAR_SIZE_Y",			"ICON_X",				"ICON_Y",				"ICON_SIZE_X",			"ICON_SIZE_Y",			"POS_X",		"POS_Y",		"SIZE_X",			"SIZE_Y",			"POS_X",		"POS_Y",		"SIZE_X",		"SIZE_Y",		"POS_X",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"SPACE",						"POS_X",		"POS_Y",		"SIZE_X",		"SIZE_Y",		"SLANT",		"POS_X",			"POS_Y",			"SIZE_X",			"SIZE_Y",			"SLANT",			"POS_X",			"POS_Y",			"SIZE_X",			"SIZE_Y",			"LINEWIDTH",			"POS_X1",							"SIZE_X1",								"POS_X",			"POS_Y",			"SIZE_X",			"SIZE_Y",			"WIDTH",			"BORDER_SIZE",				"POS_X",		"POS_Y",		"SIZE_X",		"SIZE_Y",		"POS_Y",				"POS_Y1",					"POS_Y2",					"SIZE_X",				"SIZE_Y",				"POS_X",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_X",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_X",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_X1",								"POS_X2",						"POS_Y",				"SIZE_X",					"SIZE_Y",					"POS_X1",					"POS_X2",						"POS_Y",				"SPACE",						"POS_X",					"POS_Y",					"SIZE_X",					"SIZE_Y",					"POS_Y",				"SIZE_X",				"SIZE_Y",				"POS_Y",			"SIZE_X",			"SIZE_Y",			"LINEWIDTH",		"POS_X",				"POS_Y",				"SIZE_X",				"SIZE_Y",				"LINEWIDTH" };
				float		incr[] =			{ 1.0f,				1.0f,			0.01f,			0.01f,			1.0f,			1.0f,			0.01f,			0.01f,			1.0f,			1.0f,			0.01f,				0.01f,				2.0f,				2.0f,				1.0f,					1.0f,					2.0f,					2.0f,					0.5f,					0.5f,					1.0f,			1.0f,			0.01f,				0.01f,				2.0f,					2.0f,					0.5f,					0.5f,					2.0f,				2.0f,				1.0f,					1.0f,					1.0f,			1.0f,			0.01f,				0.01f,				2.0f,				2.0f,				1.0f,					1.0f,					2.0f,					2.0f,					0.5f,					0.5f,					1.0f,			1.0f,			1.0f,				1.0f,				1.0f,			1.0f,			0.01f,			0.01f,			2.0f,					2.0f,					1.0f,					1.0f,					1.0f,							1.0f,			1.0f,			0.01f,			0.01f,			0.01f,			1.0f,				1.0f,				0.01f,				0.01f,				0.01f,				1.0f,				1.0f,				0.01f,				0.01f,				5.0f,					1.0f,								0.01f,									1.0f,				1.0f,				0.01f,				0.01f,				1.0f,				1.0f,						1.0f,			1.0f,			1.0f,			1.0f,			2.0f,					1.0f,						1.0f,						0.01f,					0.01f,					2.0f,					2.0f,					0.01f,					0.01f,					2.0f,					2.0f,					0.01f,					0.01f,					2.0f,					2.0f,					0.01f,					0.01f,					2.0f,					0.01f,					0.01f,					2.0f,					0.01f,					0.01f,					2.0f,					0.01f,					0.01f,					2.0f,									2.0f,							2.0f,					0.01f,						0.02f,						1.0f,						1.0f,							1.0f,					0.01f,							1.0f,						1.0f,						0.5f,						1.0f,						1.0f,					0.01f,					0.02f,					1.0f,				0.01f,				0.02f,				10.0f,				1.0f,					1.0f,					0.01f,					0.02f,					10.0f };
				int			size = sizeof(incr) / sizeof(incr[0]);

				switch (menu_level)
				{
				default:
				case 0:
					if (KeyPressed(VK_ADD))
						chosen = (chosen == size - 1) ? 0 : chosen + 1;
					if (KeyPressed(VK_SUBTRACT))
						chosen = (chosen == 0) ? size - 1 : chosen - 1;
					sprintf(custom_text, labels[chosen].c_str());
						break;
				case 1:
					HudEditor::ModifyValueInIni((char*)sections[chosen].c_str(),
						(char*)keys[chosen].c_str(), incr[chosen]);
					break;
				}

				section = sections[chosen];
			}

		};
	}
}editHud;
