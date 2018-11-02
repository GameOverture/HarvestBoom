#pragma once

class IPlant : public HyEntity2d
{
	HyPrimitive2d		m_Body;

public:
	IPlant(HyEntity2d *pParent);
	virtual ~IPlant();
};

