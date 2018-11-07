#pragma once
#include "IArea.h"

class Player;

class AreaStructure : public IArea
{
	HyPrimitive2d	m_CollidePt1;
	HyPrimitive2d	m_CollidePt2;

public:
	AreaStructure(HyEntity2d *pParent);
	virtual ~AreaStructure();

	bool CollisionTest(Player &playerRef);
};

