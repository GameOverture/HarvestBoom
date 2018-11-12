#pragma once

#include "pch.h"

class Tile : public HyEntity2d
{
protected:
	TileType			m_eTileType;

	HyPrimitive2d		m_Ground;
	HySprite2d *		m_pTexture;

	Tile *				m_pNeighborNorth;
	Tile *				m_pNeighborEast;
	Tile *				m_pNeighborSouth;
	Tile *				m_pNeighborWest;
	Tile *				m_pNeighborNorthEast;
	Tile *				m_pNeighborSouthEast;
	Tile *				m_pNeighborSouthWest;
	Tile *				m_pNeighborNorthWest;

	enum GrassState
	{
		GRASS_Full = 0,
		GRASS_North,
		GRASS_East,
		GRASS_South,
		GRASS_West,
		GRASS_NorthWest,
		GRASS_NorthEast,
		GRASS_SouthEast,
		GRASS_SouthWest
	};

public:
	Tile(HyEntity2d *pParent);
	virtual ~Tile();

	TileType GetTileType() const;

	void SetNeighbors(Tile *pNorth, Tile *pEast, Tile *pSouth, Tile *pWest, Tile *pNorthEast, Tile *pSouthEast, Tile *pSouthWest, Tile *pNorthWest);
	void SetType(TileType eType);

	void SetTileState();
	HyShape2d &GetCollision();
};

