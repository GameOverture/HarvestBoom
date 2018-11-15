#include "pch.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Stamina.h"

World::World(HyEntity2d *pParent) :	HyEntity2d(pParent),
									m_CollidePt1(nullptr),
									m_CollidePt2(nullptr),
									m_CollideNormal(nullptr),
									m_uiSetRowCurrentIndex(0),
									m_pHousePanel(nullptr)
{
	m_CollidePt1.GetShape().SetAsCircle(2.0f);
	m_CollidePt1.topColor.Set(1.0f, 0.0f, 1.0f);
	m_CollidePt1.SetDisplayOrder(DISPLAYORDER_DebugCollision);

	m_CollidePt2.GetShape().SetAsCircle(2.0f);
	m_CollidePt2.topColor.Set(1.0f, 0.0f, 1.0f);
	m_CollidePt2.SetDisplayOrder(DISPLAYORDER_DebugCollision);

	m_CollideNormal.SetLineThickness(2.0f);
	m_CollideNormal.topColor.Set(1.0f, 0.0f, 1.0f);
	m_CollideNormal.SetDisplayOrder(DISPLAYORDER_DebugCollision);

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j] = nullptr;
	}

	InfoPanelInit equipInfoPanelInit;
	equipInfoPanelInit.panel_LoadPath.Set("Game", "EquipButton");
	equipInfoPanelInit.text_LoadPath.Set("Game", "Small");
	HySetVec(equipInfoPanelInit.text_LocalOffSet, 8, 5);
	HySetVec(equipInfoPanelInit.text_ScaleBox, 70, 35);

	InfoPanelInit buyInfoPanelInit;
	buyInfoPanelInit.panel_LoadPath.Set("Game", "BuyButton");
	buyInfoPanelInit.text_LoadPath.Set(HY_SYSTEM_FONT);// "Game", "Small");
	HySetVec(buyInfoPanelInit.text_LocalOffSet, 8, 3);
	HySetVec(buyInfoPanelInit.text_ScaleBox, 65, 30);

	m_pHousePanel = HY_NEW HousePanel(equipInfoPanelInit, buyInfoPanelInit, this);
}

World::~World()
{
	DeleteTiles();
}

void World::DeleteTiles()
{
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			delete m_pTileGrid[i][j];
	}
}

void World::Construct()
{
	DeleteTiles();

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
		{
			m_pTileGrid[i][j] = HY_NEW Tile(this);
			m_pTileGrid[i][j]->pos.Set(i * TILE_SIZE, j * TILE_SIZE);
			m_pTileGrid[i][j]->SetDisplayOrder((WORLD_HEIGHT - j) * DISPLAYORDER_PerRow);
		}
	}

	// Setting up each Tiles' neighbor
	for(int32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(int32 j = 0; j < WORLD_HEIGHT; ++j)
		{
			Tile *pNorth = (j + 1) < WORLD_HEIGHT ?	m_pTileGrid[i][j+1] : nullptr;
			Tile *pEast  = (i + 1) < WORLD_WIDTH ?	m_pTileGrid[i+1][j] : nullptr;
			Tile *pSouth = (j - 1) >= 0 ?			m_pTileGrid[i][j-1] : nullptr;
			Tile *pWest  = (i - 1) >= 0 ?			m_pTileGrid[i-1][j] : nullptr;

			Tile *pNorthEast = ((i+1) < WORLD_WIDTH	&& (j+1) < WORLD_HEIGHT)	?	m_pTileGrid[i+1][j+1] : nullptr;
			Tile *pSouthEast = ((i+1) < WORLD_WIDTH	&& (j-1) >= 0)			?	m_pTileGrid[i+1][j-1] : nullptr;
			Tile *pSouthWest = ((i-1) >= 0			&& (j-1) >= 0)			?	m_pTileGrid[i-1][j-1] : nullptr;
			Tile *pNorthWest = ((i-1) >= 0			&& (j+1) < WORLD_HEIGHT)	?	m_pTileGrid[i-1][j+1] : nullptr;

			m_pTileGrid[i][j]->SetNeighbors(pNorth, pEast, pSouth, pWest, pNorthEast, pSouthEast, pSouthWest, pNorthWest);
		}
	}

	m_CollidePt1.Load();
	m_CollidePt2.Load();
	m_CollideNormal.Load();

	m_CollidePt1.SetEnabled(false);
	m_CollidePt2.SetEnabled(false);
	m_CollideNormal.SetEnabled(false);

	m_pHousePanel->Construct();
}

void World::SetLevel()
{
	switch(Values::Get()->m_uiCurrentDay)
	{
	case 1:	SetAsLevel1(); break;
	case 2:	SetAsLevel2(); break;
	}
}

void World::SetAsLevel1()
{
	m_uiSetRowCurrentIndex = WORLD_HEIGHT -1;

	//      0123456789012345678901234
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________HHHHHH__________");
	SetRow("_________HHHHHH__________");
	SetRow("_________HHHHHH__________");
	SetRow("_________HHDHHH__________");
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

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j]->SetTileState();
	}
}

