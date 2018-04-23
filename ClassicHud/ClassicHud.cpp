#include <plugin.h>

#include "IniReader.h"
#include "HudEditor.h"

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

using namespace plugin;

static int STYLE;

class ClassicHud {
public:
	static void TransformHud();

	ClassicHud() {

		static int keyPressTime = 0;

		STYLE = 1;
		settings.Init(STYLE);
		//CIniReader iniReader(CLASSICHUD_DAT_PATH);
		//settings.WEAPONS_TXD = iniReader.ReadString("SA_FILES", "WEAPONS_TXD", DEFAULT_WEAPONS_TXD);

		Events::initRwEvent += HudIcons::ClassicHudTextures;
		Events::shutdownRwEvent += HudIcons::ClassicHudTextureShutdown;

		Events::initRwEvent += Weapon::WeaponTextures;
		Events::shutdownRwEvent += Weapon::WeaponTexturesShutdown;

		Events::initRwEvent += [] {
			//screen::SetBaseResolution(900.0f);
			MobileTextures::Setup();

			{
				ClassicHud::TransformHud();
				CFont::Initialise();

				//MobileMenuSystem::InstallPatches();
				//MobileLoadingScreen::InstallPatches();
				MobileMenuPage::InstallPatches();
				MobileFrontEnd::InstallPatches();
			}
		};

		Events::shutdownRwEvent += [] {
			MobileTxdStorage::Instance().Shutdown();
		};

		Events::gameProcessEvent += [] {

			if (FindPlayerPed() && KeyPressed(VK_F9) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;

				STYLE = (STYLE >= 3) ? 0 : STYLE + 1;
				settings.Init(STYLE);

				Weapon::WeaponTexturesShutdown();
				Weapon::WeaponTextures();

				CFont::Initialise();

				//CHud::Shutdown();
				//CHud::Initialise();

				ClassicHud::TransformHud();

				MobileTxdStorage::Instance().Shutdown();
				MobileTextures::Setup();

				MobileMenuPage::InstallPatches();
				MobileFrontEnd::InstallPatches();
			}
		};
	}
} classicHud;



void ClassicHud::TransformHud()
{
	plugin::patch::RedirectCall(0x5BA8AF, HudIcons::HudTextures);
	plugin::patch::RedirectCall(0x5BA6A4, HudIcons::FontTextures);
	plugin::patch::RedirectCall(0x7187DB, HudIcons::FontData);

	Money::InstallPatches();
	Clock::InstallPatches();
	HudIcons::InstallPatches();
	Weapon::InstallPatches();
	Wanted::InstallPatches();
	Radar::InstallPatches();

	AreaName::InstallPatches();
	VehicleName::InstallPatches();
	Subtitles::InstallPatches();
	HelpText::InstallPatches();
	StyledTexts::InstallPatches();
	MissionTimers::InstallPatches();
	RadioStation::InstallPatches();
	GarageMessages::InstallPatches();
}