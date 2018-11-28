#include "pch.h"
#include "BugAttack.h"
#include "World.h"
#include "HarvestBoom.h"

BugAttack::BugAttack(World &worldRef, HyEntity2d *pParent) :
	HyEntity2d(pParent),
	m_WorldRef(worldRef),
	m_eBugState(BUGSTATE_CreateBugs)
{

}

BugAttack::~BugAttack()
{
}

void BugAttack::Sync()
{
}

bool BugAttack::BugUpdate()
{
	switch(m_eBugState)
	{
	case BUGSTATE_CreateBugs:
		
		switch(Values::Get()->m_uiCurrentDay)
		{
		case 2:
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, this));
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, this));
			m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, this));
			break;

		case 3:
			for(uint32 i = 0; i < 3; ++i)
				m_BugList.push_back(HY_NEW Bug(BUGTYPE_Beetle, this));
			for(uint32 i = 0; i < 2; ++i)
				m_BugList.push_back(HY_NEW Bug(BUGTYPE_Ant, this));
			break;
		}

		for(uint32 i = 0; i < static_cast<uint32>(m_BugList.size()); ++i)
		{
			m_BugList[i]->Load();
			m_BugList[i]->SetDisplayOrder(DISPLAYORDER_DebugGrid);
			m_BugList[i]->SetPos(WORLD_WIDTH / 2, 0);
			m_BugList[i]->WalkTo((static_cast<float>(WORLD_WIDTH) * 0.5f) + (i * TILE_SIZE) * (i & 1 ? -1.0f : 1.0f), 1);
		}

		m_eBugState = BUGSTATE_Setup;
		break;

	case BUGSTATE_Setup:
		{
			bool bContinue = true;
			for(uint32 i = 0; i < static_cast<uint32>(m_BugList.size()); ++i)
			{
				if(m_BugList[i]->IsIdle())
				{
					bContinue = false;
					break;
				}
			}

			if(bContinue)
			{
				for(uint32 i = 0; i < m_WorldRef.GetNumWaypoints(); ++i)
				{
					glm::vec2 ptWaypoint(static_cast<float>(m_WorldRef.GetWaypoint(i).x), static_cast<float>(m_WorldRef.GetWaypoint(i).y));
					ptWaypoint += (TILE_SIZE * 0.5f);

					for(uint32 j = 0; j < static_cast<uint32>(m_BugList.size()); ++j)
						m_BugList[j]->WalkTo(ptWaypoint.x, ptWaypoint.y);
				}

				m_eBugState = BUGSTATE_March;
			}
		}
		break;

	case BUGSTATE_March:
		break;
	}

	return true;
}

void BugAttack::PathStart(int32 x, int32 y)
{
	m_PathList.push_back(Path());
}

void BugAttack::PathAppend(int32 x, int32 y)
{

}

void BugAttack::PathEnd()
{
}
