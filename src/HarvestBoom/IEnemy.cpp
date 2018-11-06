#include "pch.h"
#include "IEnemy.h"

IEnemy::IEnemy(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_Body(this)
{
	m_Body.GetShape().SetAsBox(10.0f, 10.0f);
	m_Body.topColor.Set(1.0f, 0.0f, 0.0);

	SetDisplayOrder(DISPLAYORDER_Object);
}

IEnemy::~IEnemy()
{
}
