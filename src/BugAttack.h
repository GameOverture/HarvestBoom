#pragma once
#include "pch.h"
#include "Bug.h"

class World;

class BugAttack : public HyEntity2d
{
	typedef std::vector<glm::ivec2> Path;

	World &					m_WorldRef;
	std::vector<Bug *>		m_BugList;

public:
	BugAttack(World &worldRef, HyEntity2d *pParent);
	virtual ~BugAttack();

	void Setup();
	bool BugUpdate();
};
