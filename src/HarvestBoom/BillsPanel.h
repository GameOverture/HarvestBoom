#pragma once
#include "pch.h"
#include "FoodStuffs.h"
#include "ContinueButton.h"

class BillsPanel : public IHy9Slice
{
	HySprite2d		m_Scroll;
	HyText2d		m_BillsText;

	HyPrimitive2d	m_FoodStocksBg;
	FoodStuffs		m_FoodStocks;

	HyText2d		m_Savings;
	HyText2d		m_SavingsVal;

	HyText2d		m_Harvest;
	HyText2d		m_HarvestVal;

	HyText2d		m_Rent;
	HyText2d		m_RentVal;

	HyText2d		m_Food;
	HyText2d		m_FoodVal;

	HyText2d		m_AirConditioning;
	HyText2d		m_AirConditioningVal;

	HyPrimitive2d	m_BarLineOutline;
	HyPrimitive2d	m_BarLine;
	HyText2d		m_TotalVal;

	ContinueButton *m_pContinueBtn;

public:
	BillsPanel(HyEntity2d *pParent);
	virtual ~BillsPanel();

	virtual float OnShow() override;
	virtual void OnShown() override;
	virtual float OnHide() override;
	virtual void OnHidden() override;

	virtual void OnUpdate() override;

	int32 CalculateMoney();
	void Sync();
};
