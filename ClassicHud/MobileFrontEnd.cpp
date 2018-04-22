#include <plugin.h>
#include "MobileFrontEnd.h"
#include "game_sa\CPad.h"
#include "game_sa\CRadar.h"
#include "game_sa\CHudColours.h"
#include "game_sa\CVector2D.h"
#include "game_sa\CStats.h"
//#include "Settings.h"
#include <time.h>

MobileFrontEnd FrontEndMobileMenuManager;

void MobileFrontEnd::InstallPatches() {
    plugin::patch::RedirectJump(0x57B750, DrawBackground);
    plugin::patch::RedirectCall(0x57FEAB, CheckMouseInput);
    plugin::patch::RedirectCall(0x57B66F, ProcessMobileMenuOptions);
    plugin::patch::RedirectCall(0x57B702, ProcessMobileMenuOptions);
    plugin::patch::RedirectCall(0x5764E7, PrintBriefsText);
    plugin::patch::RedirectCall(0x574DC1, PrintStatsText);
    plugin::patch::RedirectCall(0x574E4D, PrintStatsText2);
    plugin::patch::RedirectCall(0x574F54, DrawStatsSlider);

    // PrintMap Patches
    // Legend
    plugin::patch::Set<BYTE>(0x5760A1, 0x83);
    plugin::patch::Set<BYTE>(0x5760A2, 0xC4);
    plugin::patch::Set<BYTE>(0x5760A3, 0x18);
    plugin::patch::Nop(0x5760A4, 0x90);
    plugin::patch::Nop(0x5760A5, 0x90);
    plugin::patch::Nop(0x5761D3, 0x90);
    plugin::patch::Nop(0x5761D4, 0x90);
    plugin::patch::Nop(0x5761D5, 0x90);
    plugin::patch::Nop(0x5761D6, 0x90);
    plugin::patch::Nop(0x5761D7, 0x90);
    plugin::patch::Nop(0x5761D8, 0x90);
    // Borders
    plugin::patch::Set(0x575E12, 5);
    plugin::patch::Set(0x575DC2, 5);
    plugin::patch::Set(0x575D6F, 5);
    plugin::patch::Set(0x575D1F, 5);
    plugin::patch::Set(0x575CCE, 5);
    plugin::patch::Set(0x575C84, 5);
    plugin::patch::Set(0x575C40, 5);
    plugin::patch::Set(0x575BF6, 5);
    // Place name 
    plugin::patch::Set(0x575F89, 5);
    // Help texts
    plugin::patch::SetChar(0x5762E7 + 1, 0);
    plugin::patch::SetChar(0x5762FD + 1, 0);
    // Legend text
    plugin::patch::Set(0x582DEE, 5);
    // PrintStats Patches
    plugin::patch::Set(0x5750BA, 5);
    plugin::patch::Set(0x57511B, 5);
    plugin::patch::Set(0x574957, 5);
}

void MobileFrontEnd::DrawBackground(void *ecx0) {
    CSprite2d::DrawRect(CRect(0.0f, 0.0f, 0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT), CRGBA(0, 0, 0, 255));

    if (FrontEndMenuManager.m_nCurrentMenuPage != 5) {
        RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

        // Background
        mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(MENU_BGMAP);
        mobileTex.m_nBackgroundSprite.Draw(CRect(SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.x), SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.y), SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.x) + SCREEN_WIDTH + SCREEN_COORD(900.0f), SCREEN_COORD(-FrontEndMobileMenuManager.BGCoords.y) + SCREEN_HEIGHT + SCREEN_COORD(1024.0f)), CRGBA(255, 255, 255, FrontEndMobileMenuManager.BGAlpha));

        // Mask
        mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(MENU_MAINMASK);
        mobileTex.m_nBackgroundSprite.Draw(CRect(0.0, 0.0f, 0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT), CRGBA(255, 255, 255, 250));
        mobileTex.m_nBackgroundSprite.m_pTexture = nullptr;

        int coordsId;

        if (FrontEndMobileMenuManager.BGFrameFirst)
            coordsId = 1;
        else if (FrontEndMobileMenuManager.BGFrameSecond)
            coordsId = 2;
        else
            coordsId = 0;

        MobileFrontEnd::GetRandomBGCoords(coordsId);
    }

    // Char     
    int charId;

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_MAIN_MENU)
        charId = MENU_CHAR_0;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_OPTIONS)
        charId = MENU_CHAR_1;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_SELECT_GAME)
        charId = MENU_CHAR_5;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_QUIT_GAME_2)
        charId = MENU_CHAR_6;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_LANGUAGE)
        charId = MENU_CHAR_7;
    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEF)
        charId = MENU_CHAR_8;
    else
        charId = MENU_CHAR_2;

    if (FrontEndMobileMenuManager.CharAlpha != 255)
        FrontEndMobileMenuManager.CharAlpha += 5;

    mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(charId);
    if (FrontEndMenuManager.m_nCurrentMenuPage != 0)
        mobileTex.m_nBackgroundSprite.Draw(CRect(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(843.7f / 2),
            SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2) + SCREEN_MULTIPLIER(375.0f), SCREEN_COORD_CENTER_Y - SCREEN_COORD(843.7f / 2) + SCREEN_MULTIPLIER(837.0f)), CRGBA(255, 255, 255, FrontEndMobileMenuManager.CharAlpha));

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_MAP) {
        MobileFrontEnd::PrintMap();
        MobileFrontEnd::PrintLegend();
        MobileFrontEnd::PrintPlaceName();
    }

    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_CONTROLS_VEHICLE_ONFOOT) {
        FrontEndMenuManager.DrawControllerSetupScreen();
    }

    else if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_EMPTY) {
        FrontEndMenuManager.SaveSettings();
        exit(0);
    }

    else {
        MobileFrontEnd::DrawStandardMenu();
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_STATS) {
        MobileFrontEnd::PrintStats();
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_BRIEF) {
        FrontEndMenuManager.PrintBriefs();
    }

    if (FrontEndMenuManager.m_nCurrentMenuPage == MENUPAGE_AUDIO_SETTINGS) {
        MobileFrontEnd::PrintRadioStationList();
    }

    if (FrontEndMenuManager.m_bScanningUserTracks) {
        // TODO: ScanningUserTracks
        CFont::SetBackground(0, 0);
        CFont::SetProp(1);
        CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetAlignment(ALIGN_RIGHT);
        CFont::SetOutlinePosition(2);
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
        CFont::SetScale(SCREEN_MULTIPLIER(0.6f), SCREEN_MULTIPLIER(1.2f));
        CFont::PrintStringFromBottom(SCREEN_COORD_RIGHT(10.0f), SCREEN_COORD_BOTTOM(-35.0f), TheText.Get("FEA_SMP"));

        FrontEndMenuManager.m_bScanningUserTracks = 0;
    }

    if (FrontEndMenuManager.m_bDrawMouse) {
        // TODO: Get cursor icon from system.
        POINT position;
        if (GetCursorPos(&position)) {
            if (FrontEndMenuManager.m_nCurrentMenuPage == 5 && CPad::NewMouseControllerState.lmb)
                FrontEndMenuManager.m_apTextures[24].Draw(position.x, position.y, SCREEN_MULTIPLIER(22.5f), SCREEN_MULTIPLIER(22.5f), CRGBA(255, 255, 255, 255));
            else
                FrontEndMenuManager.m_apTextures[23].Draw(position.x, position.y, SCREEN_MULTIPLIER(22.5f), SCREEN_MULTIPLIER(22.5f), CRGBA(255, 255, 255, 255));

        }
    }
}

