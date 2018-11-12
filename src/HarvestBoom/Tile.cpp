#include "pch.h"
#include "Tile.h"


Tile::Tile(HyEntity2d *pParent) :	HyEntity2d(pParent),
									m_eTileType(Unknown),
									m_Ground(this),
									m_pTexture(nullptr),
									m_pNeighborNorth(nullptr),
									m_pNeighborEast(nullptr),
									m_pNeighborSouth(nullptr),
									m_pNeighborWest(nullptr),
									m_pNeighborNorthEast(nullptr),
									m_pNeighborSouthEast(nullptr),
									m_pNeighborSouthWest(nullptr),
									m_pNeighborNorthWest(nullptr)
{
	m_Ground.GetShape().SetAsBox(TILE_SIZE, TILE_SIZE);
}

Tile::~Tile()
{
}

TileType Tile::GetTileType() const
{
	return m_eTileType;
}

void Tile::SetNeighbors(Tile *pNorth, Tile *pEast, Tile *pSouth, Tile *pWest, Tile *pNorthEast, Tile *pSouthEast, Tile *pSouthWest, Tile *pNorthWest)
{
	m_pNeighborNorth = pNorth;
	m_pNeighborEast = pEast;
	m_pNeighborSouth = pSouth;
	m_pNeighborWest = pWest;

	m_pNeighborNorthEast = pNorthEast;
	m_pNeighborSouthEast = pSouthEast;
	m_pNeighborSouthWest = pSouthWest;
	m_pNeighborNorthWest = pNorthWest;
}

void Tile::SetType(TileType eType)
{
	m_eTileType = eType;
	switch(m_eTileType)
	{
	case Grass:
		delete m_pTexture;
		m_pTexture = HY_NEW HySprite2d("Tiles", "Grass", this);
		m_Ground.SetEnabled(false);
		break;
	case House:
		m_Ground.topColor.Set(0.623529f, 0.623529f, 0.372549f);
		m_Ground.SetEnabled(true);
		break;

	case HouseDoor:
		m_Ground.topColor.Set(0.184314f, 0.309804f, 0.309804f);
		m_Ground.SetEnabled(true);
		break;

	case Dirt:
		delete m_pTexture;
		m_pTexture = HY_NEW HySprite2d("Tiles", "Dirt", this);
		m_Ground.SetEnabled(false);
		break;
	case Impassable:
		m_Ground.topColor.Set(0.6f, 0.8f, 0.196078f);
		break;
	//case Asphalt:
	//	m_Ground.topColor.Set(0.184314f, 0.309804f, 0.309804f);
	//	SetDisplayOrder(DISPLAYORDER_Asphalt);
	//	break;
	}
}

void Tile::SetTileState()
{
	switch(m_eTileType)
	{
	case Grass:
		if(m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_South);
		if(m_pNeighborEast && m_pNeighborEast->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_West);
		if(m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_North);
		if(m_pNeighborWest && m_pNeighborWest->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_East);

		if(m_pNeighborNorthEast && m_pNeighborNorthEast->GetTileType() == Dirt &&
		   m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Grass &&
		   m_pNeighborEast && m_pNeighborEast->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_SouthWest);
		}

		if(m_pNeighborSouthEast && m_pNeighborSouthEast->GetTileType() == Dirt &&
		   m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Grass &&
		   m_pNeighborEast && m_pNeighborEast->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_NorthWest);
		}

		if(m_pNeighborSouthWest && m_pNeighborSouthWest->GetTileType() == Dirt &&
		   m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Grass &&
		   m_pNeighborWest && m_pNeighborWest->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_NorthEast);
		}

		if(m_pNeighborNorthWest && m_pNeighborNorthWest->GetTileType() == Dirt &&
		   m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Grass &&
		   m_pNeighborWest && m_pNeighborWest->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_SouthEast);
		}

		break;
	}
}

HyShape2d &Tile::GetCollision()
{
	return m_Ground.GetShape();
}
