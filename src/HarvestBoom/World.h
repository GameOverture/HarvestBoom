#pragma once
#include "pch.h"
#include "HousePanel.h"

#define WORLD_WIDTH 25
#define WORLD_HEIGHT 25

class Player;
class Tile;

class World : public HyEntity2d
{
	HyPrimitive2d	m_CollidePt1;
	HyPrimitive2d	m_CollidePt2;
	HyPrimitive2d	m_CollideNormal;

	Tile *			m_pTileGrid[WORLD_WIDTH][WORLD_HEIGHT];
	uint32			m_uiSetRowCurrentIndex;

	HousePanel *	m_pHousePanel;

public:
	World(HyEntity2d *pParent);
	virtual ~World();

	void DeleteTiles();
	void Construct();

	void SetAsLevel1();

	void UpdatePlayer(Player &playerRef);

private:
	void SetRow(std::string sRow);
};

