#pragma once
#include "pch.h"

class Stamina : public HyEntity2d
{
	HySprite2d			m_OuterFrame;
	HySprite2d			m_Fill;

public:
	Stamina(HyEntity2d *pParent);
	virtual ~Stamina();

	virtual void Stamina::OnLoaded() override;

	void Offset(float fOffset);
	void Set(float fStaminaAmt);
};
