#include "pch.h"
#include "BillsPanel.h"
#include "HarvestBoom.h"

extern HyWindow &Hy_Window();

BillsPanel::BillsPanel(HyEntity2d *pParent) :
	IHy9Slice(glm::vec2(Hy_Window().GetWidth(), Hy_Window().GetHeight()), 10, pParent),
	m_Scroll("UI", "Bills", this),
	m_BillsText("Game", "Main", this),
	m_FoodStocks(true, this),
	m_Savings("Game", "Small", this),
	m_SavingsVal("Game", "Small", this),
	m_Harvest("Game", "Small", this),
	m_HarvestVal("Game", "Small", this),
	m_Rent("Game", "Small", this),
	m_RentVal("Game", "Small", this),
	m_Damage("Game", "Small", this),
	m_DamageVal("Game", "Small", this),
	m_Vitamins("Game", "Small", this),
	m_VitaminsVal("Game", "Small", this),
	m_VitaminsCheckBox(true, this),
	m_AirConditioning("Game", "Small", this),
	m_AirConditioningVal("Game", "Small", this),
	m_AirConditioningCheckBox(false, this),
	m_BarLineOutline(this),
	m_BarLine(this),
	m_TotalVal("Game", "Small", this),
	m_TotalValMinus(this),
	m_ContinueBtn(this)
{
	m_Scroll.scale.Set(2.0f, 2.25f);
	m_Scroll.pos.Set(80.0f, 90.0f);

	glm::ivec2 vWindowSize = Hy_Window().GetWindowSize();
	const float fTextX = 175.0f;
	const float fTextY = 287.0f;

	m_BillsText.TextSet("Bills");
	m_BillsText.TextSetAlignment(HYALIGN_Center);
	m_BillsText.pos.Set(fTextX, 320.0f);
	m_BillsText.SetAsScaleBox(vWindowSize.x - (fTextX * 2), 65.0f);

	m_FoodStocks.pos.Set(-m_FoodStocks.GetWidth(true), 10.0f);
	m_FoodStocks.Hide();
	
	m_Savings.TextSet("Savings");
	m_Savings.TextSetState(1);
	m_Savings.TextSetAlignment(HYALIGN_Left);
	m_Savings.pos.Set(fTextX, fTextY);

	m_SavingsVal.TextSetState(1);
	m_SavingsVal.TextSetAlignment(HYALIGN_Right);
	m_SavingsVal.pos.Set(vWindowSize.x - fTextX, fTextY);

	m_Harvest.TextSet("Harvest");
	m_Harvest.TextSetState(1);
	m_Harvest.TextSetAlignment(HYALIGN_Left);
	m_Harvest.pos.Set(fTextX, fTextY - 25.0f);
	
	m_HarvestVal.TextSetState(1);
	m_HarvestVal.TextSetAlignment(HYALIGN_Right);
	m_HarvestVal.pos.Set(vWindowSize.x - fTextX, fTextY - 25.0f);

	m_Rent.TextSet("Rent");
	m_Rent.TextSetLayerColor(0, 1, PAY_COLORS);
	m_Rent.TextSetState(1);
	m_Rent.TextSetAlignment(HYALIGN_Left);
	m_Rent.pos.Set(fTextX, fTextY - 50.0f);

	m_RentVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_RentVal.TextSetState(1);
	m_RentVal.TextSetAlignment(HYALIGN_Right);
	m_RentVal.pos.Set(vWindowSize.x - fTextX, fTextY - 50.0f);

	m_Vitamins.TextSet("Vitamins");
	m_Vitamins.TextSetLayerColor(0, 1, PAY_COLORS);
	m_Vitamins.TextSetState(1);
	m_Vitamins.TextSetAlignment(HYALIGN_Left);
	m_Vitamins.pos.Set(fTextX, fTextY - 75.0f);

	m_VitaminsVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_VitaminsVal.TextSetState(1);
	m_VitaminsVal.TextSetAlignment(HYALIGN_Right);
	m_VitaminsVal.pos.Set(vWindowSize.x - fTextX, fTextY - 75.0f);

	m_VitaminsCheckBox.pos.Set(m_VitaminsVal.pos.X(), fTextY - 75.0f);
	m_VitaminsCheckBox.pos.Offset(5.0f, -2.0f);

	m_AirConditioning.TextSet("A/C");
	m_AirConditioning.TextSetLayerColor(0, 1, PAY_COLORS);
	m_AirConditioning.TextSetState(1);
	m_AirConditioning.TextSetAlignment(HYALIGN_Left);
	m_AirConditioning.pos.Set(fTextX, fTextY - 100.0f);

	m_AirConditioningVal.TextSetState(1);
	m_AirConditioningVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_AirConditioningVal.TextSetAlignment(HYALIGN_Right);
	m_AirConditioningVal.pos.Set(vWindowSize.x - fTextX, fTextY - 100.0f);

	m_AirConditioningCheckBox.pos.Set(m_AirConditioningVal.pos.X(), fTextY - 100.0f);
	m_AirConditioningCheckBox.pos.Offset(5.0f, -2.0f);

	m_Damage.TextSet("Bug Damages");
	m_Damage.TextSetLayerColor(0, 1, PAY_COLORS);
	m_Damage.TextSetState(1);
	m_Damage.TextSetAlignment(HYALIGN_Left);
	m_Damage.pos.Set(fTextX, fTextY - 125.0f);

	m_DamageVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_DamageVal.TextSetState(1);
	m_DamageVal.TextSetAlignment(HYALIGN_Right);
	m_DamageVal.pos.Set(vWindowSize.x - fTextX, fTextY - 125.0f);

	m_BarLineOutline.SetAsLineSegment(glm::vec2(fTextX, fTextY - 110.0f), glm::vec2(vWindowSize.x - fTextX, fTextY - 110.0f));
	m_BarLineOutline.SetLineThickness(7.0f);
	m_BarLineOutline.SetTint(0.0f, 0.0f, 0.0f);

	m_BarLine.SetAsLineSegment(glm::vec2(fTextX + 2, fTextY - 110.0f), glm::vec2(vWindowSize.x - fTextX - 2, fTextY - 110.0f));
	m_BarLine.SetLineThickness(3.0f);
	m_BarLine.SetTint(0.9f, 0.9f, 0.9f);

	m_TotalVal.TextSetState(1);
	m_TotalVal.TextSetAlignment(HYALIGN_Right);

	m_ContinueBtn.GetTextPtr()->TextSetState(1);

	Sync();

	GetBorder().SetVisible(false);
	GetFill().SetVisible(false);

	SetDisplayOrder(DISPLAYORDER_Panel);
}

