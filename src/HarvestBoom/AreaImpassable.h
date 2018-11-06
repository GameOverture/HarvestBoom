#pragma once

#include "IArea.h"
class AreaImpassable : public IArea
{
public:
	AreaImpassable(HyEntity2d *pParent);
	virtual ~AreaImpassable();
};

