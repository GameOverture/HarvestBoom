#include "pch.h"
#include "BugAttack.h"
#include "HarvestBoom.h"

BugAttack::BugAttack(HyEntity2d *pParent) :
	HyEntity2d(pParent),
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