void MobileFrontEnd::GetRandomBGCoords(int coordsId) {
    switch (coordsId) {
    case 0:
        if (!FrontEndMenuManager.m_bMenuActive) {
            FrontEndMobileMenuManager.BGCoords.x = 0.0f;
            FrontEndMobileMenuManager.BGCoords.y = 0.0f;
            FrontEndMobileMenuManager.BGAlpha = 0;
        }
        else {
            if (FrontEndMobileMenuManager.BGCoords.y >= SCREEN_COORD(750.0f)) {
                // End Animation
                if (FrontEndMobileMenuManager.BGAlpha != 0.0f)
                    FrontEndMobileMenuManager.BGAlpha -= 1;

                else if (FrontEndMobileMenuManager.BGAlpha == 0.0f) {
                    if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                        FrontEndMobileMenuManager.BGAlpha += 1;

                    FrontEndMobileMenuManager.BGCoords.x = 640.0f;
                    FrontEndMobileMenuManager.BGCoords.y = 1024.0f;

                    FrontEndMobileMenuManager.BGFrameFirst = 1;
                }
            }
            else {
                // Start Animation
                if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                    FrontEndMobileMenuManager.BGAlpha += 1;
                if (FrontEndMobileMenuManager.BGCoords.y != SCREEN_COORD(1024.0f))
                    FrontEndMobileMenuManager.BGCoords.y += 1.0f * 0.3f;
            }
        }
        break;
    case 1:
        if (!FrontEndMenuManager.m_bMenuActive) {
            FrontEndMobileMenuManager.BGCoords.x = 0.0f;
            FrontEndMobileMenuManager.BGCoords.y = 0.0f;
            FrontEndMobileMenuManager.BGAlpha = 0;
        }
        else {
            if (FrontEndMobileMenuManager.BGCoords.y <= SCREEN_COORD(330.0f)) {
                // End Animation
                if (FrontEndMobileMenuManager.BGAlpha != 0.0f)
                    FrontEndMobileMenuManager.BGAlpha -= 1;

                else if (FrontEndMobileMenuManager.BGAlpha == 0.0f) {
                    if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                        FrontEndMobileMenuManager.BGAlpha += 1;

                    FrontEndMobileMenuManager.BGCoords.x = 800.0f;
                    FrontEndMobileMenuManager.BGCoords.y = 0.0f;

                    FrontEndMobileMenuManager.BGFrameFirst = 0;
                    FrontEndMobileMenuManager.BGFrameSecond = 1;
                }
            }
            else {
                // Start Animation
                if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                    FrontEndMobileMenuManager.BGAlpha += 1;
                if (FrontEndMobileMenuManager.BGCoords.y != SCREEN_COORD(0.0f))
                    FrontEndMobileMenuManager.BGCoords.y -= 1.0f * 0.3f;
            }
        }
        break;
    case 2:
        if (!FrontEndMenuManager.m_bMenuActive) {
            FrontEndMobileMenuManager.BGCoords.x = 0.0f;
            FrontEndMobileMenuManager.BGCoords.y = 0.0f;
            FrontEndMobileMenuManager.BGAlpha = 0;
        }
        else {
            if (FrontEndMobileMenuManager.BGCoords.x < SCREEN_COORD(40.0f) || FrontEndMobileMenuManager.BGCoords.y >= SCREEN_COORD(800.0f)) {
                // End Animation
                if (FrontEndMobileMenuManager.BGAlpha != 0.0f)
                    FrontEndMobileMenuManager.BGAlpha -= 1;

                else if (FrontEndMobileMenuManager.BGAlpha == 0.0f) {
                    if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                        FrontEndMobileMenuManager.BGAlpha += 1;

                    FrontEndMobileMenuManager.BGCoords.x = 0.0f;
                    FrontEndMobileMenuManager.BGCoords.y = 0.0f;

                    FrontEndMobileMenuManager.BGFrameZero = 1;
                    FrontEndMobileMenuManager.BGFrameFirst = 0;
                    FrontEndMobileMenuManager.BGFrameSecond = 0;
                }
            }
            else {
                // Start Animation
                if (FrontEndMobileMenuManager.BGAlpha != 40.0f)
                    FrontEndMobileMenuManager.BGAlpha += 1;
                if (FrontEndMobileMenuManager.BGCoords.x != SCREEN_COORD(900.0f))
                    FrontEndMobileMenuManager.BGCoords.x -= 1.0f * 0.3f;
                if (FrontEndMobileMenuManager.BGCoords.y != SCREEN_COORD(1024.0f))
                    FrontEndMobileMenuManager.BGCoords.y += 1.0f * 0.4f;
            }
        }
        break;
    };
}

float __fastcall MobileFrontEnd::CheckMouseInput(float a1) {
    return SCREEN_COORD_CENTER_Y - SCREEN_COORD(-a1 - 32.5f);
}

