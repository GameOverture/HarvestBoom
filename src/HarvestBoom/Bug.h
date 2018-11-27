#pragma once
#include "pch.h"

class Bug : public HySprite2d
{
public:
	Bug(BugType eBugType, HyEntity2d *pParent);
	virtual ~Bug();
};

