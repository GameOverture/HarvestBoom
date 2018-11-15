#include "pch.h"
#include "BillsPanel.h"

BillsPanel::BillsPanel(HyEntity2d *pParent) :	IPanel(pParent),
												m_Scroll("UI", "Bills", this),
												m_BillsText("Game", "Main", this),
												m_FoodStocksBg(this),
												m_FoodStocks(this),
												m_Savings("Game", "Small", this),
												m_SavingsVal("Game", "Small", this),
												m_Harvest("Game", "Small", this),
												m_HarvestVal("Game", "Small", this),
												m_uiHarvestSoldAmt(0),
												m_Rent("Game", "Small", this),
												m_RentVal("Game", "Small", this),
												m_Food("Game", "Small", this),
												m_FoodVal("Game", "Small", this),
												m_AirConditioning("Game", "Small", this),
												m_AirConditioningVal("Game", "Small", this),
												m_BarLineOutline(this),
												m_BarLine(this),
												m_TotalVal("Game", "Small", this),
												m_pContinueBtn(nullptr)
{
}

BillsPanel::~BillsPanel()
{
	delete m_pContinueBtn;
}

#define REVENU_COLORS 58.0f / 255.0f, 221.0f / 255.0f,  32.0f / 255.0f
#define PAY_COLORS 223.0f / 255.0f, 32.0f / 255.0f,  32.0f / 255.0f

void BillsPanel::Construct()
{
	IPanel::Construct();

	m_PanelFill.SetEnabled(false);
	m_PanelFrameOutline.SetEnabled(false);
	m_PanelFrame.SetEnabled(false);

	m_Scroll.scale.Set(2.0f, 2.25f);
	m_Scroll.pos.Set(80.0f, 90.0f);

	const float fTextX = 175.0f;
	const float fTextY = 275.0f;

	m_BillsText.TextSet("Bills");
	m_BillsText.pos.Set(fTextX, 320.0f);
	m_BillsText.SetAsScaleBox(150.0f, 65.0f);

	m_FoodStocks.Construct();
	m_FoodStocks.SetTitle("Click to sell");
	m_FoodStocks.pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	m_FoodStocks.Hide();
	m_Scroll.SetDisplayOrder(m_FoodStocks.GetDisplayOrder() - 1);

	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	m_Savings.TextSet("Savings");
	m_Savings.TextSetState(1);
	m_Savings.TextSetAlignment(HYALIGN_Left);
	m_Savings.pos.Set(fTextX, fTextY);
	m_Savings.alpha.Set(0.0f);

	m_SavingsVal.TextSetState(1);
	m_SavingsVal.TextSetAlignment(HYALIGN_Right);
	m_SavingsVal.pos.Set(vWindowSize.x - fTextX, fTextY);
	m_SavingsVal.alpha.Set(0.0f);

	m_Harvest.TextSet("Harvest");
	m_Harvest.TextSetState(1);
	m_Harvest.TextSetAlignment(HYALIGN_Left);
	m_Harvest.pos.Set(fTextX, fTextY - 25.0f);
	m_Harvest.alpha.Set(0.0f);
	
	m_HarvestVal.TextSetState(1);
	m_HarvestVal.TextSetAlignment(HYALIGN_Right);
	m_HarvestVal.pos.Set(vWindowSize.x - fTextX, fTextY - 25.0f);
	m_HarvestVal.alpha.Set(0.0f);

	m_Rent.TextSet("Rent");
	m_Rent.TextSetLayerColor(0, 1, PAY_COLORS);
	m_Rent.TextSetState(1);
	m_Rent.TextSetAlignment(HYALIGN_Left);
	m_Rent.pos.Set(fTextX, fTextY - 50.0f);
	m_Rent.alpha.Set(0.0f);

	m_RentVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_RentVal.TextSetState(1);
	m_RentVal.TextSetAlignment(HYALIGN_Right);
	m_RentVal.pos.Set(vWindowSize.x - fTextX, fTextY - 50.0f);
	m_RentVal.alpha.Set(0.0f);

	m_Food.TextSet("Food");
	m_Food.TextSetLayerColor(0, 1, PAY_COLORS);
	m_Food.TextSetState(1);
	m_Food.TextSetAlignment(HYALIGN_Left);
	m_Food.pos.Set(fTextX, fTextY - 75.0f);
	m_Food.alpha.Set(0.0f);

	m_FoodVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_FoodVal.TextSetState(1);
	m_FoodVal.TextSetAlignment(HYALIGN_Right);
	m_FoodVal.pos.Set(vWindowSize.x - fTextX, fTextY - 75.0f);
	m_FoodVal.alpha.Set(0.0f);

	m_AirConditioning.TextSet("A/C");
	m_AirConditioning.TextSetLayerColor(0, 1, PAY_COLORS);
	m_AirConditioning.TextSetState(1);
	m_AirConditioning.TextSetAlignment(HYALIGN_Left);
	m_AirConditioning.pos.Set(fTextX, fTextY - 100.0f);
	m_AirConditioning.alpha.Set(0.0f);

	m_AirConditioningVal.TextSetState(1);
	m_AirConditioningVal.TextSetLayerColor(0, 1, PAY_COLORS);
	m_AirConditioningVal.TextSetAlignment(HYALIGN_Right);
	m_AirConditioningVal.pos.Set(vWindowSize.x - fTextX, fTextY - 100.0f);
	m_AirConditioningVal.alpha.Set(0.0f);

	m_BarLineOutline.GetShape().SetAsLineSegment(glm::vec2(fTextX, fTextY - 110.0f), glm::vec2(vWindowSize.x - fTextX, fTextY - 110.0f));
	m_BarLineOutline.SetLineThickness(7.0f);
	m_BarLineOutline.SetTint(0.0f, 0.0f, 0.0f);

	m_BarLine.GetShape().SetAsLineSegment(glm::vec2(fTextX + 2, fTextY - 110.0f), glm::vec2(vWindowSize.x - fTextX - 2, fTextY - 110.0f));
	m_BarLine.SetLineThickness(3.0f);
	m_BarLine.SetTint(0.9f, 0.9f, 0.9f);

	m_TotalVal.TextSetState(1);
	m_TotalVal.TextSetAlignment(HYALIGN_Right);
	m_TotalVal.pos.Set(vWindowSize.x - fTextX, fTextY - 135.0f);
	m_TotalVal.alpha.Set(0.0f);

	Sync();

	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	SetEnabled(true);

	if(m_pContinueBtn == nullptr)
	{
		InfoPanelInit init = {};
		init.panel_LoadPath.Set("Game", "EquipButton");
		init.text_LoadPath.Set("Game", "Small");
		HySetVec(init.text_LocalOffSet, 4, 20);
		HySetVec(init.text_ScaleBox, 70, 35);
		m_pContinueBtn = HY_NEW ContinueButton(init, this);
		m_pContinueBtn->Load();
	}

	m_pContinueBtn->pos.Set(vWindowSize.x, 15);
	m_pContinueBtn->alpha.Set(0.0f);
	m_pContinueBtn->GetTextPtr()->TextSetState(1);
	m_pContinueBtn->GetTextPtr()->TextSet("Sleep");
}