void MobileFrontEnd::DrawStandardMenu() {
    CFont::SetBackground(0, 0);
    CFont::SetProp(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetOutlinePosition(2);
    CFont::SetRightJustifyWrap(12.5f);
    CFont::SetCentreSize(SCREEN_COORD_MAX_X);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));

    // Header
    if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName[0]) {
        if (FrontEndMenuManager.m_nCurrentMenuPage != 5 || !FrontEndMenuManager.field_78) {
            CFont::SetAlignment(ALIGN_LEFT);
            CFont::SetFontStyle(FONT_GOTHIC);
            CFont::SetScale(SCREEN_MULTIPLIER(1.8f), SCREEN_MULTIPLIER(3.6f));
            CFont::SetOutlinePosition(2);
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            if (FrontEndMenuManager.m_nCurrentMenuPage != 0)
                CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName));
            else
                CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_szTitleName));
        }
    }

    // Actions
    if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_nActionType == 1)
    {
        static char* pText;
        CFont::SetFontStyle(FONT_SUBTITLES);
        CFont::SetAlignment(ALIGN_LEFT);
        CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
        CFont::SetOutlinePosition(2);
        CFont::SetColor(CRGBA(255, 255, 255, 255));
        CFont::SetDropColor(CRGBA(0, 0, 0, 255));

        switch (FrontEndMenuManager.m_nCurrentMenuPage)
        {
        case 6:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FESZ_QQ" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        case 35:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FEQ_SRW" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        case 17:
        {
            switch (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_bSelectedSaveGame + 1]) {
            case 0:
                    pText = TheText.Get("FESZ_QO");
                    break;
            case 2:
                    pText = TheText.Get("FESZ_QC");
                    break;
            default:
                pText = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
                break;
            }
            break;
        }
        case 11:
        {
            pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FES_LCG" : MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        default:
        {
            pText = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[0].m_szName);
            break;
        }
        }
        CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(640.0f / 2), pText);
    }

    for (unsigned int i = 0; i < 12; i++) {
        CFont::SetFontStyle(FONT_MENU);
        CFont::SetOutlinePosition(2);

        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType != 1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_szName[0]) {
            const char* LeftColumn = nullptr;
            const char* RightColumn = nullptr;
            char ReservedSpace[64];

            if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType <= MENU_ENTRY_SAVE_8) { 
                switch (FrontEndMobileMenuManager.SlotValidation[i]) {
                case 0:
                    LeftColumn = plugin::CallAndReturn<const char*, 0x5D0F40>(i - 1);
                    break;
                case 2:
                    LeftColumn = TheText.Get("FESZ_CS");
                    break;
                }

                if (!LeftColumn || !LeftColumn[0]) {
                    sprintf(gString, "FEM_SL%X", i);
                    LeftColumn = TheText.Get(gString);

                }
            }

            else if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_MISSIONPACK) {
            }

            else if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_JOYMOUSE) {
                LeftColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FEJ_TIT" : "FEC_MOU");
            }

            else {
                LeftColumn = TheText.Get(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_szName);
            }

            CAERadioTrackManager RadioEntity;

            switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType) {
            case 30:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bRadioEq ? "FEM_ON" : "FEM_OFF");
                break;
            case 31:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bRadioAutoSelect ? "FEM_ON" : "FEM_OFF");
                break;
            case 32:
                RightColumn = RadioEntity.GetRadioStationName(FrontEndMenuManager.m_nRadioStation);
                break;
            case 33:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bMapLegend ? "FEM_ON" : "FEM_OFF");
                break;
            case 25:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bShowSubtitles ? "FEM_ON" : "FEM_OFF");
                break;
            case 26:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bWidescreenOn ? "FEM_ON" : "FEM_OFF");
                break;
            case 34:
                switch (FrontEndMenuManager.m_nRadarMode) {
                case 0:
                    RightColumn = TheText.Get("FED_RDM");
                    break;
                case 1:
                    RightColumn = TheText.Get("FED_RDB");
                    break;
                case 2:
                    RightColumn = TheText.Get("FEM_OFF");
                    break;
                }
                break;
            case 35:
                switch (FrontEndMenuManager.m_bHudOn) {
                case 0:
                    RightColumn = TheText.Get("FEM_OFF");
                    FrontEndMenuManager.m_nRadarMode = 2;
                    break;
                case 1:
                    RightColumn = TheText.Get("FEM_ON");
                    FrontEndMenuManager.m_nRadarMode = 0;
                    break;
                }
                break;
            case 65:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bSavePhotos ? "FEM_ON" : "FEM_OFF");
                break;
            case 63:
                switch (FrontEndMenuManager.m_nRadioMode) {
                case 0:
                    RightColumn = TheText.Get("FEA_PR1");
                    break;
                case 1:
                    RightColumn = TheText.Get("FEA_PR2");
                    break;
                case 2:
                    RightColumn = TheText.Get("FEA_PR3");
                    break;
                }
                break;
            case 24:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bFrameLimiterOn ? "FEM_ON" : "FEM_OFF");
                break;
            case 43:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bMipMapping ? "FEM_ON" : "FEM_OFF");
                break;
            case 64:
                RightColumn = TheText.Get(FrontEndMenuManager.m_bTracksAutoScan ? "FEM_ON" : "FEM_OFF");
                break;
            case 46:
                RightColumn = TheText.Get(!FrontEndMenuManager.bInvertMouseY ? "FEM_ON" : "FEM_OFF");
                break;
            case 47:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadX1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 48:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadY1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 49:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadX2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 50:
                RightColumn = TheText.Get(FrontEndMenuManager.invertPadY2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 51:
                RightColumn = TheText.Get(FrontEndMenuManager.swapPadAxis1 ? "FEM_ON" : "FEM_OFF");
                break;
            case 52:
                RightColumn = TheText.Get(FrontEndMenuManager.swapPadAxis2 ? "FEM_ON" : "FEM_OFF");
                break;
            case 59:
                RightColumn = TheText.Get(CVehicle::m_bEnableMouseSteering ? "FEM_ON" : "FEM_OFF");
                break;
            case 60:
                RightColumn = TheText.Get(CVehicle::m_bEnableMouseFlying ? "FEM_ON" : "FEM_OFF");
                break;
            case 56:
            {
                const char* pszResolution = ((const char**(*)())0x745AF0)()[FrontEndMenuManager.m_nResolution];

                if (!pszResolution)
                    pszResolution = "";

                strncpy(ReservedSpace, pszResolution, sizeof(ReservedSpace));
                RightColumn = ReservedSpace;
            }
            break;
            case 44:
                if (FrontEndMenuManager.m_nAntiAliasingLevel <= 1)
                    RightColumn = TheText.Get("FEM_OFF");
                else {
                    switch (FrontEndMenuManager.m_nAntiAliasingLevel)
                    {
                    case 2:
                        RightColumn = "2x";
                        break;
                    case 3:
                        RightColumn = "4x";
                        break;
                    case 4:
                        RightColumn = "8x";
                        break;
                    }
                }
                break;
            case 42:
                switch (g_fx.GetFxQuality()) {
                case FXQUALITY_LOW:
                    RightColumn = TheText.Get("FED_FXL");
                    break;
                case FXQUALITY_MEDIUM:
                    RightColumn = TheText.Get("FED_FXM");
                    break;
                case FXQUALITY_HIGH:
                    RightColumn = TheText.Get("FED_FXH");
                    break;
                case FXQUALITY_VERY_HIGH:
                    RightColumn = TheText.Get("FED_FXV");
                    break;
                }
                break;
            case 58:
                RightColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FET_CCN" : "FET_SCN");
                break;
            }

            unsigned int savedAlpha;
            float f_leftPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2);
            float fPosnXForStats = SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2);
            float f_rightPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(-1113.0f / 2);
            float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nPosnY) + (0.0f / 2);

            if (i == FrontEndMenuManager.m_nSelectedMenuItem) {
                if (FrontEndMenuManager.m_nCurrentMenuPage != 5) {
                    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

                    if (FrontEndMenuManager.m_nCurrentMenuPage == 0)
                        CSprite2d::DrawRect(CRect(fPosnXForStats - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (fPosnXForStats - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(330.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));
                    else
                        CSprite2d::DrawRect(CRect(f_leftPosX - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (f_leftPosX - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(725.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));

                    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
                }
            }

            CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));

            if (FrontEndMenuManager.m_nCurrentMenuPage == 7 || FrontEndMenuManager.m_nCurrentMenuPage == 9 || FrontEndMenuManager.m_nCurrentMenuPage == 10 || FrontEndMenuManager.m_nCurrentMenuPage == 16) {
                float width = CFont::GetStringWidth((char*)LeftColumn, true, false);

                if (width > SCREEN_COORD(690.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.9f * SCREEN_COORD(690.0f) / width), SCREEN_MULTIPLIER(1.7f));
            }

            // Print left column
            CFont::SetDropColor(CRGBA(0, 0, 0, 255));
            CFont::SetColor(CRGBA(255, 255, 255, 255));
            CFont::SetAlignment(ALIGN_LEFT);

            if (FrontEndMenuManager.m_nCurrentMenuPage == 0)
                CFont::PrintString(fPosnXForStats, fPosY, (char*)LeftColumn);
            else
                CFont::PrintString(f_leftPosX, fPosY, (char*)LeftColumn);


            // Print right column
            if (RightColumn) {
                float width = CFont::GetStringWidth((char*)RightColumn, true, false);

                if (width > SCREEN_COORD(312.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.8f * SCREEN_COORD(312.0f) / width), SCREEN_MULTIPLIER(1.7f));

                CFont::SetAlignment(ALIGN_RIGHT);
                CFont::PrintString(f_rightPosX, fPosY, (char*)RightColumn);
            }

            // Sliders
            CVector2D vecPosition;
            CVector2D vecScale;
            vecPosition.x = 285.0f;
            vecPosition.y = MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nPosnY + 2.0f;
            vecScale.x = 265.0f;
            vecScale.y = 28.5f;

            switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[i].m_nActionType)
            {
            case 27:
            {
                // Brightness
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nBrightness * 0.0026041667f, true);
                break;
            }
            case 28:
            {
                // Radio Volume
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nRadioVolume * 0.015625f, true);
                break;
            }
            case 29:
            {
                // SFX Volume
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nSfxVolume * 0.015625f, true);
                break;
            }
            case 61:
            {
                // Draw Distance
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), (FrontEndMenuManager.m_fDrawDistance - 0.925f) * 1.1428572f, true);
                break;
            }
            case 62:
            {
                // Mouse Sensitivity
                DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), (CCamera::m_fMouseAccelHorzntl / 0.005f), true);
                break;
            }
            }
        }
    }
}

