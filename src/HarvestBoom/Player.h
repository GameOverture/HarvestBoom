#pragma once
#include "pch.h"

class Player : public HyEntity2d
{
	HyPrimitive2d	m_Body;

public:
	Player(HyEntity2d *pParent);
	virtual ~Player();
};
