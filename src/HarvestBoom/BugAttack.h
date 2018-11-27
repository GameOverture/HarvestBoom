#pragma once
#include "pch.h"
#include "Bug.h"

class BugAttack : public HyEntity2d
{
	typedef std::vector<glm::ivec2> Path;

	std::vector<Path>		m_PathList;
	std::vector<Bug *>		m_BugList;

	enum BugState
	{
		BUGSTATE_CreateBugs = 0,
		BUGSTATE_March,
	};
	BugState				m_eBugState;

public:
	BugAttack(HyEntity2d *pParent);
	virtual ~BugAttack();

	void Sync();

	bool BugUpdate();

private:
	void PathStart(int32 x, int32 y);
	void PathAppend(int32 x, int32 y);
	void PathEnd();
};