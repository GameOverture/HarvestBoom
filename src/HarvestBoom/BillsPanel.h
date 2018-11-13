#pragma once
#include "pch.h"

#include "IPanel.h"
#include "FoodStocks.h"

class BillsPanel : public IPanel
{
	FoodStocks		m_FoodStocks;

	HyText2d		m_Savings;
	HyText2d		m_SavingsVal;

	HyText2d		m_Harvest;
	HyText2d		m_HarvestVal;

	HyText2d		m_Rent;
	HyText2d		m_RentVal;

	HyText2d		m_Food;
	HyText2d		m_FoodVal;

	HyText2d		m_Heat;
	HyText2d		m_HeatVal;

	HyPrimitive2d	m_BarLine;
	HyText2d		m_TotalVal;

public:
	BillsPanel(HyEntity2d *pParent);
	virtual ~BillsPanel();

	virtual void Construct() override;

	virtual void OnUpdate() override;
};
