#include "pch.h"
#include "Bug.h"

Bug::Bug(BugType eBugType, HyEntity2d *pParent) :
	HySprite2d("Game", "Bug", pParent)
{
	AnimSetState(eBugType);
}

Bug::~Bug()
{
}
