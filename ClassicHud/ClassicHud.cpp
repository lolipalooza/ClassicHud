#include <plugin.h>

#include "IniReader.h"
#include "HudEditor.h"

#include "CSpecialFX.h"

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

#include "3DMarkers.h"

using namespace plugin;

static int STYLE;
static int MAX_STYLE = STYLE_LCS;

class ClassicHud {
public:
	static void TransformHud();

	ClassicHud() {

		static int keyPressTime = 0;
		
		CIniReader iniReader(CLASSICHUD_INI_PATH);
		int random_style = iniReader.ReadInt("INITIALIZE", "Random", 0);
		STYLE = iniReader.ReadInt("INITIALIZE", "Style", 0);

		if (random_style)
			STYLE = rand() % (MAX_STYLE + 1);

		settings.Init(STYLE);

		Events::initRwEvent += HudIcons::ClassicHudTextures;
		Events::shutdownRwEvent += HudIcons::ClassicHudTextureShutdown;

		Events::initRwEvent += Weapon::WeaponTextures;
		Events::shutdownRwEvent += Weapon::WeaponTexturesShutdown;

		Events::initRwEvent += C3dMarkers::InitTextures;
		Events::shutdownRwEvent += C3dMarkers::ShutDownTextures;

		Events::initRwEvent += [] {
			//screen::SetBaseResolution(900.0f);
			MobileTextures::Setup();

			{
				ClassicHud::TransformHud();
				CFont::Initialise();
			}
		};

		Events::shutdownRwEvent += [] {
			MobileTxdStorage::Instance().Shutdown();
		};

		Events::gameProcessEvent += [] {

			if (FindPlayerPed() && KeyPressed(VK_F9) && CTimer::m_snTimeInMilliseconds - keyPressTime > 500) {
				keyPressTime = CTimer::m_snTimeInMilliseconds;

				STYLE = (STYLE >= MAX_STYLE) ? 0 : STYLE + 1;
				settings.Init(STYLE);

				Weapon::WeaponTexturesShutdown();
				Weapon::WeaponTextures();

				CFont::Initialise();

				//CHud::Shutdown();
				//CHud::Initialise();

				MobileTxdStorage::Instance().Shutdown();
				MobileTextures::Setup();

				ClassicHud::TransformHud();

				CSpecialFX::Init();
			}
		};
	}
} classicHud;



void ClassicHud::TransformHud()
{
	patch::RedirectCall(0x5BA8AF, HudIcons::HudTextures);
	patch::RedirectCall(0x5BA6A4, HudIcons::FontTextures);
	patch::RedirectCall(0x7187DB, HudIcons::FontData);

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

	MobileMenuSystem::InstallPatches();
	MobileLoadingScreen::InstallPatches();
	MobileMenuPage::InstallPatches();
	MobileFrontEnd::InstallPatches();

	C3dMarkers::InstallPatches();
}