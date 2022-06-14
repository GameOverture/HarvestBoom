#include "pch.h"
#include "World.h"
#include "Tile.h"
#include "Player.h"
#include "Stamina.h"
#include "Plant.h"
#include "HarvestBoom.h"

World::World(HyEntity2d *pParent) :
	HyEntity2d(pParent),
	m_uiSetRowCurrentIndex(0),
	m_pDoorTile(nullptr),
	m_DebugCollidePt1(nullptr),
	m_DebugCollidePt2(nullptr),
	m_DebugCollideNormal(nullptr)
{
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			m_pTileGrid[i][j] = nullptr;
	}

	Reset();

	m_DebugCollidePt1.shape.SetAsCircle(2.0f);
	m_DebugCollidePt1.topColor.Set(1.0f, 0.0f, 1.0f);
	m_DebugCollidePt1.SetDisplayOrder(DISPLAYORDER_DebugCollision);
	m_DebugCollidePt1.SetVisible(false);

	m_DebugCollidePt2.shape.SetAsCircle(2.0f);
	m_DebugCollidePt2.topColor.Set(1.0f, 0.0f, 1.0f);
	m_DebugCollidePt2.SetDisplayOrder(DISPLAYORDER_DebugCollision);
	m_DebugCollidePt2.SetVisible(false);

	m_DebugCollideNormal.SetLineThickness(2.0f);
	m_DebugCollideNormal.topColor.Set(1.0f, 0.0f, 1.0f);
	m_DebugCollideNormal.SetDisplayOrder(DISPLAYORDER_DebugCollision);
	m_DebugCollideNormal.SetVisible(false);
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
	if(uiX >= 0 && uiX < WORLD_WIDTH && uiY >= 0 && uiY < WORLD_HEIGHT)
		return m_pTileGrid[uiX][uiY];
	
	return nullptr;
}

Tile *World::FindTile(glm::vec2 ptWorldCoordinate)
{
	int32 iX = static_cast<int32>(ptWorldCoordinate.x / TILE_SIZE);
	int32 iY = static_cast<int32>(ptWorldCoordinate.y / TILE_SIZE);
	
	if(iX >= 0 && iX < WORLD_WIDTH && iY >= 0 && iY < WORLD_HEIGHT)
		return m_pTileGrid[iX][iY];

	return nullptr;
}

glm::vec2 World::GetDoorCenter()
{
	if(m_pDoorTile == nullptr)
		return glm::vec2();

	return glm::vec2(m_pDoorTile->pos.X() + (TILE_SIZE * 0.5f), m_pDoorTile->pos.Y() + (TILE_SIZE * 0.5f));
}

uint32 World::GetNumWaypoints()
{
	return static_cast<uint32>(m_PheromoneWaypointList.size());
}

glm::ivec2 World::GetTileWaypoint(uint32 uiIndex)
{
	return m_PheromoneWaypointList[uiIndex].second->GetPos();
}

