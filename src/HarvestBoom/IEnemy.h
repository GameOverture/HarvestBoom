#pragma once

class IEnemy : public HyEntity2d
{
	HyPrimitive2d	m_Body;
public:
	IEnemy(HyEntity2d *pParent);
	virtual ~IEnemy();
};

