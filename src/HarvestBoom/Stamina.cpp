#include "pch.h"
#include "Stamina.h"

#define STAMINA_STROKE_AMT 4
#define STAMINA_BAR_WIDTH 50
#define STAMINA_BAR_HEIGHT 250

Stamina::Stamina(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_fStamina(1.0f),
										m_OuterFrame(this),
										m_Fill(this)
{
	UseWindowCoordinates();

	m_OuterFrame.GetShape().SetAsBox(STAMINA_BAR_WIDTH, STAMINA_BAR_HEIGHT);
	m_OuterFrame.topColor.Set(0.0f, 0.0f, 0.0f);

	m_Fill.GetShape().SetAsBox(STAMINA_BAR_WIDTH - (STAMINA_STROKE_AMT * 2), STAMINA_BAR_HEIGHT - (STAMINA_STROKE_AMT * 2));
	m_Fill.pos.Offset(STAMINA_STROKE_AMT, STAMINA_STROKE_AMT);
	m_Fill.topColor.Set(0.0f, 0.8f, 0.0f);
}

Stamina::~Stamina()
{
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