/*virtual*/ void BillsPanel::Show() /*override*/
{
	alpha.Set(1.0f);
	IPanel::Show();
}

void BillsPanel::Hide()
{
	alpha.Tween(0.0f, 1.0f, HyTween::Linear, [this](IHyNode *pThis) { SetEnabled(false); m_bIsShowing = false; });
}

/*virtual*/ void BillsPanel::OnUpdate() /*override*/
{
	if(m_bIsShowing == false)
		return;

	const float fFADEIN_DUR = 0.5f;

	if(m_Savings.alpha.Get() == 0.0f)
	{
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
	if(m_Rent.alpha.Get() == 1.0f && m_Food.alpha.Get() == 0.0f)
	{
		m_Food.alpha.Tween(1.0f, fFADEIN_DUR);
		m_FoodVal.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_Food.alpha.Get() == 1.0f && m_AirConditioning.alpha.Get() == 0.0f)
	{
		m_AirConditioning.alpha.Tween(1.0f, fFADEIN_DUR);
		m_AirConditioningVal.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_AirConditioning.alpha.Get() == 1.0f && m_TotalVal.alpha.Get() == 0.0f)
		m_TotalVal.alpha.Tween(1.0f, fFADEIN_DUR);
	if(m_TotalVal.alpha.Get() == 1.0f && m_FoodStocks.IsShowing() == false && m_FoodStocks.IsTransition() == false)
	{
		m_FoodStocks.Show();
		m_pContinueBtn->pos.Tween(Hy_App().Window().GetWindowSize().x - 100, 15, 1.0f, HyTween::QuadOut);
		m_pContinueBtn->alpha.Set(1.0f);
		m_pContinueBtn->EnableMouseInput(this);
	}
}

void BillsPanel::Sync()
{
	m_FoodStocks.Sync();

	m_SavingsVal.TextSet("$" + std::to_string(Values::Get()->m_iSavings));
	m_HarvestVal.TextSet("$" + std::to_string(m_uiHarvestSoldAmt));
	m_RentVal.TextSet("$" + std::to_string(Values::Get()->m_uiBILLS_RENT));
	m_FoodVal.TextSet("$" + std::to_string(Values::Get()->m_uiBILLS_FOOD));
	m_AirConditioningVal.TextSet("$" + (Values::Get()->m_bAirConditioning ? std::to_string(Values::Get()->m_uiBILLS_AC) : std::to_string(0)));

	int32 iTotal = Values::Get()->m_iSavings;
	iTotal += m_uiHarvestSoldAmt;
	iTotal -= Values::Get()->m_uiBILLS_RENT;
	iTotal -= Values::Get()->m_uiBILLS_FOOD;
	iTotal -= Values::Get()->m_uiBILLS_AC;
	m_TotalVal.TextSet("$" + std::to_string(iTotal));
}
