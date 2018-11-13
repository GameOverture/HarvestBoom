#pragma once
#include "IPanel.h"
#include "FoodStocks.h"

class HousePanel : public IPanel
{
	FoodStocks		m_FoodStocks;

	HyText2d		m_Savings;
	HyText2d		m_SavingsVal;

public:
	HousePanel(HyEntity2d *pParent);
	virtual ~HousePanel();

	virtual void Construct() override;

	virtual void Show() override;
	virtual void Hide() override;
	virtual bool IsTransition() override;
};
