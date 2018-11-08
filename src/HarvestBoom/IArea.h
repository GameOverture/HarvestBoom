#pragma once

#include "pch.h"

class IArea : public HyEntity2d
{
protected:
	enum Type
	{
		Impassable = 0,
		Structure,
		Dirt,
		Asphalt
	};
	const Type	m_eTYPE;

	glm::ivec2			m_vSize;
	HyPrimitive2d		m_Ground;

public:
	IArea(Type eType, HyEntity2d *pParent);
	virtual ~IArea();

	void SetSize(uint32 uiWidth, uint32 uiHeight);
	void SetPos(int32 iX, int32 iY);
};

