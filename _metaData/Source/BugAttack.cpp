#include "pch.h"
#include "BugAttack.h"
#include "World.h"
#include "Tile.h"
#include "HarvestBoom.h"

#include <random>

void AddUnique(std::vector<Tile *> &vectorRef, Tile *pTile)
{
	for(uint32 i = 0; i < static_cast<uint32>(vectorRef.size()); ++i)
	{
		if(vectorRef[i] == pTile)
			return;
	}

	vectorRef.push_back(pTile);
}

BugAttack::BugAttack(World &worldRef, HyEntity2d *pParent) :
	HyEntity2d(pParent),
	m_WorldRef(worldRef)
{

}

BugAttack::~BugAttack()
{
}

void BugAttack::Setup()
{
	while(m_BugList.empty() == false)
	{
		delete m_BugList.back();
		m_BugList.pop_back();
	}

	switch(Values::Get()->m_uiCurrentDay)
	{
	case 2:
		m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, m_WorldRef, this));
		m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, m_WorldRef, this));
		m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, m_WorldRef, this));
		break;

	case 3:
		for(uint32 i = 0; i < 3; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, m_WorldRef, this));
		for(uint32 i = 0; i < 2; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, m_WorldRef, this));
		break;

	case 4:
		for(uint32 i = 0; i < 5; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, m_WorldRef, this));
		for(uint32 i = 0; i < 2; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, m_WorldRef, this));
		break;

	case 5:
		for(uint32 i = 0; i < 7; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, m_WorldRef, this));
		for(uint32 i = 0; i < 4; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, m_WorldRef, this));

		m_BugList.push_back(HY_NEW Bug(BUGTYPE_Spider, m_WorldRef, this));
		break;

	case 6:
		for(uint32 i = 0; i < 7; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, m_WorldRef, this));
		for(uint32 i = 0; i < 4; ++i)
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, m_WorldRef, this));

		m_BugList.push_back(HY_NEW Bug(BUGTYPE_Spider, m_WorldRef, this));
		m_BugList.push_back(HY_NEW Bug(BUGTYPE_Spider, m_WorldRef, this));
		break;
	}

	for(uint32 i = 0; i < static_cast<uint32>(m_BugList.size()); ++i)
	{
		m_BugList[i]->Load();
		m_BugList[i]->SetDisplayOrder(DISPLAYORDER_DebugGrid);
		m_BugList[i]->SetPos((WORLD_WIDTH / 2) + (i * (i & 1 ? -1 : 1)), -2);
		m_BugList[i]->WalkTo((WORLD_WIDTH / 2) + (i * (i & 1 ? -1 : 1)), 1);
	}

	auto rng = std::default_random_engine {};
	std::shuffle(m_BugList.begin(), m_BugList.end(), rng);

	for(uint32 i = 0; i < static_cast<uint32>(m_BugList.size()); ++i)
		m_BugList[i]->Wait(i * 2.5f);

	if(m_WorldRef.GetNumWaypoints() > 0)
	{
		glm::vec2 ptStartPos = m_WorldRef.GetPixelWaypoint(0);
		for(uint32 i = 1; i < m_WorldRef.GetNumWaypoints(); ++i)
		{
			Tile *pTileDestination = m_WorldRef.FindTile(m_WorldRef.GetPixelWaypoint(i));
			std::vector<Tile *> tilesOnPathList;
			for(uint32 j = 0; j < WORLD_HEIGHT; ++j)
			{
				glm::vec2 vDirection = m_WorldRef.GetPixelWaypoint(i) - ptStartPos;
				vDirection = glm::normalize(vDirection);
				vDirection *= (j * TILE_SIZE);

				Tile *pTileAlongPath = m_WorldRef.FindTile(ptStartPos + vDirection);
				if(pTileAlongPath == pTileDestination)
					break;

				AddUnique(tilesOnPathList, pTileAlongPath);
			}

			for(uint32 j = 0; j < static_cast<uint32>(tilesOnPathList.size()); ++j)
			{
				if(tilesOnPathList[j]->GetPlant())
				{
					for(uint32 k = 0; k < static_cast<uint32>(m_BugList.size()); ++k)
					{
						m_BugList[k]->WalkTo(tilesOnPathList[j]->GetPos().x, tilesOnPathList[j]->GetPos().y);
						m_BugList[k]->Eat();
					}


					// TODO: Check neighboring tiles for plants to eat?



				}
			}

			for(uint32 j = 0; j < static_cast<uint32>(m_BugList.size()); ++j)
			{
				m_BugList[j]->WalkTo(m_WorldRef.GetTileWaypoint(i).x, m_WorldRef.GetTileWaypoint(i).y);
				if(i == 1) // After first waypoint, enable collision
					m_BugList[j]->EnableCollision();
			}
			
			ptStartPos = m_WorldRef.GetPixelWaypoint(i);
		}
	}
}

bool BugAttack::BugUpdate()
{
	for(auto iter = m_BugList.begin(); iter != m_BugList.end(); )
	{
		Tile *pTile = m_WorldRef.FindTile((*iter)->pos.Get());
		if(pTile)
		{
			if((*iter)->IsEating() && pTile->GetPlant() == nullptr)
				(*iter)->StopEating();

			if(pTile->GetTileType() == HouseDoor)
			{
				switch((*iter)->GetBugType())
				{
				case BUGTYPE_Beetle:
					Values::Get()->m_uiDamageCost += Values::Get()->m_uiDAMAGE_BEETLE;
					break;
		
				case BUGTYPE_Ant:
					Values::Get()->m_uiDamageCost += Values::Get()->m_uiDAMAGE_ANT;
					break;

				case BUGTYPE_Spider:
					Values::Get()->m_uiDamageCost += Values::Get()->m_uiDAMAGE_SPIDER;
					break;
				}
				
				delete (*iter);
				iter = m_BugList.erase(iter);
				continue;
			}
		}

		if((*iter)->GetHealth() == 0.0f)
		{
			delete (*iter);
			iter = m_BugList.erase(iter);
			continue;
		}

		if((*iter)->GetStomach() == 1.0f)
		{
			if((*iter)->IsGoingHome() == false)
				(*iter)->GoHome();
			else if((*iter)->pos.IsAnimating() == false)
			{
				delete (*iter);
				iter = m_BugList.erase(iter);
				continue;
			}
		}

		// Check for bug collision
		for(uint32 i = 0; i < static_cast<uint32>(m_BugList.size()); ++i)
		{
			if(m_BugList[i] == (*iter) || (*iter)->IsGoingHome() || (*iter)->IsColliable() == false)
				continue;

			float fThisDist = glm::distance((*iter)->pos.Get(), m_WorldRef.GetDoorCenter());
			float fTestDist = glm::distance(m_BugList[i]->pos.Get(), m_WorldRef.GetDoorCenter());

			if(b2TestOverlap(m_BugList[i]->GetLeaf().GetSceneAABB(), (*iter)->GetLeaf().GetSceneAABB()) && fThisDist > fTestDist && (*iter)->IsWaiting() == false)
				(*iter)->InterruptWalkTo(0.5f);
		}

		(*iter)->BugUpdate();
		++iter;
	}

	return m_BugList.size() > 0;
}