BillsPanel::~BillsPanel()
{
}

/*virtual*/ float BillsPanel::OnShow() /*override*/
{
	alpha.Set(1.0f);
	m_Savings.alpha.Set(0.0f);
	m_SavingsVal.alpha.Set(0.0f);
	m_Harvest.alpha.Set(0.0f);
	m_HarvestVal.alpha.Set(0.0f);
	m_Rent.alpha.Set(0.0f);
	m_RentVal.alpha.Set(0.0f);
	m_Vitamins.alpha.Set(0.0f);
	m_VitaminsVal.alpha.Set(0.0f);
	m_VitaminsCheckBox.alpha.Set(0.0f);
	m_AirConditioning.alpha.Set(0.0f);
	m_AirConditioningVal.alpha.Set(0.0f);
	m_AirConditioningCheckBox.alpha.Set(0.0f);
	m_Damage.alpha.Set(0.0f);
	m_DamageVal.alpha.Set(0.0f);
	m_TotalVal.alpha.Set(0.0f);
	m_TotalValMinus.alpha.Set(0.0f);

#define BARLINE_YPOS_NODMG 110.0f
#define BARLINE_YPOS_YESDMG 135.0f

#define TOTALVAL_YPOS_NODMG 135.0f
#define TOTALVAL_YPOS_YESDMG 160.0f

	glm::ivec2 vWindowSize = Hy_Window().GetWindowSize();
	const float fTextX = 175.0f;
	const float fTextY = 287.0f;

	if(Values::Get()->m_uiDamageCost != 0.0f)
	{
		m_BarLineOutline.pos.Y(-25.0f);
		m_BarLine.pos.Y(-25.0f);
	}
	else
	{
		m_BarLineOutline.pos.Y(0.0f);
		m_BarLine.pos.Y(0.0f);
	}

	m_TotalVal.pos.Set(vWindowSize.x - fTextX, fTextY - (Values::Get()->m_uiDamageCost == 0.0f ? TOTALVAL_YPOS_NODMG : TOTALVAL_YPOS_YESDMG));
	m_TotalValMinus.pos.Y(m_TotalVal.pos.Y() + 5.0f);

	pos.Set(-GetWidth(true), 0.0f);
	pos.Tween(0.0f, 0.0f, 1.0f, HyTween::QuadOut);

	m_FoodStocks.pos.Set(-m_FoodStocks.GetWidth(true), 10.0f);
	m_FoodStocks.Hide();
	Sync();

	m_ContinueBtn.pos.Set(Hy_Window().GetWidth(), 15);
	m_ContinueBtn.alpha.Set(0.0f);

	return 1.0f;
}

