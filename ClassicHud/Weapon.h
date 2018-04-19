#pragma once
#include <plugin.h>
#include "Settings.h"

#include "CFont.h"
#include "CTxdStore.h"
#include "CStats.h"
#include "CSprite2d.h"

static CSprite2d weaponicons[50];
static CSprite2d sprite;

class Weapon {
public:
	static void InstallPatches();
	static void DrawWeaponAmmo(float x, float y, char *string);
	static void WeaponTextures();
	static void WeaponTexturesShutdown();
	static void PrintIcon();
	static void DrawWeaponIcon(CPed *player);
};

void Weapon::InstallPatches() {
	plugin::patch::RedirectJump(0x58D7D0, DrawWeaponIcon);
	plugin::patch::RedirectCall(0x58962A, DrawWeaponAmmo);
}

void Weapon::DrawWeaponAmmo(float x, float y, char *string) {
	CFont::SetBackground(0, 0);
	CFont::SetDropShadowPosition(settings.AMMO_SHADOW);
	if (settings.AMMO_OUTLINE != 0)
		CFont::SetOutlinePosition(settings.AMMO_OUTLINE);
	CFont::SetDropColor(CRGBA(0, 0, 0, 255));
	CFont::SetColor(CRGBA(settings.AMMO_R, settings.AMMO_G, settings.AMMO_B, 255));
	CFont::SetScale(SCREEN_MULTIPLIER(settings.AMMO_SIZE_X), SCREEN_MULTIPLIER(settings.AMMO_SIZE_Y));
	CFont::PrintString(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.AMMO_X),
		SCREEN_COORD(settings.AMMO_Y), string);
}

void Weapon::WeaponTextures() {
	int v1 = CTxdStore::AddTxdSlot("weapons");
	CTxdStore::LoadTxd(v1, settings.WEAPONS_TXD);
	CTxdStore::AddRef(v1);
	CTxdStore::PushCurrentTxd();
	CTxdStore::SetCurrentTxd(v1);
	weaponicons[0].SetTexture("UNARMED");
	weaponicons[1].SetTexture("GUN_DILDO1");
	weaponicons[2].SetTexture("GUN_DILDO2");
	weaponicons[3].SetTexture("GUN_VIBE1");
	weaponicons[4].SetTexture("GUN_VIBE2");
	weaponicons[5].SetTexture("FLOWERA");
	weaponicons[6].SetTexture("GUN_CANE");
	weaponicons[7].SetTexture("GUN_BOXWEE");
	weaponicons[8].SetTexture("GUN_BOXBIG");
	weaponicons[9].SetTexture("CELLPHONE");
	weaponicons[10].SetTexture("BRASSKNUCKLE");
	weaponicons[11].SetTexture("GOLFCLUB");
	weaponicons[12].SetTexture("NITESTICK");
	weaponicons[13].SetTexture("KNIFECUR");
	weaponicons[14].SetTexture("BAT");
	weaponicons[15].SetTexture("SHOVEL");
	weaponicons[16].SetTexture("POOLCUE");
	weaponicons[17].SetTexture("KATANA");
	weaponicons[18].SetTexture("CHNSAW");
	weaponicons[19].SetTexture("GRENADE");
	weaponicons[20].SetTexture("TEARGAS");
	weaponicons[21].SetTexture("MOLOTOV");
	weaponicons[22].SetTexture("MISSILE");
	weaponicons[23].SetTexture("COLT45");
	weaponicons[24].SetTexture("SILENCED");
	weaponicons[25].SetTexture("DESERT_EAGLE");
	weaponicons[26].SetTexture("CHROMEGUN");
	weaponicons[27].SetTexture("SAWNOFF");
	weaponicons[28].SetTexture("SHOTGSPA");
	weaponicons[29].SetTexture("MICRO_UZI");
	weaponicons[30].SetTexture("MP5LNG");
	weaponicons[31].SetTexture("FLARE");
	weaponicons[32].SetTexture("AK47");
	weaponicons[33].SetTexture("M4");
	weaponicons[34].SetTexture("CUNTGUN");
	weaponicons[35].SetTexture("SNIPER");
	weaponicons[36].SetTexture("ROCKETLA");
	weaponicons[37].SetTexture("HEATSEEK");
	weaponicons[38].SetTexture("FLAME");
	weaponicons[39].SetTexture("MINIGUN");
	weaponicons[40].SetTexture("SATCHEL");
	weaponicons[41].SetTexture("DETONATOR");
	weaponicons[42].SetTexture("SPRAYCAN");
	weaponicons[43].SetTexture("FIRE_EX");
	weaponicons[44].SetTexture("CAMERA");
	weaponicons[45].SetTexture("GOGGLES");
	weaponicons[46].SetTexture("GOGGLES");
	weaponicons[47].SetTexture("JETPACK");
	weaponicons[48].SetTexture("GUN_PARA");
	weaponicons[49].SetTexture("TEC9");
	CTxdStore::PopCurrentTxd();
}

