#pragma once

#include <plugin.h>
#include "Settings.h"
#include "Utility.h"

#include "CVector2D.h"
#include "CSprite2d.h"
#include "common.h"
#include "CMenuManager.h"
#include "CPad.h"

class Radar {
public:
	static void InstallPatches();
	static void MyTransformRadarPointToScreenSpace(CVector2D *out, CVector2D *in);
	static void __fastcall MyDrawRadarCircle(CSprite2d *sprite, int, CRect const &rect, CRGBA const &color);
	static void __fastcall MyDrawRadarPlane(CSprite2d *sprite, int, float x1, float y1, float x2, float y2, float x3, float y3, float x4,
		float y4, CRGBA const &color);
	static void MyDrawPlaneHeightBorder(CRect const& rect, CRGBA const& color);
	static void MyDrawPlaneHeight(CRect const& rect, CRGBA const& color);
	static void DrawRadarRectangle(CSprite2d *sprite, CRect const& rect, CRGBA const& color);
};

void Radar::InstallPatches() {
	plugin::patch::RedirectCall(0x58AA25, MyDrawRadarCircle);
	//plugin::patch::RedirectCall(0x58A551, MyDrawRadarPlane);
	//plugin::patch::RedirectCall(0x58A649, MyDrawPlaneHeightBorder);
	//plugin::patch::RedirectCall(0x58A77A, MyDrawPlaneHeight);
	plugin::patch::RedirectJump(0x583480, MyTransformRadarPointToScreenSpace);
	plugin::patch::Nop(0x58A818, 16);
	plugin::patch::Nop(0x58A8C2, 16);
	plugin::patch::Nop(0x58A96C, 16);
}

void Radar::DrawRadarRectangle(CSprite2d *sprite, CRect const& rect, CRGBA const& color) {
	if (sprite) {
		sprite->Draw(CRect(rect.left, SCREEN_HEIGHT - rect.top, rect.right, SCREEN_HEIGHT - rect.bottom), color);
	}
	else {
		CSprite2d::DrawRect(CRect(rect.left, SCREEN_HEIGHT - rect.top, rect.right, SCREEN_HEIGHT - rect.bottom), color);
	}
}

void __fastcall Radar::MyDrawRadarCircle(CSprite2d *sprite, int, CRect const &rect, CRGBA const &color)
{
	CPed *player = FindPlayerPed(-1);
	CPad *pad = CPad::GetPad(0);
	DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.RADAR_X - settings.RADAR_SIZE_X), SCREEN_COORD(settings.RADAR_Y - settings.RADAR_SIZE_Y),
		SCREEN_COORD(settings.RADAR_X), SCREEN_COORD(settings.RADAR_Y)), CRGBA(255, 255, 255, 255));
	DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.RADAR_X + settings.RADAR_SIZE_X), SCREEN_COORD(settings.RADAR_Y - settings.RADAR_SIZE_Y),
		SCREEN_COORD(settings.RADAR_X), SCREEN_COORD(settings.RADAR_Y)), CRGBA(255, 255, 255, 255));
	DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.RADAR_X - settings.RADAR_SIZE_X), SCREEN_COORD(settings.RADAR_Y + settings.RADAR_SIZE_Y),
		SCREEN_COORD(settings.RADAR_X), SCREEN_COORD(settings.RADAR_Y)), CRGBA(255, 255, 255, 255));
	DrawRadarRectangle(sprite, CRect(SCREEN_COORD(settings.RADAR_X + settings.RADAR_SIZE_X), SCREEN_COORD(settings.RADAR_Y + settings.RADAR_SIZE_Y),
		SCREEN_COORD(settings.RADAR_X), SCREEN_COORD(settings.RADAR_Y)), CRGBA(255, 255, 255, 255));
}

