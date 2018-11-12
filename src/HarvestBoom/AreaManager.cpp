#include "pch.h"
#include "AreaManager.h"
#include "Tile.h"
#include "Player.h"

AreaManager::AreaManager(HyEntity2d *pParent) :	HyEntity2d(pParent),
												m_CollidePt1(nullptr),
												m_CollidePt2(nullptr),
												m_uiSetRowCurrentIndex(0)
{
	m_CollidePt1.GetShape().SetAsCircle(2.0f);
	m_CollidePt1.topColor.Set(1.0f, 1.0f, 0.0f);
	m_CollidePt1.SetDisplayOrder(DISPLAYORDER_DebugCollision);

	m_CollidePt2.GetShape().SetAsCircle(2.0f);
	m_CollidePt2.topColor.Set(1.0f, 1.0f, 0.0f);
	m_CollidePt2.SetDisplayOrder(DISPLAYORDER_DebugCollision);

	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(uint32 j = 0; j < AREA_HEIGHT; ++j)
			m_pTileGrid[i][j] = nullptr;
	}
}

AreaManager::~AreaManager()
{
	DeleteTiles();
}

void AreaManager::DeleteTiles()
{
	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(uint32 j = 0; j < AREA_HEIGHT; ++j)
			delete m_pTileGrid[i][j];
	}
}

void AreaManager::ResetTiles()
{
	DeleteTiles();

	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(uint32 j = 0; j < AREA_HEIGHT; ++j)
		{
			m_pTileGrid[i][j] = HY_NEW Tile(this);
			m_pTileGrid[i][j]->pos.Set(i * TILE_SIZE, j * TILE_SIZE);
			m_pTileGrid[i][j]->SetDisplayOrder((AREA_HEIGHT - j) * DISPLAYORDER_PerRow);
		}
	}

	// Setting up each Tiles' neighbor
	for(int32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(int32 j = 0; j < AREA_HEIGHT; ++j)
		{
			Tile *pNorth = (j + 1) < AREA_HEIGHT ?	m_pTileGrid[i][j+1] : nullptr;
			Tile *pEast  = (i + 1) < AREA_WIDTH ?	m_pTileGrid[i+1][j] : nullptr;
			Tile *pSouth = (j - 1) >= 0 ?			m_pTileGrid[i][j-1] : nullptr;
			Tile *pWest  = (i - 1) >= 0 ?			m_pTileGrid[i-1][j] : nullptr;

			Tile *pNorthEast = ((i+1) < AREA_WIDTH	&& (j+1) < AREA_HEIGHT)	?	m_pTileGrid[i+1][j+1] : nullptr;
			Tile *pSouthEast = ((i+1) < AREA_WIDTH	&& (j-1) >= 0)			?	m_pTileGrid[i+1][j-1] : nullptr;
			Tile *pSouthWest = ((i-1) >= 0			&& (j-1) >= 0)			?	m_pTileGrid[i-1][j-1] : nullptr;
			Tile *pNorthWest = ((i-1) >= 0			&& (j+1) < AREA_HEIGHT)	?	m_pTileGrid[i-1][j+1] : nullptr;

			m_pTileGrid[i][j]->SetNeighbors(pNorth, pEast, pSouth, pWest, pNorthEast, pSouthEast, pSouthWest, pNorthWest);
		}
	}

	m_CollidePt1.Load();
	m_CollidePt2.Load();
}

void AreaManager::ConstructLevel1()
{
	m_uiSetRowCurrentIndex = AREA_HEIGHT -1;

	//      0123456789012345678901234
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("________HHHHHHHHH________");
	SetRow("________HHHHHHHHH________");
	SetRow("________HHHHHHHHH________");
	SetRow("________HHHHHHDHH________");
	SetRow("________HHHHHHDHH________");
	SetRow("_________________________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");

	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(uint32 j = 0; j < AREA_HEIGHT; ++j)
			m_pTileGrid[i][j]->SetTileState();
	}
}

void AreaManager::UpdatePlayer(Player &playerRef)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Display Order
	int iPlayerInRow = AREA_HEIGHT - (playerRef.pos.Y() * TILE_SIZE);
	playerRef.SetDisplayOrder(((AREA_HEIGHT - iPlayerInRow) * DISPLAYORDER_PerRow) + DISPLAYORDER_Player);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Player Tile
	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(uint32 j = 0; j < AREA_HEIGHT; ++j)
			m_pTileGrid[i][j]->topColor.Set(1.0f, 1.0f, 1.0f);
	}

	int32 iX = static_cast<int32>(playerRef.pos.X() / TILE_SIZE);
	int32 iY = static_cast<int32>(playerRef.pos.Y() / TILE_SIZE);
	Tile *pPlayerTile = nullptr;
	if(iX >= 0 && iX < AREA_WIDTH && iY >= 0 && iY < AREA_HEIGHT)
		pPlayerTile = m_pTileGrid[iX][iY];

	if(pPlayerTile)
		pPlayerTile->topColor.Set(1.0f, 0.0f, 0.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Collision
	b2WorldManifold manifold;
	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		for(uint32 j = 0; j < AREA_HEIGHT; ++j)
		{
			if(m_pTileGrid[i][j]->GetTileType() == House && m_pTileGrid[i][j]->GetCollision().IsColliding(playerRef.GetCollision(), manifold))
			{
				m_CollidePt1.pos.Set(manifold.points[0].x, manifold.points[0].y);
				m_CollidePt2.pos.Set(manifold.points[1].x, manifold.points[1].y);


			}
		}
	}
}

void AreaManager::SetRow(std::string sRow)
{
	HyAssert(sRow.length() == AREA_WIDTH, "AreaManager::SetRow improper sRow length. Not " << AREA_WIDTH);

	for(uint32 i = 0; i < AREA_WIDTH; ++i)
	{
		switch(sRow[i])
		{
		case '_':	m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Grass);			break;
		case 'H':	m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(House);			break;
		case 'D':	m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(HouseDoor);		break;
		case '+':	m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);			break;
		}
	}

	--m_uiSetRowCurrentIndex;
}
