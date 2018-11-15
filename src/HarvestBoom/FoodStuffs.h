#pragma once
#include "pch.h"
#include "IPanel.h"

class FoodStuffs : public IPanel
{
	HyText2d				m_txtTitle;

	HySprite2d				m_CornIcon;
	HyText2d				m_CornQuantity;

	HySprite2d				m_EggplantIcon;
	HyText2d				m_EggplantQuantity;

	HySprite2d				m_PumpkinIcon;
	HyText2d				m_PumpkinQuantity;

public:
	FoodStuffs(HyEntity2d *pParent);
	virtual ~FoodStuffs();

	void Construct();

	void SetTitle(std::string sTitle);

	void Sync();
};
