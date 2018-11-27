#pragma once
#include "pch.h"
#include "FoodStuffs.h"
#include "ContinueButton.h"
#include "CheckBox.h"

#define REVENU_COLORS 58.0f / 255.0f, 221.0f / 255.0f,  32.0f / 255.0f
#define PAY_COLORS 223.0f / 255.0f, 32.0f / 255.0f,  32.0f / 255.0f

class MinusSymbol : public HyEntity2d
{
	HyPrimitive2d	m_Outline;
	HyPrimitive2d	m_Fill;

public:
	MinusSymbol(HyEntity2d *pParent) : HyEntity2d(pParent), m_Outline(this), m_Fill(this)
	{
		m_Outline.GetShape().SetAsLineSegment(glm::vec2(0.0f, 0.0f), glm::vec2(25.0f, 0.0f));
		m_Outline.SetLineThickness(7.0f);
		m_Outline.SetTint(0.0f, 0.0f, 0.0f);

		m_Fill.GetShape().SetAsLineSegment(glm::vec2(3.0f, 0.0f), glm::vec2(19.0f, 0.0f));
		m_Fill.SetLineThickness(3.0f);
		m_Fill.SetTint(PAY_COLORS);
	}
};

class BillsPanel : public IHy9Slice
{
	HySprite2d		m_Scroll;
	HyText2d		m_BillsText;

	FoodStuffs		m_FoodStocks;

	HyText2d		m_Savings;
	HyText2d		m_SavingsVal;

	HyText2d		m_Harvest;
	HyText2d		m_HarvestVal;

	HyText2d		m_Rent;
	HyText2d		m_RentVal;

	HyText2d		m_Vitamins;
	HyText2d		m_VitaminsVal;
	CheckBox		m_VitaminsCheckBox;

	HyText2d		m_AirConditioning;
	HyText2d		m_AirConditioningVal;
	CheckBox		m_AirConditioningCheckBox;

	HyPrimitive2d	m_BarLineOutline;
	HyPrimitive2d	m_BarLine;
	
	HyText2d		m_TotalVal;
	MinusSymbol		m_TotalValMinus;

	ContinueButton	m_ContinueBtn;

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