/*virtual*/ void BillsPanel::OnShown() /*override*/
{
	m_VitaminsCheckBox.EnableMouseInput();
	m_AirConditioningCheckBox.EnableMouseInput();
}

/*virtual*/ float BillsPanel::OnHide() /*override*/
{
	m_VitaminsCheckBox.DisableMouseInput();
	Values::Get()->m_bVitaminStrength = m_VitaminsCheckBox.IsChecked();

	m_AirConditioningCheckBox.DisableMouseInput();
	Values::Get()->m_bAirConditioning = m_AirConditioningCheckBox.IsChecked();

	alpha.Tween(0.0f, 1.0f, HyTween::Linear);
	return 1.0f;
}

/*virtual*/ void BillsPanel::OnHidden() /*override*/
{
	Values::Get()->m_iSavings = CalculateMoney();
	Values::Get()->m_uiHarvestSoldAmt = 0;
	Values::Get()->m_uiDamageCost = 0;
}

/*virtual*/ void BillsPanel::OnUpdate() /*override*/
{
	IHy9Slice::OnUpdate();

	if(IsShown() == false)
		return;

	const float fFADEIN_DUR = 0.5f;

	if(m_Savings.alpha.Get() == 0.0f)
	{
		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_SRCIBBLE_LONG);
		m_Savings.alpha.Tween(1.0f, fFADEIN_DUR);
		m_SavingsVal.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_Savings.alpha.Get() == 1.0f && m_Harvest.alpha.Get() == 0.0f)
	{
		m_Harvest.alpha.Tween(1.0f, fFADEIN_DUR);
		m_HarvestVal.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_Harvest.alpha.Get() == 1.0f && m_Rent.alpha.Get() == 0.0f)
	{
		m_Rent.alpha.Tween(1.0f, fFADEIN_DUR);
		m_RentVal.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_Rent.alpha.Get() == 1.0f && m_Vitamins.alpha.Get() == 0.0f)
	{
		m_Vitamins.alpha.Tween(1.0f, fFADEIN_DUR);
		m_VitaminsVal.alpha.Tween(1.0f, fFADEIN_DUR);
		m_VitaminsCheckBox.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_Vitamins.alpha.Get() == 1.0f && m_AirConditioning.alpha.Get() == 0.0f)
	{
		m_AirConditioning.alpha.Tween(1.0f, fFADEIN_DUR);
		m_AirConditioningVal.alpha.Tween(1.0f, fFADEIN_DUR);
		m_AirConditioningCheckBox.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_AirConditioning.alpha.Get() == 1.0f && m_TotalVal.alpha.Get() == 0.0f)
	{
		if(Values::Get()->m_uiDamageCost != 0.0f)
		{
			m_Damage.alpha.Tween(1.0f, fFADEIN_DUR);
			m_DamageVal.alpha.Tween(1.0f, fFADEIN_DUR);
		}

		m_TotalVal.alpha.Tween(1.0f, fFADEIN_DUR);

		if(CalculateMoney() < 0)
			m_TotalValMinus.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_TotalVal.alpha.Get() == 1.0f && m_FoodStocks.Show())
	{
		m_FoodStocks.pos.Set(-m_FoodStocks.GetWidth(true), 10.0f);
		if(Values::Get()->m_uiHarvestCorn > 0 || Values::Get()->m_uiHarvestEggplant > 0 || Values::Get()->m_uiHarvestPumpkin > 0)
			m_FoodStocks.pos.Tween(10.0f, 10.0f, 1.0f, HyTween::QuadOut);

		m_ContinueBtn.pos.Tween(Hy_Window().GetWindowSize().x - 100, 15, 1.0f, HyTween::QuadOut);
		m_ContinueBtn.alpha.Set(1.0f);
		m_ContinueBtn.EnableMouseInput();
	}
}

