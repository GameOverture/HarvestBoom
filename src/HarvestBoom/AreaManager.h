#pragma once
#include "pch.h"

#define AREA_WIDTH 25
#define AREA_HEIGHT 25

class Player;
class Tile;

class AreaManager : public HyEntity2d
{
	HyPrimitive2d	m_CollidePt1;
	HyPrimitive2d	m_CollidePt2;

	Tile *			m_pTileGrid[AREA_WIDTH][AREA_HEIGHT];
	uint32			m_uiSetRowCurrentIndex;

public:
	AreaManager(HyEntity2d *pParent);
	virtual ~AreaManager();

	void DeleteTiles();
	void ResetTiles();

	void ConstructLevel1();

	void UpdatePlayer(Player &playerRef);

private:
	void SetRow(std::string sRow);
};

