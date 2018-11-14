#pragma once

class Hoe : public HyEntity2d
{
	HyPrimitive2d		m_Staff;

public:
	Hoe(HyEntity2d *pParent);
	virtual ~Hoe();
};

