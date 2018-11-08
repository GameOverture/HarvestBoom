#pragma once
#include "IActor.h"

class IEnemy : public IActor
{
	HyPrimitive2d	m_Body;
public:
	IEnemy(HyEntity2d *pParent);
	virtual ~IEnemy();
};

