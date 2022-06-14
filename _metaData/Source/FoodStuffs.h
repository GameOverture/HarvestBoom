#pragma once
#include "pch.h"
#include "FoodButton.h"

class FoodStuffs : public HyUiContainer
{
	bool					m_bIS_SELLING;
	HyLabel					m_Title;

	FoodButton				m_CornBtn;
	FoodButton				m_EggplantBtn;
	FoodButton				m_PumpkinBtn;

public:
	FoodStuffs(bool bIsSelling, HyEntity2d *pParent);
	virtual ~FoodStuffs();

	void Sync();
};