void Radar::MyTransformRadarPointToScreenSpace(CVector2D *out, CVector2D *in) {
	CPed *player = FindPlayerPed(-1);
	CPad *pad = CPad::GetPad(0);
	__asm push edx

	if (FrontEndMenuManager.drawRadarOrMap) {
		out->x = FrontEndMenuManager.m_fMapZoom * in->x + FrontEndMenuManager.m_fMapBaseX;
		out->y = FrontEndMenuManager.m_fMapBaseY - FrontEndMenuManager.m_fMapZoom * in->y;
	}
	else {
		if (!pad->GetDisplayVitalStats(player) || FindPlayerVehicle(-1, 0))
			out->x = SCREEN_COORD(settings.RADAR_X) + in->x * SCREEN_COORD(settings.RADAR_SIZE_X)*0.98f;
		else
			out->x = SCREEN_COORD(settings.RADAR_X + 270.0f) + in->x * SCREEN_COORD(settings.RADAR_SIZE_X)*0.98f;
		out->y = SCREEN_COORD_MAX_Y - SCREEN_COORD(settings.RADAR_Y) - in->y * SCREEN_COORD(settings.RADAR_SIZE_Y)*0.98f;
	}

	__asm pop edx
}

/*static void __fastcall Radar::MyDrawRadarPlane(CSprite2d *sprite, int, float x1, float y1, float x2, float y2, float x3,
	float y3, float x4, float y4, CRGBA const &color)
{
	CVector2D posn[4];
	posn[0].x = SCREEN_COORD(RADAR_X) - SCREEN_COORD(RADAR_SIZE_X);
	posn[0].y = SCREEN_COORD(RADAR_Y) + SCREEN_COORD(RADAR_SIZE_Y);
	posn[1].x = SCREEN_COORD(RADAR_X) + SCREEN_COORD(RADAR_SIZE_X);
	posn[1].y = SCREEN_COORD(RADAR_Y) + SCREEN_COORD(RADAR_SIZE_Y);
	posn[2].x = SCREEN_COORD(RADAR_X) - SCREEN_COORD(RADAR_SIZE_X);
	posn[2].y = SCREEN_COORD(RADAR_Y) - SCREEN_COORD(RADAR_SIZE_Y);
	posn[3].x = SCREEN_COORD(RADAR_X) + SCREEN_COORD(RADAR_SIZE_X);
	posn[3].y = SCREEN_COORD(RADAR_Y) - SCREEN_COORD(RADAR_SIZE_Y);
	CMatrix *planeMat = FindPlayerVehicle(-1, false)->m_matrix;
	float angle = atan2f(planeMat->at.z, -planeMat->right.z) - 1.57079632679f;
	RotateVertices(posn, 4, SCREEN_COORD(RADAR_X), SCREEN_COORD(RADAR_Y), -angle);
	sprite->Draw(posn[2].x, SCREEN_COORD_MAX_Y - posn[2].y - SCREEN_COORD(1.0f),
		posn[3].x, SCREEN_COORD_MAX_Y - posn[3].y - SCREEN_COORD(1.0f),
		posn[0].x, SCREEN_COORD_MAX_Y - posn[0].y - SCREEN_COORD(1.0f),
		posn[1].x, SCREEN_COORD_MAX_Y - posn[1].y - SCREEN_COORD(1.0f),
		CRGBA(255, 255, 255, 255));
}

static void Radar::MyDrawPlaneHeightBorder(CRect const& rect, CRGBA const& color) {
	float settings_vecPlaneRadarPosn_x = 0.0f, settings_vecPlaneRadarPosn_y = 67.0f;
	float settings_vecPlaneRadarSize_x = 14.0f, settings_vecPlaneRadarSize_y = 145.0f;
	float settings_vecPlaneRadarLightPartPosn_x = 225.0f, settings_vecPlaneRadarLightPartPosn_y = 70.0f;
	float settings_vecPlaneRadarLightPartSize_x = 8.0f, settings_vecPlaneRadarLightPartSize_y = 139.0f;
	CPed *player = FindPlayerPed();
	CPad *pad = CPad::GetPad(0);
	if (!pad->GetDisplayVitalStats(player) || FindPlayerVehicle(-1, 0)) {
		DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_x)), BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_y)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_x) + SCREEN_COORD(settings_vecPlaneRadarSize_x)), BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_y)
				+ SCREEN_COORD(settings_vecPlaneRadarSize_y))), CRGBA(0, 0, 0, 255));
		DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_x)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_y)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_x) + SCREEN_COORD(settings_vecPlaneRadarLightPartSize_x)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_y) + SCREEN_COORD(settings_vecPlaneRadarLightPartSize_y))), CRGBA(120, 120, 120, 255));
	}
	else {
		DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_x + 270.0f)), BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_y)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_x + 270.0f) + SCREEN_COORD(settings_vecPlaneRadarSize_x)), BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarPosn_y)
				+ SCREEN_COORD(settings_vecPlaneRadarSize_y))), CRGBA(0, 0, 0, 255));
		DrawRadarRectangle(NULL, CRect(BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_x + 270.0f)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_y)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_x + 270.0f) + SCREEN_COORD(settings_vecPlaneRadarLightPartSize_x)),
			BilinearOffset(SCREEN_COORD(settings_vecPlaneRadarLightPartPosn_y) + SCREEN_COORD(settings_vecPlaneRadarLightPartSize_y))), CRGBA(120, 120, 120, 255));
	}
}

void Radar::MyDrawPlaneHeight(CRect const& rect, CRGBA const& color) {
	float playerHeight = 0.0f;
	float blackLineBaseY = 0.0f;
	CPed *playa = FindPlayerPed();
	CPad *pad = CPad::GetPad(0);
	CVehicle *playaVeh = FindPlayerVehicle(-1, false);
	if (playaVeh)
		playerHeight = playaVeh->GetPosition().z;
	else if (playa)
		playerHeight = playa->GetPosition().z;
	if (playerHeight < 0.0f)
		playerHeight = 0.0f;
	else
		playerHeight /= 900.0f;
	if (playerHeight > 1.0f)
		playerHeight = 1.0f;
	if (playerHeight > 0.0f) {
		if (!pad->GetDisplayVitalStats(playa) || FindPlayerVehicle(-1, 0)) {
			CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x)),
				BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) -
					SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight),
				BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
				BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y))), CRGBA(255, 255, 255, 255));
		}
		else {
			CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x + 270.0f)),
				BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) -
					SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight),
				BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.x + 270.0f) + SCREEN_COORD(settings.vecPlaneRadarLightPartSize.x)),
				BilinearOffset(SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y))), CRGBA(255, 255, 255, 255));
		}
	}
	if (!pad->GetDisplayVitalStats(playa) || FindPlayerVehicle(-1, 0)) {
		blackLineBaseY = playerHeight * (settings.vecPlaneRadarLightPartSize.y) > 4.0f ?
			SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight :
			SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(4.0f);
		CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) - SCREEN_COORD(3.0f)),
			BilinearOffset(blackLineBaseY), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x) + SCREEN_COORD(settings.vecPlaneRadarSize.x) + SCREEN_COORD(3.0f)),
			BilinearOffset(blackLineBaseY + SCREEN_COORD(4.0f))), CRGBA(0, 0, 0, 255));
	}
	else {
		blackLineBaseY = playerHeight * (settings.vecPlaneRadarLightPartSize.y) > 4.0f ?
			SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(settings.vecPlaneRadarLightPartSize.y) * playerHeight :
			SCREEN_COORD_MAX_Y + 1.0f - SCREEN_COORD(settings.vecPlaneRadarLightPartPosn.y) - SCREEN_COORD(4.0f);
		CSprite2d::DrawRect(CRect(BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x + 270.0f) - SCREEN_COORD(3.0f)),
			BilinearOffset(blackLineBaseY), BilinearOffset(SCREEN_COORD(settings.vecPlaneRadarPosn.x + 270.0f) + SCREEN_COORD(settings.vecPlaneRadarSize.x) + SCREEN_COORD(3.0f)),
			BilinearOffset(blackLineBaseY + SCREEN_COORD(4.0f))), CRGBA(0, 0, 0, 255));
	}
}
*/