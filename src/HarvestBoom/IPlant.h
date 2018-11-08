#pragma once
#include "IActor.h"

class IPlant : public IActor
{
	HyPrimitive2d		m_Body;

public:
	IPlant(HyEntity2d *pParent);
	virtual ~IPlant();
};

