#pragma once
#include "pch.h"

#include "IPanel.h"
#include "FoodStuffs.h"

class BillsPanel : public IPanel
{
	HySprite2d		m_Scroll;
	HyText2d		m_BillsText;

	HyPrimitive2d	m_FoodStocksBg;
	FoodStuffs		m_FoodStocks;

	HyText2d		m_Savings;
	HyText2d		m_SavingsVal;

	HyText2d		m_Harvest;
	HyText2d		m_HarvestVal;
	uint32			m_uiHarvestSoldAmt;

	HyText2d		m_Rent;
	HyText2d		m_RentVal;

	HyText2d		m_Food;
	HyText2d		m_FoodVal;

	HyText2d		m_AirConditioning;
	HyText2d		m_AirConditioningVal;

	HyPrimitive2d	m_BarLineOutline;
	HyPrimitive2d	m_BarLine;
	HyText2d		m_TotalVal;

public:
	BillsPanel(HyEntity2d *pParent);
	virtual ~BillsPanel();

	virtual void Construct() override;
	virtual void Show() override;

	virtual void OnUpdate() override;

	void Sync();
};
