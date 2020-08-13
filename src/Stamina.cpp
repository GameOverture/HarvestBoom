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

	Reset();
}

Stamina::~Stamina()
{
}

void Stamina::Sync()
{
	if(Values::Get()->m_bVitaminStrength)
		m_Fill.SetTint(1.0f, 1.0f, 1.0f);
	else
		m_Fill.SetTint(1.0f, 0.0f, 0.0f);

	Set(Values::Get()->m_fStamina);
}

/*virtual*/ void Stamina::OnLoaded() /*override*/
{
	m_OuterFrame.AnimSetState(0);
	m_Fill.AnimSetState(1);
}

void Stamina::Offset(float fOffset)
{
	Set(Values::Get()->m_fStamina + fOffset);
}

void Stamina::Reset()
{
	Set(1.0f);
	Sync();
}

void Stamina::Set(float fStaminaAmt)
{
	Values::Get()->m_fStamina = fStaminaAmt;
	Values::Get()->m_fStamina = HyClamp(Values::Get()->m_fStamina, 0.0f, 1.0f);
	m_Fill.scale.Y(Values::Get()->m_fStamina);
}