void Weapon::WeaponTexturesShutdown() {
	weaponicons[0].Delete();
	weaponicons[1].Delete();
	weaponicons[2].Delete();
	weaponicons[3].Delete();
	weaponicons[4].Delete();
	weaponicons[5].Delete();
	weaponicons[6].Delete();
	weaponicons[7].Delete();
	weaponicons[8].Delete();
	weaponicons[9].Delete();
	weaponicons[10].Delete();
	weaponicons[11].Delete();
	weaponicons[12].Delete();
	weaponicons[13].Delete();
	weaponicons[14].Delete();
	weaponicons[15].Delete();
	weaponicons[16].Delete();
	weaponicons[17].Delete();
	weaponicons[18].Delete();
	weaponicons[19].Delete();
	weaponicons[20].Delete();
	weaponicons[21].Delete();
	weaponicons[22].Delete();
	weaponicons[23].Delete();
	weaponicons[24].Delete();
	weaponicons[25].Delete();
	weaponicons[26].Delete();
	weaponicons[27].Delete();
	weaponicons[28].Delete();
	weaponicons[29].Delete();
	weaponicons[30].Delete();
	weaponicons[31].Delete();
	weaponicons[32].Delete();
	weaponicons[33].Delete();
	weaponicons[34].Delete();
	weaponicons[35].Delete();
	weaponicons[36].Delete();
	weaponicons[37].Delete();
	weaponicons[38].Delete();
	weaponicons[39].Delete();
	weaponicons[40].Delete();
	weaponicons[41].Delete();
	weaponicons[42].Delete();
	weaponicons[43].Delete();
	weaponicons[44].Delete();
	weaponicons[45].Delete();
	weaponicons[46].Delete();
	weaponicons[47].Delete();
	weaponicons[48].Delete();
	weaponicons[49].Delete();
	int v1 = CTxdStore::FindTxdSlot("weapons");
	CTxdStore::RemoveTxdSlot(v1);
}

void Weapon::PrintIcon() {
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZTESTENABLE, 0);
	sprite.Draw(
		RsGlobal.maximumWidth - SCREEN_COORD(settings.WEAPON_X),
		SCREEN_COORD(settings.WEAPON_Y),
		SCREEN_MULTIPLIER(settings.WEAPON_SIZE_X),
		SCREEN_MULTIPLIER(settings.WEAPON_SIZE_Y), CRGBA(255, 255, 255, settings.WEAPON_A));
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATEZWRITEENABLE, 0);
}

void Weapon::DrawWeaponIcon(CPed *player) {
	RwEngineInstance->dOpenDevice.fpRenderStateSet(rwRENDERSTATETEXTUREFILTER, (void *)rwFILTERLINEAR);
	int modelId = CWeaponInfo::GetWeaponInfo((eWeaponType)player->m_aWeapons[player->m_nActiveWeaponSlot].m_nType, 1)->m_nModelId1;
	if (modelId <= 0) {
		sprite = weaponicons[0];
		PrintIcon();
		settings.stat3_2 = CStats::GetStatValue(-1);
		settings.STAT_WEP_ALPHA = 50;
	}
	else {
		switch (modelId) {
		case MODEL_GUN_DILDO1:
			sprite = weaponicons[1];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_DILDO2:
			sprite = weaponicons[2];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_VIBE1:
			sprite = weaponicons[3];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_VIBE2:
			sprite = weaponicons[4];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_FLOWERA:
			sprite = weaponicons[5];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_CANE:
			sprite = weaponicons[6];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_BOXWEE:
			sprite = weaponicons[7];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_BOXBIG:
			sprite = weaponicons[8];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_CELLPHONE:
			sprite = weaponicons[9];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_BRASSKNUCKLE:
			sprite = weaponicons[10];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GOLFCLUB:
			sprite = weaponicons[11];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_NITESTICK:
			sprite = weaponicons[12];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_KNIFECUR:
			sprite = weaponicons[13];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_BAT:
			sprite = weaponicons[14];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_SHOVEL:
			sprite = weaponicons[15];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_POOLCUE:
			sprite = weaponicons[16];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_KATANA:
			sprite = weaponicons[17];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_CHNSAW:
			sprite = weaponicons[18];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GRENADE:
			sprite = weaponicons[19];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_TEARGAS:
			sprite = weaponicons[20];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_MOLOTOV:
			sprite = weaponicons[21];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_MISSILE:
			sprite = weaponicons[22];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_COLT45:
			sprite = weaponicons[23];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(69)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_SILENCED:
			sprite = weaponicons[24];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(70)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_DESERT_EAGLE:
			sprite = weaponicons[25];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(71)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_CHROMEGUN:
			sprite = weaponicons[26];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(72)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_SAWNOFF:
			sprite = weaponicons[27];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(73)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_SHOTGSPA:
			sprite = weaponicons[28];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(74)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_MICRO_UZI:
			sprite = weaponicons[29];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(75)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_MP5LNG:
			sprite = weaponicons[30];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(76)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_FLARE:
			sprite = weaponicons[31];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_AK47:
			sprite = weaponicons[32];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(77)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_M4:
			sprite = weaponicons[33];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(78)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_CUNTGUN:
			sprite = weaponicons[34];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_SNIPER:
			sprite = weaponicons[35];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(79)* 0.001f * 100.0f;
			settings.STAT_WEP_ALPHA = 255;
			break;
		case MODEL_ROCKETLA:
			sprite = weaponicons[36];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_HEATSEEK:
			sprite = weaponicons[37];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_FLAME:
			sprite = weaponicons[38];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_MINIGUN:
			sprite = weaponicons[39];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_SATCHEL:
			sprite = weaponicons[40];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_BOMB:
			sprite = weaponicons[41];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_SPRAYCAN:
			sprite = weaponicons[42];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_FIRE_EX:
			sprite = weaponicons[43];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_CAMERA:
			sprite = weaponicons[44];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_NVGOGGLES:
			sprite = weaponicons[45];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_IRGOGGLES:
			sprite = weaponicons[46];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_JETPACK:
			sprite = weaponicons[47];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_GUN_PARA:
			sprite = weaponicons[48];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		case MODEL_TEC9:
			sprite = weaponicons[49];
			PrintIcon();
			settings.stat3_2 = CStats::GetStatValue(-1);
			settings.STAT_WEP_ALPHA = 50;
			break;
		}
	}
}