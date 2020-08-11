#pragma once
#include "pch.h"
#include "FoodButton.h"

class FoodStuffs : public IHy9Slice
{
	bool					m_bIS_SELLING;
	HyText2d				m_txtTitle;

	FoodButton				m_CornBtn;
	FoodButton				m_EggplantBtn;
	FoodButton				m_PumpkinBtn;

public:
	FoodStuffs(bool bIsSelling, HyEntity2d *pParent);
	virtual ~FoodStuffs();

	void Sync();

	virtual float OnShow() override;
	virtual void OnShown() override;
	virtual float OnHide() override;
	virtual void OnHidden() override;


};
