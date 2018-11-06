#pragma once
#include "IArea.h"

class Player;

class AreaStructure : public IArea
{
public:
	AreaStructure(HyEntity2d *pParent);
	virtual ~AreaStructure();

	bool CollisionTest(Player &playerRef);
};

