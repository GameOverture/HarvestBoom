#pragma once
#include "pch.h"
#include "HousePanel.h"

#define WORLD_WIDTH 25
#define WORLD_HEIGHT 25

class Tile;
class Player;
class Stamina;
class HousePanel;

class World : public HyEntity2d
{
	Tile *			m_pTileGrid[WORLD_WIDTH][WORLD_HEIGHT];
	uint32			m_uiSetRowCurrentIndex;

	HyPrimitive2d	m_DebugCollidePt1;
	HyPrimitive2d	m_DebugCollidePt2;
	HyPrimitive2d	m_DebugCollideNormal;

public:
	World(HyEntity2d *pParent);
	virtual ~World();

	void SetupNewDay();

	void CleanupTiles();
	void UpdatePlayer(Player &playerRef, Stamina &staminaRef, HousePanel &housePanelRef);

private:
	void SetRow(std::string sRow);
};

