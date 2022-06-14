#pragma once
#include "pch.h"

class Stamina : public HyEntity2d
{
	HySprite2d			m_OuterFrame;
	HySprite2d			m_Fill;

public:
	Stamina(HyEntity2d *pParent);
	virtual ~Stamina();

	void Sync();

	virtual void OnLoaded() override;

	void Offset(float fOffset);
	void Reset();

private:
	void Set(float fStaminaAmt);
};