glm::vec2 World::GetPixelWaypoint(uint32 uiIndex)
{
	return glm::vec2((m_PheromoneWaypointList[uiIndex].second->GetPos().x * TILE_SIZE) + (TILE_SIZE * 0.5f), (m_PheromoneWaypointList[uiIndex].second->GetPos().y * TILE_SIZE) + (TILE_SIZE * 0.5f));
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
		SetRow("__________+4++___________");
		SetRow("__________++++___________");
		SetRow("__________++++___________");
		SetRow("__________++3+___________");
		SetRow("___________++____________");
		SetRow("___________2+____________");
		SetRow("___________++____________");
		SetRow("___________+1____________");
		SetRow("_________________________");
		SetRow("_________________________");
		SetRow("____________0____________");
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
		SetRow("__________+++5+__________");
		SetRow("__________+++4+__________");
		SetRow("__________++++___________");
		SetRow("__________+3++___________");
		SetRow("___________+++___________");
		SetRow("___________++2___________");
		SetRow("___________+++___________");
		SetRow("___________+1+___________");
		SetRow("_________________________");
		SetRow("_________________________");
		SetRow("____________0____________");
		break;

	case 4:
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
		SetRow("_________++5+++__________");
		SetRow("_________++++++__________");
		SetRow("_________+4++++__________");
		SetRow("_________++++++__________");
		SetRow("_________++++3+__________");
		SetRow("_________++++++__________");
		SetRow("_________+2++++__________");
		SetRow("_________++++++__________");
		SetRow("_________++++++__________");
		SetRow("_________+1++++__________");
		SetRow("___________0_____________");
		break;

	case 5:
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
		SetRow("_______+++++++6__________");
		SetRow("_______++++++++__________");
		SetRow("_______+5++++++__________");
		SetRow("_______++++++++++________");
		SetRow("_______++++++4+++________");
		SetRow("_________++++++++________");
		SetRow("_________+3++++++________");
		SetRow("_________++++++++________");
		SetRow("_________+2++++++________");
		SetRow("_________++++1+__________");
		SetRow("___________0_____________");
		break;

	case 6:
	case 7:
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
		SetRow("_______+8++++++++________");
		SetRow("_______+++++++7++________");
		SetRow("_______+6++++++++________");
		SetRow("_______+++++++5++________");
		SetRow("_______++++++++++________");
		SetRow("_______+++++++4++________");
		SetRow("_______+3++++++++________");
		SetRow("_______++++++++++________");
		SetRow("_______+++++++2++________");
		SetRow("_______++1+++++++________");
		SetRow("___________0_____________");
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
		if(pPlayerTile->GetPlant())
		{
			if(playerRef.pos.Y() < pPlayerTile->pos.Y() + (TILE_SIZE * 0.5f))
				playerRef.SetDisplayOrder(pPlayerTile->GetPlant()->GetDisplayOrder() + 1);
			else
				playerRef.SetDisplayOrder(pPlayerTile->GetPlant()->GetDisplayOrder() - 1);
		}
		else
			playerRef.SetDisplayOrder(pPlayerTile->GetDisplayOrder() + DISPLAYORDER_TILE_SelectRect);

		if(pPlayerTile->GetTileType() == HouseDoor)
		{
			if(housePanelRef.Show())
				HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_DOOR_OPEN);

			playerRef.SetVisible(false);
		}
		else if(pPlayerTile->GetTileType() != HouseDoor)
		{
			if(housePanelRef.Hide())
			{
				HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_DOOR_CLOSE);
				playerRef.SetVisible(true);
				Values::Get()->Sync();
			}
		}

		if(housePanelRef.IsShown() && housePanelRef.IsTransition() == false && Values::Get()->m_bAirConditioning)
			staminaRef.Offset(Values::Get()->m_fSTAMINA_AC * HyEngine::DeltaTime());
		
		// Determine if this tile should be "Selected"
		if(pPlayerTile->GetTileType() == Dirt)
		{
			pPlayerTile->SetAsSelected();
		}

		// Apply or clear Player action / animations
		if(HyEngine::Input().IsActionDown(UseEquip) && pPlayerTile->GetTileType() == Dirt)
		{
			if(playerRef.DoAction(*pPlayerTile))
			{
				float fStaminaCost = Values::Get()->m_fSTAMINA_ACTION * (1.0f + (Values::Get()->m_bVitaminStrength ? 0.0f : Values::Get()->m_fSTAMINA_NO_VITAMIN_PENALTY));
				staminaRef.Offset(fStaminaCost * -HyEngine::DeltaTime());
				Values::Get()->Sync();
			}
		}
		else
			playerRef.StopAction();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Player movement and Collision
	playerRef.HandleInput(pPlayerTile);

	glm::mat4 mtxIdentity(1.0f);

	b2WorldManifold manifold;
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
		{
			if(m_pTileGrid[i][j]->GetTileType() != House)
				continue;

			bool bColliding = false;//m_pTileGrid[i][j]->GetCollision().IsColliding(m_pTileGrid[i][j]->GetSceneTransform(), playerRef.GetCollision(), playerRef.GetCollisionTransform(), manifold);
			if(bColliding)
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
				m_DebugCollideNormal.shape.SetAsLineSegment(ptMidpoint, ptMidpoint + vNormal);

				m_DebugCollidePt1.pos.Set(manifold.points[0].x, manifold.points[0].y);
				m_DebugCollidePt2.pos.Set(manifold.points[1].x, manifold.points[1].y);
			}
		}
	}

	float fRunNormalized = playerRef.GetMagnitude() / Values::Get()->m_fPLAYER_MAXVELOCITY;
	staminaRef.Offset((Values::Get()->m_fSTAMINA_RUN * fRunNormalized) * -HyEngine::DeltaTime());
}

void World::Reset()
{
	for(uint32 i = 0; i < WORLD_WIDTH; ++i)
	{
		for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			delete m_pTileGrid[i][j];
	}

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
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(10, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(HouseDoor);
			m_pDoorTile = m_pTileGrid[i][m_uiSetRowCurrentIndex];
			break;

		case '0':
			m_PheromoneWaypointList.push_back(std::pair<uint32, Tile *>(0, m_pTileGrid[i][m_uiSetRowCurrentIndex]));
			m_pTileGrid[i][m_uiSetRowCurrentIndex]->SetType(Grass);
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
