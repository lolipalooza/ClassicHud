#include <plugin.h>

#include "Settings.h"
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

		Events::initRwEvent += [] {
			//screen::SetBaseResolution(900.0f);
			MobileTextures::Setup();

			{
				//MobileProgressBar::InstallPatches();
				//MobileMenuSystem::InstallPatches();
				MobileLoadingScreen::InstallPatches();
				//MobileMenuPage::InstallPatches();
				//MobileFrontEnd::InstallPatches();
			}
		};

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
		};
	}
} classicHud;