void __fastcall MobileFrontEnd::ProcessMobileMenuOptions(void *ecx0, int, signed char nArrowsInput, bool *bReturn, bool bEnterInput) {
    switch (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nSelectedMenuItem].m_nActionType)
    {
    case 2:
        *bReturn = true;
        return;
    case 25:
        FrontEndMenuManager.m_bShowSubtitles = FrontEndMenuManager.m_bShowSubtitles == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 33:
        FrontEndMenuManager.m_bMapLegend = FrontEndMenuManager.m_bMapLegend == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 26:
        FrontEndMenuManager.m_bWidescreenOn = FrontEndMenuManager.m_bWidescreenOn == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 35:
        FrontEndMenuManager.m_bHudOn = FrontEndMenuManager.m_bHudOn == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 23:
        FrontEndMenuManager.field_31 = FrontEndMenuManager.field_31 == false;
        return;
    case 30:
        FrontEndMenuManager.m_bRadioEq = FrontEndMenuManager.m_bRadioEq == false;
        ((char(__stdcall *)(char))0x506F90)(FrontEndMenuManager.m_bRadioEq);
        FrontEndMenuManager.SaveSettings();
        return;
    case 31:
        FrontEndMenuManager.m_bRadioAutoSelect = FrontEndMenuManager.m_bRadioAutoSelect == false;
        ((char(__stdcall *)(char))0x506F80)(FrontEndMenuManager.m_bRadioAutoSelect);
        FrontEndMenuManager.SaveSettings();
        return;
    case 21:
        if (nArrowsInput >= 0)
        {
            if (FrontEndMenuManager.field_0)
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed == 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 150.0f;
                else if (FrontEndMenuManager.m_fStatsScrollSpeed == 150.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 30.0f;
            }
            else
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed == 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 150.0f;
                else
                    FrontEndMenuManager.m_fStatsScrollSpeed = 0.0f;

                FrontEndMenuManager.field_0 = true;
            }
        }
        else
        {
            if (FrontEndMenuManager.field_0)
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed != 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 0.0f;
                FrontEndMenuManager.field_0 = false;
            }
            else
            {
                if (FrontEndMenuManager.m_fStatsScrollSpeed == 0.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 150.0f;
                else if (FrontEndMenuManager.m_fStatsScrollSpeed == 150.0f)
                    FrontEndMenuManager.m_fStatsScrollSpeed = 30.0f;
            }
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 32:
        FrontEndMenuManager.ScrollRadioStations(nArrowsInput);
        FrontEndMenuManager.SaveSettings();
        return;
    case 34:
        if (nArrowsInput >= 0)
        {
            if (++FrontEndMenuManager.m_nRadarMode > 2)
                FrontEndMenuManager.m_nRadarMode = 0;
        }
        else
        {
            if (FrontEndMenuManager.m_nRadarMode)
                --FrontEndMenuManager.m_nRadarMode;
            else
                FrontEndMenuManager.m_nRadarMode = 2;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 3:
    case 4:
    case 5:
        FrontEndMenuManager.SwitchToNewScreen(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nSelectedMenuItem].m_nTargetMenu);
        return;
    case 11:
        FrontEndMenuManager.field_160 = 261 * FrontEndMenuManager.m_nSelectedMenuItem - 169;
        FrontEndMenuManager.SwitchToNewScreen(8);
    return;
    case 10:
        FrontEndMenuManager.ProcessMissionPackNewGame();
        return;
    case 13:
        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nSelectedMenuItem].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nSelectedMenuItem].m_nType <= MENU_ENTRY_SAVE_8)
        {
            FrontEndMenuManager.m_bSelectedSaveGame = FrontEndMenuManager.m_nSelectedMenuItem - 1;
            if (FrontEndMenuManager.m_nCurrentMenuPage == 9)
            {
                if (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nSelectedMenuItem] != 1 && FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nSelectedMenuItem] != 2)
                    FrontEndMenuManager.SwitchToNewScreen(11);
            }
            else if (FrontEndMenuManager.m_nCurrentMenuPage == 10)
            {
               if (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_nSelectedMenuItem] != 1)
                    FrontEndMenuManager.SwitchToNewScreen(12);
            }
        }
        return;
    case 18:
        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nSelectedMenuItem].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[FrontEndMenuManager.m_nSelectedMenuItem].m_nType <= MENU_ENTRY_SAVE_8)
        {
            FrontEndMenuManager.m_bSelectedSaveGame = FrontEndMenuManager.m_nSelectedMenuItem - 1;
            FrontEndMenuManager.SwitchToNewScreen(17);
        }
        return;
    case 12:
        *(char*)0xB72910 = FrontEndMenuManager.field_160;
        FrontEndMenuManager.DoSettingsBeforeStartingAGame();
        return;
    case 14:
        *(char*)0xB72910 = 0;
        FrontEndMenuManager.DoSettingsBeforeStartingAGame();
        FrontEndMenuManager.m_bDontDrawFrontEnd = true;
        return;
    case 15:
        FrontEndMenuManager.m_bDontDrawFrontEnd = true;
        return;
    case 46:
        FrontEndMenuManager.bInvertMouseY = FrontEndMenuManager.bInvertMouseY == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 47:
        FrontEndMenuManager.invertPadX1 = FrontEndMenuManager.invertPadX1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 48:
        FrontEndMenuManager.invertPadY1 = FrontEndMenuManager.invertPadY1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 49:
        FrontEndMenuManager.invertPadX2 = FrontEndMenuManager.invertPadX2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 50:
        FrontEndMenuManager.invertPadY2 = FrontEndMenuManager.invertPadY2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 51:
        FrontEndMenuManager.swapPadAxis1 = FrontEndMenuManager.swapPadAxis1 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 52:
        FrontEndMenuManager.swapPadAxis2 = FrontEndMenuManager.swapPadAxis2 == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 59:
        if (!FrontEndMenuManager.m_nController)
        {
            CVehicle::m_bEnableMouseSteering = CVehicle::m_bEnableMouseSteering == false;
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 60:
        if (!FrontEndMenuManager.m_nController)
        {
            CVehicle::m_bEnableMouseFlying = CVehicle::m_bEnableMouseFlying == false;
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 24:
        FrontEndMenuManager.m_bFrameLimiterOn = FrontEndMenuManager.m_bFrameLimiterOn == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 64:
        FrontEndMenuManager.m_bTracksAutoScan = FrontEndMenuManager.m_bTracksAutoScan == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 65:
        FrontEndMenuManager.m_bSavePhotos = FrontEndMenuManager.m_bSavePhotos == false;
        FrontEndMenuManager.SaveSettings();
        return;
    case 58:
        if (FrontEndMenuManager.m_nController == 1)
        {
            FrontEndMenuManager.m_nController = 0;
            *(bool*)0xB6EC2E = true;
        }
        else
        {
            FrontEndMenuManager.m_nController = 1;
            *(bool*)0xB6EC2E = false;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 56:
        if (bEnterInput)
        {
            if (FrontEndMenuManager.m_nResolution != FrontEndMenuManager.m_nAppliedResolution)
            {
                FrontEndMenuManager.m_nAppliedResolution = FrontEndMenuManager.m_nResolution;
                ((void(*)(int))0x745C70)(FrontEndMenuManager.m_nAppliedResolution);

                FrontEndMenuManager.m_bDrawMouse = true;
                FrontEndMenuManager.SaveSettings();
            }
        }
        else
        {
            char** pVideoModes = ((char**(*)())0x745AF0)();
            int nNumVideoModes = RwEngineGetNumVideoModes();

            if (nArrowsInput > 0)
            {
                int		nCurrentVidMode = FrontEndMenuManager.m_nResolution + 1;

                if (nCurrentVidMode >= nNumVideoModes)
                    nCurrentVidMode = 0;

                while (!pVideoModes[nCurrentVidMode])
                {
                    ++nCurrentVidMode;

                    if (nCurrentVidMode >= nNumVideoModes)
                        nCurrentVidMode = 0;
                }

                FrontEndMenuManager.m_nResolution = nCurrentVidMode;
            }
            else
            {
                int nCurrentVidMode = FrontEndMenuManager.m_nResolution - 1;

                if (nCurrentVidMode < 0)
                    nCurrentVidMode = nNumVideoModes - 1;

                while (!pVideoModes[nCurrentVidMode])
                {
                    --nCurrentVidMode;

                    if (nCurrentVidMode < 0)
                        nCurrentVidMode = nNumVideoModes - 1;
                }

                FrontEndMenuManager.m_nResolution = nCurrentVidMode;
            }
        }
        return;
    case 44:
        if (bEnterInput)
        {
            if (FrontEndMenuManager.m_nAntiAliasingLevel != FrontEndMenuManager.m_nAppliedAntiAliasingLevel)
            {
                FrontEndMenuManager.m_nAppliedAntiAliasingLevel = FrontEndMenuManager.m_nAntiAliasingLevel;

                RwD3D9ChangeMultiSamplingLevels(FrontEndMenuManager.m_nAppliedAntiAliasingLevel);
                ((void(*)(int))0x745C70)(FrontEndMenuManager.m_nAppliedResolution);
                FrontEndMenuManager.SaveSettings();
            }
        }
        else
        {
            int nNumMultiSamplingModes = RwD3D9EngineGetMaxMultiSamplingLevels();

            if (nNumMultiSamplingModes > 4)
                nNumMultiSamplingModes = 4;

            if (nArrowsInput > 0)
            {
                int nCurrentMode = FrontEndMenuManager.m_nAntiAliasingLevel + 1;

                if (nCurrentMode > nNumMultiSamplingModes)
                    nCurrentMode = 1;

                FrontEndMenuManager.m_nAntiAliasingLevel = nCurrentMode;
            }
            else
            {
                int nCurrentMode = FrontEndMenuManager.m_nAntiAliasingLevel - 1;

                if (nCurrentMode <= 0)
                    nCurrentMode = nNumMultiSamplingModes;

                FrontEndMenuManager.m_nAntiAliasingLevel = nCurrentMode;
            }
        }
        return;
    case 42:
        if (nArrowsInput >= 0)
        {
            switch (g_fx.GetFxQuality())
            {
            case FXQUALITY_LOW:
                g_fx.SetFxQuality(FXQUALITY_MEDIUM);
                break;
            case FXQUALITY_MEDIUM:
                g_fx.SetFxQuality(FXQUALITY_HIGH);
                break;
            case FXQUALITY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_VERY_HIGH);
                break;
            case FXQUALITY_VERY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_LOW);
                break;
            }
        }
        else
        {
            switch (g_fx.GetFxQuality())
            {
            case FXQUALITY_LOW:
                g_fx.SetFxQuality(FXQUALITY_VERY_HIGH);
                break;
            case FXQUALITY_MEDIUM:
                g_fx.SetFxQuality(FXQUALITY_LOW);
                break;
            case FXQUALITY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_MEDIUM);
                break;
            case FXQUALITY_VERY_HIGH:
                g_fx.SetFxQuality(FXQUALITY_HIGH);
                break;
            }
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 63:
        if (nArrowsInput >= 0)
        {
            if (++FrontEndMenuManager.m_nRadioMode > 2)
                FrontEndMenuManager.m_nRadioMode = 0;
        }
        else
        {
            if (FrontEndMenuManager.m_nRadioMode)
                --FrontEndMenuManager.m_nRadioMode;
            else
                FrontEndMenuManager.m_nRadioMode = 2;
        }
        FrontEndMenuManager.SaveSettings();
        return;
    case 54:
        FrontEndMenuManager.m_bDontDrawFrontEnd = true;
        return;
    case 57:
        FrontEndMenuManager.SetDefaultPreferences((eMenuPage)MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu);

        if (MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu == 36)
            plugin::CallAndReturn<char, 0x531F20>();

        FrontEndMenuManager.SaveSettings();
        FrontEndMenuManager.SwitchToNewScreen(MenuPages[FrontEndMenuManager.m_nCurrentMenuPage].m_aButtons[2].m_nTargetMenu);
        return;
    case 7:
        FrontEndMenuManager.SwitchToNewScreen(FrontEndMenuManager.m_nController == 1 ? 40 : 39);
        return;
    case 8:
        FrontEndMenuManager.field_B7 = false;
        FrontEndMenuManager.SwitchToNewScreen(38);
        FrontEndMenuManager.field_90 = 0;
        return;
    case 9:
        FrontEndMenuManager.field_B7 = true;
        FrontEndMenuManager.SwitchToNewScreen(38);
        FrontEndMenuManager.field_90 = 0;
        return;
    case 45:
        FrontEndMenuManager.field_1B14 = 1;
        FrontEndMenuManager.field_1B09 = 1;
        FrontEndMenuManager.field_1B08 = 1;
        FrontEndMenuManager.field_1B0C = FrontEndMenuManager.m_nSelectedMenuItem;
        FrontEndMenuManager.field_F0 = FrontEndMenuManager.field_36[2];
        return;
    case 53:
        FrontEndMenuManager.SwitchToNewScreen(43);
        return;
    case 55:
        FrontEndMenuManager.SwitchToNewScreen(-2);
        return;
    case 6:
        FrontEndMenuManager.m_bScanningUserTracks = 1;
        return;
    case 37:
        if (FrontEndMenuManager.m_nLanguage != 0)
        {
            FrontEndMenuManager.m_nLanguage = 0;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 38:
        if (FrontEndMenuManager.m_nLanguage != 1)
        {
            FrontEndMenuManager.m_nLanguage = 1;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 39:
        if (FrontEndMenuManager.m_nLanguage != 2)
        {
            FrontEndMenuManager.m_nLanguage = 2;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 40:
        if (FrontEndMenuManager.m_nLanguage != 3)
        {
            FrontEndMenuManager.m_nLanguage = 3;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
    case 41:
        if (FrontEndMenuManager.m_nLanguage != 4)
        {
            FrontEndMenuManager.m_nLanguage = 4;
            FrontEndMenuManager.field_EB = true;
            FrontEndMenuManager.InitialiseChangedLanguageSettings(false);
            FrontEndMenuManager.SaveSettings();
        }
        return;
        // Net
    case 100:
        return;
    }
}

void MobileFrontEnd::PrintRadioStationList() {
    signed int v2 = 1;
    int savedAlpha;
    float fPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(282.5f / 2);
    float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-270.0f / 2);
    float spacing = SCREEN_COORD(0.5f);
    float size = SCREEN_MULTIPLIER(58.125f);

    do {
        if (FrontEndMenuManager.m_nRadioStation == v2) {
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
            CSprite2d::DrawRect(CRect((fPosX - SCREEN_COORD(2.0f)) + (spacing), fPosY - SCREEN_COORD(2.0f), (fPosX - SCREEN_COORD(2.0f)) + (spacing) + (size + SCREEN_COORD(4.0f)), fPosY - SCREEN_COORD(2.0f) + (size + SCREEN_COORD(4.0f))), CRGBA(255, 255, 255, 100));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
        }

        FrontEndMenuManager.m_apTextures[v2].Draw(CRect(fPosX + (spacing), fPosY, fPosX + (spacing) + (size), fPosY + (size)), CRGBA(255, 255, 255, FrontEndMenuManager.m_nRadioStation == v2 ? 255 : 50));

        if (FrontEndMenuManager.m_nRadioStation == v2) {
            RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));
            CSprite2d::DrawRect(CRect((fPosX - SCREEN_COORD(2.0f)) + (spacing), fPosY - SCREEN_COORD(2.0f), (fPosX - SCREEN_COORD(2.0f)) + (spacing) + (size + SCREEN_COORD(4.0f)), fPosY - SCREEN_COORD(2.0f) + (size + SCREEN_COORD(4.0f))), 
                CRGBA(255, 255, 255, 50), CRGBA(255, 255, 255, 50),
                CRGBA(255, 255, 255, 0), CRGBA(255, 255, 255, 0));
            RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
        }

        ++v2;
        spacing += size;
    } while (v2 < 13);
}

