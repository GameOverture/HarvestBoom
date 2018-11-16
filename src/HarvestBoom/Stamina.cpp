#include "pch.h"
#include "Stamina.h"

Stamina::Stamina(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_fStamina(1.0f),
										m_OuterFrame("UI", "Stamina", this),
										m_Fill("UI", "Stamina", this)
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_UI);
	pos.Set(-100.0f, 50.0f);
}

Stamina::~Stamina()
{
}

/*virtual*/ void Stamina::OnLoaded() /*override*/
{
	m_OuterFrame.AnimSetState(0);
	m_Fill.AnimSetState(1);
	m_Fill.pos.Y(1);

	scale.Set(2.0f, 2.0f);
}

void Stamina::Offset(float fOffset)
{
	Set(m_fStamina + fOffset);
}

void Stamina::Set(float fStaminaAmt)
{
	m_fStamina = fStaminaAmt;
	m_fStamina = HyClamp(m_fStamina, 0.0f, 1.0f);
	m_Fill.scale.Y(m_fStamina);
}
