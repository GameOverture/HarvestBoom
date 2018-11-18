#pragma once
#include "pch.h"

class FoodStuffs : public IHy9Slice
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

	void SetTitle(std::string sTitle);

	void Sync();

	virtual float OnShow() override;
	virtual void OnShown() override;
	virtual float OnHide() override;
	virtual void OnHidden() override;
};