void MobileFrontEnd::PrintMap() {
    int savedAlpha;
    RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

    // Background
    CSprite2d::DrawRect(CRect(0.0f, 0.0f, 0.0f + SCREEN_WIDTH, 0.0f + SCREEN_HEIGHT), CRGBA(0, 0, 0, 255));

    // PrintMap TODO: Draw our own map?!?
    FrontEndMenuManager.PrintMap();

    // Mask
    mobileTex.m_nBackgroundSprite.m_pTexture = mobileTex.m_nBackgroundSpriteTxd.GetTexture(MENU_MAINMASK);
    mobileTex.m_nBackgroundSprite.Draw(CRect(SCREEN_COORD(-600.0), SCREEN_COORD_BOTTOM(535.0f), SCREEN_COORD(-600.0) + SCREEN_WIDTH + SCREEN_COORD(600.0 * 2), SCREEN_COORD_BOTTOM(535.0f) + SCREEN_MULTIPLIER(535.0f)), CRGBA(255, 255, 255, 240));
    mobileTex.m_nBackgroundSprite.m_pTexture = nullptr;

    RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
}

void MobileFrontEnd::PrintLegend() {
    signed int v104 = 0;
    float fSpacingX = 0.0f;
    float fSpacingY = 0.0f;
    char *str;
    CFont::SetBackground(0, 0);
    CFont::SetProp(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetOutlinePosition(0);
    CFont::SetDropShadowPosition(1);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_BLUELIGHT, 255));
    CFont::SetAlignment(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_MENU);

   // if (FrontEndMenuManager.m_bMapLegend) {
        if (CRadar::MapLegendCounter) {
            do {
                switch (CRadar::MapLegendList[v104])
                {
                case 3:
                    str = TheText.Get("LG_01");
                    break;
                case 5:
                    str = TheText.Get("LG_02");
                    break;
                case 6:
                    str = TheText.Get("LG_03");
                    break;
                case 7:
                    str = TheText.Get("LG_04");
                    break;
                case 8:
                    str = TheText.Get("LG_05");
                    break;
                case 9:
                    str = TheText.Get("LG_06");
                    break;
                case 10:
                    str = TheText.Get("LG_07");
                    break;
                case 12:
                    str = TheText.Get("LG_09");
                    break;
                case 13:
                    str = TheText.Get("LG_10");
                    break;
                case 14:
                    str = TheText.Get("LG_11");
                    break;
                case 15:
                    str = TheText.Get("LG_12");
                    break;
                case 16:
                    str = TheText.Get("LG_13");
                    break;
                case 18:
                    str = TheText.Get("LG_15");
                    break;
                case 19:
                    str = TheText.Get("LG_16");
                    break;
                case 20:
                    str = TheText.Get("LG_17");
                    break;
                case 21:
                    str = TheText.Get("LG_18");
                    break;
                case 22:
                    str = TheText.Get("LG_19");
                    break;
                case 23:
                    str = TheText.Get("LG_20");
                    break;
                case 24:
                    str = TheText.Get("LG_21");
                    break;
                case 25:
                    str = TheText.Get("LG_22");
                    break;
                case 26:
                    str = TheText.Get("LG_23");
                    break;
                case 27:
                    str = TheText.Get("LG_24");
                    break;
                case 28:
                    str = TheText.Get("LG_25");
                    break;
                case 29:
                    str = TheText.Get("LG_26");
                    break;
                case 30:
                    str = TheText.Get("LG_27");
                    break;
                case 31:
                    str = TheText.Get("LG_28");
                    break;
                case 32:
                    str = TheText.Get("LG_29");
                    break;
                case 33:
                    str = TheText.Get("LG_30");
                    break;
                case 34:
                    str = TheText.Get("LG_31");
                    break;
                case 35:
                    str = TheText.Get("LG_32");
                    break;
                case 36:
                    str = TheText.Get("LG_33");
                    break;
                case 63:
                    str = TheText.Get("LG_34");
                    break;
                case 38:
                    str = TheText.Get("LG_35");
                    break;
                case 39:
                    str = TheText.Get("LG_36");
                    break;
                case 40:
                    str = TheText.Get("LG_37");
                    break;
                case 42:
                    str = TheText.Get("LG_39");
                    break;
                case 43:
                    str = TheText.Get("LG_40");
                    break;
                case 44:
                    str = TheText.Get("LG_41");
                    break;
                case 45:
                    str = TheText.Get("LG_42");
                    break;
                case 46:
                    str = TheText.Get("LG_43");
                    break;
                case 47:
                    str = TheText.Get("LG_44");
                    break;
                case 48:
                    str = TheText.Get("LG_45");
                    break;
                case 49:
                    str = TheText.Get("LG_46");
                    break;
                case 50:
                    str = TheText.Get("LG_47");
                    break;
                case 51:
                    str = TheText.Get("LG_48");
                    break;
                case 52:
                    str = TheText.Get("LG_51");
                    break;
                case 53:
                    str = TheText.Get("LG_52");
                    break;
                case 54:
                    str = TheText.Get("LG_53");
                    break;
                case 55:
                    str = TheText.Get("LG_57");
                    break;
                case 58:
                    str = TheText.Get("LG_58");
                    break;
                case 59:
                    str = TheText.Get("LG_59");
                    break;
                case 60:
                    str = TheText.Get("LG_60");
                    break;
                case 61:
                    str = TheText.Get("LG_61");
                    break;
                case 62:
                    str = TheText.Get("LG_62");
                    break;
                case 37:
                    str = TheText.Get("LG_63");
                    break;
                case 41:
                    str = TheText.Get("LG_64");
                    break;
                case 11:
                    str = TheText.Get("LG_66");
                    break;
                case 17:
                    str = TheText.Get("LG_67");
                    break;
                case 57:
                    str = TheText.Get("LG_65");
                    break;
                case 4294967295:
                    str = TheText.Get("LG_49");
                    break;
                case 4294967294:
                    str = TheText.Get("LG_50");
                    break;
                case 4294967293:
                    str = TheText.Get("LG_54");
                    break;
                case 4294967292:
                    str = TheText.Get("LG_55");
                    break;
                case 4294967291:
                    str = TheText.Get("LG_56");
                    break;
                default:
                    str = TheText.Get("LG_00");
                    break;
                }

                CFont::SetScale(SCREEN_MULTIPLIER(0.4f), SCREEN_MULTIPLIER(1.0f));
                float width = CFont::GetStringWidth(str, true, false);
                if (width > SCREEN_MULTIPLIER(150.0f))
                    CFont::SetScale(SCREEN_MULTIPLIER(0.4f * SCREEN_MULTIPLIER(150.0f) / width), SCREEN_MULTIPLIER(1.0f));
                CFont::PrintString(SCREEN_COORD_LEFT(45.0f) + fSpacingX, SCREEN_COORD_BOTTOM(225.0f) + fSpacingY, str);
                CRadar::DrawLegend(SCREEN_COORD_LEFT(5.0f) + fSpacingX, SCREEN_COORD_BOTTOM(230.0f) + fSpacingY, CRadar::MapLegendList[v104]);

                if (v104 == 6) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else if (v104 == 13) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else if (v104 == 20) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else if (v104 == 27) {
                    fSpacingX += SCREEN_COORD(200.0f);
                    fSpacingY -= SCREEN_COORD(32.0f * 6);
                }
                else
                    fSpacingY += SCREEN_COORD(32.0f);

                ++v104;

            } while (v104 < CRadar::MapLegendCounter);
        }
   // }
}