int32 BillsPanel::CalculateMoney()
{
	int32 iTotal = Values::Get()->m_iSavings;
	iTotal += Values::Get()->m_uiHarvestSoldAmt;
	iTotal -= Values::Get()->m_uiBILLS_RENT;
	
	if(m_VitaminsCheckBox.IsChecked())
		iTotal -= Values::Get()->m_uiBILLS_VITAMINS;

	if(m_AirConditioningCheckBox.IsChecked())
		iTotal -= Values::Get()->m_uiBILLS_AC;

	iTotal -= Values::Get()->m_uiDamageCost;

	return iTotal;
}

void BillsPanel::Sync()
{
	m_FoodStocks.Sync();

	m_VitaminsCheckBox.Sync();
	m_AirConditioningCheckBox.Sync();

	m_SavingsVal.TextSet("$" + std::to_string(Values::Get()->m_iSavings));
	m_HarvestVal.TextSet("$" + std::to_string(Values::Get()->m_uiHarvestSoldAmt));
	m_RentVal.TextSet("$" + std::to_string(Values::Get()->m_uiBILLS_RENT));
	m_VitaminsVal.TextSet("$" + std::to_string(Values::Get()->m_uiBILLS_VITAMINS));
	m_AirConditioningVal.TextSet("$" + std::to_string(Values::Get()->m_uiBILLS_AC));
	m_DamageVal.TextSet("$" + std::to_string(Values::Get()->m_uiDamageCost));

	int32 iTotalMonies = CalculateMoney();
	m_TotalVal.TextSet("$" + std::to_string(abs(iTotalMonies)));
	m_TotalValMinus.pos.X(m_TotalVal.pos.X() - m_TotalVal.TextGetPixelWidth() - MINUS_WIDTH - 2.0f);

	if(IsShown())
		m_TotalValMinus.alpha.Set((iTotalMonies < 0) ? 1.0f : 0.0f);

	if(iTotalMonies < 0)
	{
		m_TotalVal.TextSetLayerColor(0, 1, PAY_COLORS);
		m_ContinueBtn.GetTextPtr()->TextSet("Go\nBankrupt");
		m_ContinueBtn.GetPanelPtr()->SetTint(1.0f, 0.0f, 0.0f);
	}
	else
	{
		if(Values::Get()->m_uiCurrentDay < Values::Get()->m_uiNUM_DAYS_TO_WIN)
		{
			m_TotalVal.TextSetLayerColor(0, 1, 1.0f, 1.0f, 1.0f);
			m_ContinueBtn.GetTextPtr()->TextSet("Sleep");
			m_ContinueBtn.GetPanelPtr()->SetTint(1.0f, 1.0f, 1.0f);
		}
		else
		{
			m_TotalVal.TextSetLayerColor(0, 1, 1.0f, 1.0f, 1.0f);
			m_ContinueBtn.GetTextPtr()->TextSet("Win Game!");
			m_ContinueBtn.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);
		}
	}
}
