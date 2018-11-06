#include "pch.h"
#include "IArea.h"


IArea::IArea(Type eType, HyEntity2d *pParent) :	HyEntity2d(pParent),
												m_eTYPE(eType),
												m_Ground(this)
{
	switch(m_eTYPE)
	{
	case Impassable:
		m_Ground.topColor.Set(0.6f, 0.8f, 0.196078f);
		SetDisplayOrder(DISPLAYORDER_Impassable);
		break;
	case Structure:
		m_Ground.topColor.Set(0.623529f, 0.623529f, 0.372549f);
		SetDisplayOrder(DISPLAYORDER_Structure);
		break;
	case Dirt:
		m_Ground.topColor.Set(0.647059f, 0.164706f, 0.164706f);
		SetDisplayOrder(DISPLAYORDER_Dirt);
		break;
	case Asphalt:
		m_Ground.topColor.Set(0.184314f, 0.309804f, 0.309804f);
		SetDisplayOrder(DISPLAYORDER_Asphalt);
		break;
	}
}

IArea::~IArea()
{
}

void IArea::SetSize(uint32 uiWidth, uint32 uiHeight)
{
	m_vSize.x = uiWidth;
	m_vSize.y = uiHeight;
	m_Ground.GetShape().SetAsBox(uiWidth, uiHeight);
}