void MobileFrontEnd::PrintPlaceName() {
    // Place 
    CFont::SetBackground(0, 0);
    CFont::SetProp(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetOutlinePosition(3);
    CFont::SetDropColor(CRGBA(0, 0, 0, 255));
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetAlignment(ALIGN_RIGHT);
    CFont::SetFontStyle(FONT_PRICEDOWN);
    CFont::SetScale(SCREEN_MULTIPLIER(0.8f), SCREEN_MULTIPLIER(1.8f));

    char *strc = GetForMap(FrontEndMenuManager.m_vMousePos.x, FrontEndMenuManager.m_vMousePos.y);
    CFont::PrintString(SCREEN_COORD_RIGHT(30.0f), SCREEN_COORD_BOTTOM(120.0f), strc);
}

void MobileFrontEnd::DisplaySlider(float x, float y, float width, float height, float progress, bool bNub) {
    // empty
    mobileTex.m_menuSlider.m_pTexture = mobileTex.m_menuSliderTxd.GetTexture(MENU_SLIDER_EMPTY);
    mobileTex.m_menuSlider.Draw(CRect(x, y, x + width, y + height), CRGBA(255, 255, 255, 255));
    // full
    mobileTex.m_menuSlider.m_pTexture = mobileTex.m_menuSliderTxd.GetTexture(MENU_SLIDER_FULL);
    mobileTex.m_menuSlider.Draw(CRect(x, y, x + width * progress, y + height), CRGBA(255, 255, 255, 255),
        0.0f, 1.0f, progress, 1.0f, 0.0f, 0.0f, progress, 0.0f);

    // percentage
    static char text[4];
    static float percentage;
    percentage = progress * 100.0f;
    sprintf(text, "%d%%", static_cast<int>(percentage));

    CFont::SetWrapx(SCREEN_WIDTH);
    CFont::SetRightJustifyWrap(0.0f);
    CFont::SetOutlinePosition(0);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetScale(height * 0.020f, height * 0.038f);

    if (percentage > 80.0f) {
        CFont::SetAlignment(ALIGN_LEFT);
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_BLACK, 200));
        CFont::PrintString(x + SCREEN_COORD(12.0f), y + SCREEN_COORD(3.5f), text);
    }
    if (percentage < 80.0) {
        CFont::SetAlignment(ALIGN_RIGHT);
        CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
        CFont::PrintString(x + width - SCREEN_COORD(12.0f), y + SCREEN_COORD(3.5f), text);
    }

    // nub
    mobileTex.m_menuSlider.m_pTexture = mobileTex.m_menuSliderTxd.GetTexture(MENU_SLIDER_NUB);

    if (bNub)
        mobileTex.m_menuSlider.Draw((x)+(width - SCREEN_COORD(29.0f)) * (progress), (y), height * 1.0f, height * 1.0f, CRGBA(255, 255, 255, 255));
 
    mobileTex.m_menuSlider.m_pTexture = nullptr;
}


