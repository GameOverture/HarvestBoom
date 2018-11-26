#include "pch.h"
#include "Stamina.h"

Stamina::Stamina(HyEntity2d *pParent) :
	HyEntity2d(pParent),
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

void Stamina::Sync()
{
	Set(Values::Get()->m_fStamina);
}

/*virtual*/ void Stamina::OnLoaded() /*override*/
{
	m_OuterFrame.AnimSetState(0);
	m_Fill.AnimSetState(1);
	m_Fill.pos.Set(2.0f, 9.0f);
}

void Stamina::Offset(float fOffset)
{
	Set(Values::Get()->m_fStamina + fOffset);
}

void Stamina::Set(float fStaminaAmt)
{
	Values::Get()->m_fStamina = fStaminaAmt;
	Values::Get()->m_fStamina = HyClamp(Values::Get()->m_fStamina, 0.0f, 1.0f);
	m_Fill.scale.Y(Values::Get()->m_fStamina);
}
