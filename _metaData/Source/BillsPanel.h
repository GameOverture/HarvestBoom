#pragma once
#include "pch.h"
#include "FoodStuffs.h"
#include "ContinueButton.h"
#include "CheckBox.h"

#define REVENU_COLORS 58.0f / 255.0f, 221.0f / 255.0f,  32.0f / 255.0f
#define PAY_COLORS 223.0f / 255.0f, 32.0f / 255.0f,  32.0f / 255.0f

#define MINUS_WIDTH 18.0f

class MinusSymbol : public HyEntity2d
{
	HyPrimitive2d	m_Outline;
	HyPrimitive2d	m_Fill;

public:
	MinusSymbol(HyEntity2d *pParent) : HyEntity2d(pParent), m_Outline(this), m_Fill(this)
	{
		m_Outline.shape.SetAsLineSegment(glm::vec2(0.0f, 0.0f), glm::vec2(MINUS_WIDTH, 0.0f));
		m_Outline.SetLineThickness(7.0f);
		m_Outline.SetTint(HyColor::Black);

		m_Fill.shape.SetAsLineSegment(glm::vec2(2.0f, 0.0f), glm::vec2(MINUS_WIDTH - 2.0f, 0.0f));
		m_Fill.SetLineThickness(3.0f);
		m_Fill.SetTint(HyColor(PAY_COLORS));
	}
};

class BillsPanel : public HyUiContainer
{
	HyLabel			m_BillsText;

	FoodStuffs		m_FoodStocks;

	HyLabel			m_Savings;
	HyLabel			m_SavingsVal;

	HyLabel			m_Harvest;
	HyLabel			m_HarvestVal;

	HyLabel			m_Rent;
	HyLabel			m_RentVal;

	HyLabel			m_Damage;
	HyLabel			m_DamageVal;

	HyLabel			m_Vitamins;
	HyLabel			m_VitaminsVal;
	HyCheckBox		m_VitaminsCheckBox;

	HyLabel			m_AirConditioning;
	HyLabel			m_AirConditioningVal;
	HyCheckBox		m_AirConditioningCheckBox;

	HyPrimitive2d	m_BarLineOutline;
	HyPrimitive2d	m_BarLine;
	
	HyLabel			m_TotalVal;
	MinusSymbol		m_TotalValMinus;

	HyButton		m_ContinueBtn;

public:
	BillsPanel(HyEntity2d *pParent);
	virtual ~BillsPanel();

	int32 CalculateMoney();
	void Sync();

protected:
	virtual void OnContainerUpdate() override;

	virtual float OnBeginShow() override;
	virtual void OnShown() override;
	virtual float OnBeginHide() override;
	virtual void OnHidden() override;
};