void MobileFrontEnd::PrintStats() {
    FrontEndMenuManager.PrintStats();

    char *Rate = CStats::FindCriminalRatingString();
    static char Value[6];

    // Player Rating 
    CFont::SetBackground(0, 0);
    CFont::SetProp(1);
    CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
    CFont::SetOutlinePosition(0);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetAlignment(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_PRICEDOWN);
    CFont::SetScale(SCREEN_MULTIPLIER(0.8f), SCREEN_MULTIPLIER(1.5f));

    sprintf(gString, "%d", CStats::FindCriminalRatingNumber());
    AsciiToGxtChar(gString, Value);

    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_BOTTOM(60.0f), Rate);
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1075.0f / 2) + CFont::GetStringWidth(Rate, true, false), SCREEN_COORD_BOTTOM(60.0f), Value);
}

void MobileFrontEnd::PrintStatsText(float x, float y, char *str) {
    CFont::SetAlignment(ALIGN_LEFT);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetOutlinePosition(2);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(450.0f / 2), y, str);
}

void MobileFrontEnd::PrintStatsText2(float x, float y, char *str) {
    CFont::SetAlignment(ALIGN_RIGHT);
    CFont::SetFontStyle(FONT_SUBTITLES);
    CFont::SetOutlinePosition(2);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(-1113.0f / 2), y - SCREEN_COORD(35.0f), str);
}

void MobileFrontEnd::DrawStatsSlider(float x, float y, unsigned short width, unsigned char height, float percentage, signed char,
    unsigned char, unsigned char, CRGBA, CRGBA) {
    CVector2D vecPosition;
    CVector2D vecScale;
    vecPosition.x = 285.0f;
    vecPosition.y = 0.0f;
    vecScale.x = 265.0f;
    vecScale.y = 28.5f;

    DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), y - SCREEN_COORD(28.0f), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), percentage / 100, false);
}

void MobileFrontEnd::PrintBriefsText(float x, float y, char *str) {
    CFont::SetOutlinePosition(2);
    CFont::SetColor(HudColour.GetRGB(HUD_COLOUR_WHITE, 255));
    CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
    CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), y, str);
}


