#pragma once
#include "pch.h"
#include "FoodButton.h"

class FoodStuffs : public IHy9Slice
{
	HyText2d				m_txtTitle;

	FoodButton				m_CornIcon;
	HyText2d				m_CornQuantity;

	FoodButton				m_EggplantIcon;
	HyText2d				m_EggplantQuantity;

	FoodButton				m_PumpkinIcon;
	HyText2d				m_PumpkinQuantity;

public:
	FoodStuffs(bool bIsSelling, HyEntity2d *pParent);
	virtual ~FoodStuffs();

	void SetTitle(std::string sTitle);

	void Sync();

	virtual float OnShow() override;
	virtual void OnShown() override;
	virtual float OnHide() override;
	virtual void OnHidden() override;


};