void World::SetAsLevel2()
{
	m_uiSetRowCurrentIndex = WORLD_HEIGHT -1;

	//      0123456789012345678901234
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________HHHHHH__________");
	SetRow("_________HHHHHH__________");
	SetRow("_________HHHHHH__________");
	SetRow("_________HHDHHH__________");
	SetRow("_________________________");
	SetRow("___________++____________");
	SetRow("_________++++++__________");
	SetRow("_________++++++__________");
	SetRow("_________++++++__________");
	SetRow("_________++++++__________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("___________++____________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");
	SetRow("_________________________");

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j]->SetTileState();
	}
}


void World::UpdatePlayer(Player &playerRef, Stamina &staminaRef)
{
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Display Order
	int32 iPlayerInRow = WORLD_HEIGHT - static_cast<int32>(playerRef.pos.Y() * TILE_SIZE);
	playerRef.SetDisplayOrder(((WORLD_HEIGHT - iPlayerInRow) * DISPLAYORDER_PerRow) + DISPLAYORDER_Player);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Cleanup from last update
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j]->Cleanup();
	}

	// NOTE: Cannot combine with above
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j]->IncrementGrowing();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Player Tile
	int32 iX = static_cast<int32>(playerRef.pos.X() / TILE_SIZE);
	int32 iY = static_cast<int32>(playerRef.pos.Y() / TILE_SIZE);
	Tile *pPlayerTile = nullptr;
	if(iX >= 0 && iX < WORLD_WIDTH && iY >= 0 && iY < WORLD_HEIGHT)
		pPlayerTile = m_pTileGrid[iX][iY];

	if(pPlayerTile)
	{
		if(pPlayerTile->GetTileType() == HouseDoor && m_pHousePanel->IsShowing() == false && m_pHousePanel->IsTransition() == false)
		{
			m_pHousePanel->Show();
			playerRef.SetEnabled(false);
		}
		else if(pPlayerTile->GetTileType() != HouseDoor && m_pHousePanel->IsShowing() && m_pHousePanel->IsTransition() == false)
		{
			m_pHousePanel->Hide();
			playerRef.SetEnabled(true);
			playerRef.Sync();
		}

		if(m_pHousePanel->IsShowing() && m_pHousePanel->IsTransition() == false && Values::Get()->m_bAirConditioning)
			staminaRef.Offset(Values::Get()->m_fSTAMINA_AC * Hy_UpdateStep());
		
		// Determine if this tile should be "Selected"
		if(pPlayerTile->GetTileType() == Dirt)
		{
			pPlayerTile->SetAsSelected();
		}

		// Apply or clear Player action / animations
		if(Hy_App().Input().IsActionDown(UseEquip) && pPlayerTile->GetTileType() == Dirt)
		{
			if(playerRef.DoAction(*pPlayerTile))
			{
				staminaRef.Offset(Values::Get()->m_fSTAMINA_ACTION * -Hy_UpdateStep());
				m_pHousePanel->Sync();
			}
		}
		else
			playerRef.StopAction();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Collision
	b2WorldManifold manifold;
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
		{
			if(m_pTileGrid[i][j]->GetTileType() == House && m_pTileGrid[i][j]->GetCollision().IsColliding(playerRef.GetCollision(), manifold))
			{
				glm::vec2 vNormal;
				vNormal.x = manifold.normal.x;
				vNormal.y = manifold.normal.y;
				vNormal *= (manifold.separations[0] * -1.0f);

				if(abs(vNormal.x) > 0.0f)
					playerRef.ZeroVelocityX();
				else
					playerRef.ZeroVelocityY();

				playerRef.pos.Offset(vNormal);

				glm::vec2 ptMidpoint((manifold.points[0].x + manifold.points[1].x) / 2.0f, (manifold.points[0].y + manifold.points[1].y) / 2.0f);
				m_CollideNormal.GetShape().SetAsLineSegment(ptMidpoint, ptMidpoint + vNormal);
				m_CollideNormal.Load();

				m_CollidePt1.pos.Set(manifold.points[0].x, manifold.points[0].y);
				m_CollidePt2.pos.Set(manifold.points[1].x, manifold.points[1].y);
			}
		}
	}

	float fRunNormalized = playerRef.GetMagnitude() / Values::Get()->m_fPLAYER_MAXVELOCITY;
	staminaRef.Offset((Values::Get()->m_fSTAMINA_RUN * fRunNormalized) * -Hy_UpdateStep());
}

void World::Reset()
{
	if(m_pHousePanel->IsShowing() && m_pHousePanel->IsTransition() == false)
		m_pHousePanel->Hide();
}

HousePanel *World::GetHousePanel()
{
	return m_pHousePanel;
}

void World::SetRow(std::string sRow)
{
	HyAssert(sRow.length() == WORLD_WIDTH, "World::SetRow improper sRow length. Not " << WORLD_WIDTH);

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
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
