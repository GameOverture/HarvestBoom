#pragma once
#include "pch.h"

class FoodStocks : public HyEntity2d
{
	HyText2d				m_txtTitle;

	HySprite2d				m_CornStock;
	HySprite2d				m_EggplantStock;
	HySprite2d				m_PumpkinStock;
	HyText2d				m_txtCorn;
	HyText2d				m_txtEggplant;
	HyText2d				m_txtPumpkin;

public:
	FoodStocks(HyEntity2d *pParent);
	virtual ~FoodStocks();

	void Construct();

	void Sync();
};
