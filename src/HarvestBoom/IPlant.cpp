#include "pch.h"
#include "IPlant.h"


IPlant::IPlant(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_Body(this)
{
	m_Body.GetShape().SetAsBox(12.0f, 30.0f);
	m_Body.topColor.Set(0.0f, 1.0f, 0.0f);

	SetDisplayOrder(DISPLAYORDER_Object);
}

IPlant::~IPlant()
{
}
