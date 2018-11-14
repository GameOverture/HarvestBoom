#pragma once
#include "pch.h"

class Stamina : public HyEntity2d
{
	float				m_fStamina;

	HyPrimitive2d		m_OuterFrame;
	HyPrimitive2d		m_Fill;

public:
	Stamina(HyEntity2d *pParent);
	virtual ~Stamina();

	void Offset(float fOffset);
	void Set(float fStaminaAmt);
};