void MobileFrontEnd::TestMenuStandard(unsigned char m_nCurrentMenuPage) {
	CFont::SetBackground(0, 0);
	CFont::SetProp(1);
	CFont::SetWrapx(SCREEN_COORD_MAX_X - 12.5f);
	CFont::SetOutlinePosition(2);
	CFont::SetRightJustifyWrap(12.5f);
	CFont::SetCentreSize(SCREEN_COORD_MAX_X);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));

	// Header
	if (MenuPages[m_nCurrentMenuPage].m_szTitleName[0]) {
		if (m_nCurrentMenuPage != 5 || !FrontEndMenuManager.field_78) {
			CFont::SetAlignment(ALIGN_LEFT);
			CFont::SetFontStyle(FONT_GOTHIC);
			CFont::SetScale(SCREEN_MULTIPLIER(1.8f), SCREEN_MULTIPLIER(3.6f));
			CFont::SetOutlinePosition(2);
			CFont::SetColor(CRGBA(255, 255, 255, 255));
			CFont::SetDropColor(CRGBA(0, 0, 0, 255));
			if (m_nCurrentMenuPage != 0)
				CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[m_nCurrentMenuPage].m_szTitleName));
			else
				CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(794.0f / 2), TheText.Get(MenuPages[m_nCurrentMenuPage].m_szTitleName));
		}
	}

	// Actions
	if (MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_nActionType == 1)
	{
		static char* pText;
		CFont::SetFontStyle(FONT_SUBTITLES);
		CFont::SetAlignment(ALIGN_LEFT);
		CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));
		CFont::SetOutlinePosition(2);
		CFont::SetColor(CRGBA(255, 255, 255, 255));
		CFont::SetDropColor(CRGBA(0, 0, 0, 255));

		switch (m_nCurrentMenuPage)
		{
		case 6:
		{
			pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FESZ_QQ" : MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		}
		case 35:
		{
			pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FEQ_SRW" : MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		}
		case 17:
		{
			switch (FrontEndMobileMenuManager.SlotValidation[FrontEndMenuManager.m_bSelectedSaveGame + 1]) {
			case 0:
				pText = TheText.Get("FESZ_QO");
				break;
			case 2:
				pText = TheText.Get("FESZ_QC");
				break;
			default:
				pText = TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
				break;
			}
			break;
		}
		case 11:
		{
			pText = TheText.Get(FrontEndMenuManager.m_bMainMenuSwitch ? "FES_LCG" : MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		}
		default:
		{
			pText = TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[0].m_szName);
			break;
		}
		}
		CFont::PrintString(SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2), SCREEN_COORD_CENTER_Y - SCREEN_COORD(640.0f / 2), pText);
	}

	for (unsigned int i = 0; i < 12; i++) {
		CFont::SetFontStyle(FONT_MENU);
		CFont::SetOutlinePosition(2);

		if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nActionType != 1 && MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_szName[0]) {
			const char* LeftColumn = nullptr;
			const char* RightColumn = nullptr;
			char ReservedSpace[64];

			if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType >= MENU_ENTRY_SAVE_1 && MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType <= MENU_ENTRY_SAVE_8) {
				switch (FrontEndMobileMenuManager.SlotValidation[i]) {
				case 0:
					LeftColumn = plugin::CallAndReturn<const char*, 0x5D0F40>(i - 1);
					break;
				case 2:
					LeftColumn = TheText.Get("FESZ_CS");
					break;
				}

				if (!LeftColumn || !LeftColumn[0]) {
					sprintf(gString, "FEM_SL%X", i);
					LeftColumn = TheText.Get(gString);

				}
			}

			else if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_MISSIONPACK) {
			}

			else if (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nType == MENU_ENTRY_JOYMOUSE) {
				LeftColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FEJ_TIT" : "FEC_MOU");
			}

			else {
				LeftColumn = TheText.Get(MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_szName);
			}

			CAERadioTrackManager RadioEntity;

			switch (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nActionType) {
			case 30:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bRadioEq ? "FEM_ON" : "FEM_OFF");
				break;
			case 31:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bRadioAutoSelect ? "FEM_ON" : "FEM_OFF");
				break;
			case 32:
				RightColumn = RadioEntity.GetRadioStationName(FrontEndMenuManager.m_nRadioStation);
				break;
			case 33:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bMapLegend ? "FEM_ON" : "FEM_OFF");
				break;
			case 25:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bShowSubtitles ? "FEM_ON" : "FEM_OFF");
				break;
			case 26:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bWidescreenOn ? "FEM_ON" : "FEM_OFF");
				break;
			case 34:
				switch (FrontEndMenuManager.m_nRadarMode) {
				case 0:
					RightColumn = TheText.Get("FED_RDM");
					break;
				case 1:
					RightColumn = TheText.Get("FED_RDB");
					break;
				case 2:
					RightColumn = TheText.Get("FEM_OFF");
					break;
				}
				break;
			case 35:
				switch (FrontEndMenuManager.m_bHudOn) {
				case 0:
					RightColumn = TheText.Get("FEM_OFF");
					FrontEndMenuManager.m_nRadarMode = 2;
					break;
				case 1:
					RightColumn = TheText.Get("FEM_ON");
					FrontEndMenuManager.m_nRadarMode = 0;
					break;
				}
				break;
			case 65:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bSavePhotos ? "FEM_ON" : "FEM_OFF");
				break;
			case 63:
				switch (FrontEndMenuManager.m_nRadioMode) {
				case 0:
					RightColumn = TheText.Get("FEA_PR1");
					break;
				case 1:
					RightColumn = TheText.Get("FEA_PR2");
					break;
				case 2:
					RightColumn = TheText.Get("FEA_PR3");
					break;
				}
				break;
			case 24:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bFrameLimiterOn ? "FEM_ON" : "FEM_OFF");
				break;
			case 43:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bMipMapping ? "FEM_ON" : "FEM_OFF");
				break;
			case 64:
				RightColumn = TheText.Get(FrontEndMenuManager.m_bTracksAutoScan ? "FEM_ON" : "FEM_OFF");
				break;
			case 46:
				RightColumn = TheText.Get(!FrontEndMenuManager.bInvertMouseY ? "FEM_ON" : "FEM_OFF");
				break;
			case 47:
				RightColumn = TheText.Get(FrontEndMenuManager.invertPadX1 ? "FEM_ON" : "FEM_OFF");
				break;
			case 48:
				RightColumn = TheText.Get(FrontEndMenuManager.invertPadY1 ? "FEM_ON" : "FEM_OFF");
				break;
			case 49:
				RightColumn = TheText.Get(FrontEndMenuManager.invertPadX2 ? "FEM_ON" : "FEM_OFF");
				break;
			case 50:
				RightColumn = TheText.Get(FrontEndMenuManager.invertPadY2 ? "FEM_ON" : "FEM_OFF");
				break;
			case 51:
				RightColumn = TheText.Get(FrontEndMenuManager.swapPadAxis1 ? "FEM_ON" : "FEM_OFF");
				break;
			case 52:
				RightColumn = TheText.Get(FrontEndMenuManager.swapPadAxis2 ? "FEM_ON" : "FEM_OFF");
				break;
			case 59:
				RightColumn = TheText.Get(CVehicle::m_bEnableMouseSteering ? "FEM_ON" : "FEM_OFF");
				break;
			case 60:
				RightColumn = TheText.Get(CVehicle::m_bEnableMouseFlying ? "FEM_ON" : "FEM_OFF");
				break;
			case 56:
			{
				const char* pszResolution = ((const char**(*)())0x745AF0)()[FrontEndMenuManager.m_nResolution];

				if (!pszResolution)
					pszResolution = "";

				strncpy(ReservedSpace, pszResolution, sizeof(ReservedSpace));
				RightColumn = ReservedSpace;
			}
			break;
			case 44:
				if (FrontEndMenuManager.m_nAntiAliasingLevel <= 1)
					RightColumn = TheText.Get("FEM_OFF");
				else {
					switch (FrontEndMenuManager.m_nAntiAliasingLevel)
					{
					case 2:
						RightColumn = "2x";
						break;
					case 3:
						RightColumn = "4x";
						break;
					case 4:
						RightColumn = "8x";
						break;
					}
				}
				break;
			case 42:
				switch (g_fx.GetFxQuality()) {
				case FXQUALITY_LOW:
					RightColumn = TheText.Get("FED_FXL");
					break;
				case FXQUALITY_MEDIUM:
					RightColumn = TheText.Get("FED_FXM");
					break;
				case FXQUALITY_HIGH:
					RightColumn = TheText.Get("FED_FXH");
					break;
				case FXQUALITY_VERY_HIGH:
					RightColumn = TheText.Get("FED_FXV");
					break;
				}
				break;
			case 58:
				RightColumn = TheText.Get(FrontEndMenuManager.m_nController ? "FET_CCN" : "FET_SCN");
				break;
			}

			unsigned int savedAlpha;
			float f_leftPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(282.0f / 2);
			float fPosnXForStats = SCREEN_COORD_CENTER_X - SCREEN_COORD(1113.0f / 2);
			float f_rightPosX = SCREEN_COORD_CENTER_X - SCREEN_COORD(-1113.0f / 2);
			float fPosY = SCREEN_COORD_CENTER_Y - SCREEN_COORD(-MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nPosnY) + (0.0f / 2);

			if (i == FrontEndMenuManager.m_nSelectedMenuItem) {
				if (m_nCurrentMenuPage != 5) {
					RwRenderStateGet(rwRENDERSTATEVERTEXALPHAENABLE, &savedAlpha);
					RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(TRUE));

					if (m_nCurrentMenuPage == 0)
						CSprite2d::DrawRect(CRect(fPosnXForStats - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (fPosnXForStats - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(330.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));
					else
						CSprite2d::DrawRect(CRect(f_leftPosX - SCREEN_COORD(25.0f / 2), fPosY - SCREEN_COORD(12.5f / 2), (f_leftPosX - SCREEN_COORD(25.0f / 2)) + SCREEN_MULTIPLIER(725.0f), (fPosY - SCREEN_COORD(12.5f / 2)) + SCREEN_MULTIPLIER(50.0f)), CRGBA(255, 255, 255, 50));

					RwRenderStateSet(rwRENDERSTATEVERTEXALPHAENABLE, reinterpret_cast<void *>(savedAlpha));
				}
			}

			CFont::SetScale(SCREEN_MULTIPLIER(0.9f), SCREEN_MULTIPLIER(1.7f));

			if (m_nCurrentMenuPage == 7 || m_nCurrentMenuPage == 9 || m_nCurrentMenuPage == 10 || m_nCurrentMenuPage == 16) {
				float width = CFont::GetStringWidth((char*)LeftColumn, true, false);

				if (width > SCREEN_COORD(690.0f))
					CFont::SetScale(SCREEN_MULTIPLIER(0.9f * SCREEN_COORD(690.0f) / width), SCREEN_MULTIPLIER(1.7f));
			}

			// Print left column
			CFont::SetDropColor(CRGBA(0, 0, 0, 255));
			CFont::SetColor(CRGBA(255, 255, 255, 255));
			CFont::SetAlignment(ALIGN_LEFT);

			if (m_nCurrentMenuPage == 0)
				CFont::PrintString(fPosnXForStats, fPosY, (char*)LeftColumn);
			else
				CFont::PrintString(f_leftPosX, fPosY, (char*)LeftColumn);


			// Print right column
			if (RightColumn) {
				float width = CFont::GetStringWidth((char*)RightColumn, true, false);

				if (width > SCREEN_COORD(312.0f))
					CFont::SetScale(SCREEN_MULTIPLIER(0.8f * SCREEN_COORD(312.0f) / width), SCREEN_MULTIPLIER(1.7f));

				CFont::SetAlignment(ALIGN_RIGHT);
				CFont::PrintString(f_rightPosX, fPosY, (char*)RightColumn);
			}

			// Sliders
			CVector2D vecPosition;
			CVector2D vecScale;
			vecPosition.x = 285.0f;
			vecPosition.y = MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nPosnY + 2.0f;
			vecScale.x = 265.0f;
			vecScale.y = 28.5f;

			switch (MenuPages[m_nCurrentMenuPage].m_aButtons[i].m_nActionType)
			{
			case 27:
			{
				// Brightness
				DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nBrightness * 0.0026041667f, true);
				break;
			}
			case 28:
			{
				// Radio Volume
				DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nRadioVolume * 0.015625f, true);
				break;
			}
			case 29:
			{
				// SFX Volume
				DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), FrontEndMenuManager.m_nSfxVolume * 0.015625f, true);
				break;
			}
			case 61:
			{
				// Draw Distance
				DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), (FrontEndMenuManager.m_fDrawDistance - 0.925f) * 1.1428572f, true);
				break;
			}
			case 62:
			{
				// Mouse Sensitivity
				DisplaySlider(SCREEN_COORD_CENTER_X - SCREEN_COORD(-vecPosition.x), SCREEN_COORD_CENTER_Y - SCREEN_COORD(-vecPosition.y), SCREEN_MULTIPLIER(vecScale.x), SCREEN_MULTIPLIER(vecScale.y), (CCamera::m_fMouseAccelHorzntl / 0.005f), true);
				break;
			}
			}
		}
	}
}