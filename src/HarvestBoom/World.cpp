#include "pch.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Stamina.h"
#include "Plant.h"

World::World(HyEntity2d *pParent) :	HyEntity2d(pParent),
									m_uiSetRowCurrentIndex(0),
									m_DebugCollidePt1(nullptr),
									m_DebugCollidePt2(nullptr),
									m_DebugCollideNormal(nullptr)
{
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

	m_DebugCollidePt1.GetShape().SetAsCircle(2.0f);
	m_DebugCollidePt1.topColor.Set(1.0f, 0.0f, 1.0f);
	m_DebugCollidePt1.SetDisplayOrder(DISPLAYORDER_DebugCollision);
	m_DebugCollidePt1.SetEnabled(false);
	m_DebugCollidePt1.Load();

	m_DebugCollidePt2.GetShape().SetAsCircle(2.0f);
	m_DebugCollidePt2.topColor.Set(1.0f, 0.0f, 1.0f);
	m_DebugCollidePt2.SetDisplayOrder(DISPLAYORDER_DebugCollision);
	m_DebugCollidePt2.SetEnabled(false);
	m_DebugCollidePt2.Load();

	m_DebugCollideNormal.SetLineThickness(2.0f);
	m_DebugCollideNormal.topColor.Set(1.0f, 0.0f, 1.0f);
	m_DebugCollideNormal.SetDisplayOrder(DISPLAYORDER_DebugCollision);
	m_DebugCollideNormal.SetEnabled(false);
	m_DebugCollideNormal.Load();
}

World::~World()
{
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			delete m_pTileGrid[i][j];
	}
}

Tile *World::GetTile(uint32 uiX, uint32 uiY)
{
	return m_pTileGrid[uiX][uiY];
}

uint32 World::GetNumWaypoints()
{
	return static_cast<uint32>(m_PheromoneWaypointList.size());
}

glm::ivec2 World::GetWaypoint(uint32 uiIndex)
{
	return m_PheromoneWaypointList[uiIndex].second->GetPos();
}

void World::SetupNewDay()
{
	m_uiSetRowCurrentIndex = WORLD_HEIGHT -1;
	m_PheromoneWaypointList.clear();

	switch(Values::Get()->m_uiCurrentDay)
	{
	case 1:
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
		SetRow("_________________________");
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
		break;

	case 2: // First bug attack night
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
		SetRow("_________________________");
		SetRow("__________+2++___________");
		SetRow("__________++++___________");
		SetRow("__________++++___________");
		SetRow("__________++1+___________");
		SetRow("___________++____________");
		SetRow("___________++____________");
		SetRow("___________++____________");
		SetRow("___________++____________");
		SetRow("___________++____________");
		SetRow("___________+0____________");
		SetRow("_________________________");
		break;

	case 3:
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
		SetRow("_________________________");
		SetRow("_________++3+++__________");
		SetRow("_________++++++__________");
		SetRow("_________++2+++__________");
		SetRow("_________++++++__________");
		SetRow("_________++++++__________");
		SetRow("_________++++++__________");
		SetRow("_________+1++++__________");
		SetRow("_________++++++__________");
		SetRow("_________++++++__________");
		SetRow("_________+0++++__________");
		SetRow("_________________________");
		break;
	}

	std::sort(m_PheromoneWaypointList.begin(), m_PheromoneWaypointList.end(), &PheromoneWaypointSortPredicate);

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j]->SetTileState();
	}
}

void World::CleanupTiles()
{
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j]->Reset();
	}
}


void World::UpdatePlayer(Player &playerRef, Stamina &staminaRef, HousePanel &housePanelRef)
{
	CleanupTiles();

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
		if(pPlayerTile->GetPlant() && playerRef.pos.Y() < pPlayerTile->pos.Y() + (TILE_SIZE * 0.5f))
			playerRef.SetDisplayOrder(pPlayerTile->GetPlant()->GetDisplayOrder() + 1);
		else
			playerRef.SetDisplayOrder(pPlayerTile->GetDisplayOrder() + DISPLAYORDER_TILE_SelectRect);

		if(pPlayerTile->GetTileType() == HouseDoor)
		{
			housePanelRef.Show();
			playerRef.SetEnabled(false);
		}
		else if(pPlayerTile->GetTileType() != HouseDoor)
		{
			if(housePanelRef.Hide())
			{
				playerRef.SetEnabled(true);
				Values::Get()->Sync();
			}
		}

		if(housePanelRef.IsShown() && housePanelRef.IsTransition() == false && Values::Get()->m_bAirConditioning)
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
				Values::Get()->Sync();
			}
		}
		else
			playerRef.StopAction();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Player movement and Collision
	playerRef.HandleInput(pPlayerTile);


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
				m_DebugCollideNormal.GetShape().SetAsLineSegment(ptMidpoint, ptMidpoint + vNormal);
				m_DebugCollideNormal.Load();

				m_DebugCollidePt1.pos.Set(manifold.points[0].x, manifold.points[0].y);
				m_DebugCollidePt2.pos.Set(manifold.points[1].x, manifold.points[1].y);
			}
		}
	}

	float fRunNormalized = playerRef.GetMagnitude() / Values::Get()->m_fPLAYER_MAXVELOCITY;
	staminaRef.Offset((Values::Get()->m_fSTAMINA_RUN * fRunNormalized) * -Hy_UpdateStep());
}

void World::SetRow(std::string sRow)
{
	HyAssert(sRow.length() == WORLD_WIDTH, "World::SetRow improper sRow length. Not " << WORLD_WIDTH);

	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		switch(sRow[i])
		{
		case '_':
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Grass);
			break;
		case 'H':
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(House);
			break;
		case 'D':
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(HouseDoor);
			break;

		case '0':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(0, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '1':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(1, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '2':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(2, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '3':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(3, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '4':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(4, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '5':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(5, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '6':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(6, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '7':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(7, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '8':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(8, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '9':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(9, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;
		case '+':
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Dirt);
			break;

		default:
			HyError("World::SetRow bad character");
		}
	}

	--m_uiSetRowCurrentIndex;
}

/*static*/ bool World::PheromoneWaypointSortPredicate(const PheromoneWaypoint wayPt1, const PheromoneWaypoint wayPt2)
{
	return wayPt1.first < wayPt2.first;
}
