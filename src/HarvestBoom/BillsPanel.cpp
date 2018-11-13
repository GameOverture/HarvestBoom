#include "pch.h"
#include "BillsPanel.h"

BillsPanel::BillsPanel(HyEntity2d *pParent) :	IPanel(pParent),
												m_FoodStocks(this),
												m_Savings("Game", "Small", this),
												m_SavingsVal("Game", "Small", this),
												m_Harvest("Game", "Small", this),
												m_HarvestVal("Game", "Small", this),
												m_Rent("Game", "Small", this),
												m_RentVal("Game", "Small", this),
												m_Food("Game", "Small", this),
												m_FoodVal("Game", "Small", this),
												m_Heat("Game", "Small", this),
												m_HeatVal("Game", "Small", this),
												m_BarLine(this),
												m_TotalVal("Game", "Small", this)
{
}

BillsPanel::~BillsPanel()
{
}

void BillsPanel::Construct()
{
	IPanel::Construct();
	
	m_FoodStocks.Construct();
	m_FoodStocks.pos.Set(m_ptFrameVerts[1].x + 30.0f, m_ptFrameVerts[1].y - 140.0f);

	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	m_Savings.TextSet("Savings");
	m_Savings.TextSetState(1);
	m_Savings.TextSetAlignment(HYALIGN_Left);
	m_Savings.pos.Set(100.0f, vWindowSize.y * 0.5f);
	m_Savings.alpha.Set(0.0f);
	m_SavingsVal.TextSet("$45");
	m_SavingsVal.TextSetState(1);
	m_SavingsVal.TextSetAlignment(HYALIGN_Right);
	m_SavingsVal.pos.Set(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f);
	m_SavingsVal.alpha.Set(0.0f);

	m_Harvest.TextSet("Harvest");
	m_Harvest.TextSetState(1);
	m_Harvest.TextSetAlignment(HYALIGN_Left);
	m_Harvest.pos.Set(100.0f, vWindowSize.y * 0.5f - 25.0f);
	m_Harvest.alpha.Set(0.0f);
	m_HarvestVal.TextSet("$10");
	m_HarvestVal.TextSetState(1);
	m_HarvestVal.TextSetAlignment(HYALIGN_Right);
	m_HarvestVal.pos.Set(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f - 25.0f);
	m_HarvestVal.alpha.Set(0.0f);

	m_Rent.TextSet("Rent");
	m_Rent.TextSetState(1);
	m_Rent.TextSetAlignment(HYALIGN_Left);
	m_Rent.pos.Set(100.0f, vWindowSize.y * 0.5f - 50.0f);
	m_Rent.alpha.Set(0.0f);
	m_RentVal.TextSet("$30");
	m_RentVal.TextSetState(1);
	m_RentVal.TextSetAlignment(HYALIGN_Right);
	m_RentVal.pos.Set(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f - 50.0f);
	m_RentVal.alpha.Set(0.0f);

	m_Food.TextSet("Food");
	m_Food.TextSetState(1);
	m_Food.TextSetAlignment(HYALIGN_Left);
	m_Food.pos.Set(100.0f, vWindowSize.y * 0.5f - 75.0f);
	m_Food.alpha.Set(0.0f);
	m_FoodVal.TextSet("$25");
	m_FoodVal.TextSetState(1);
	m_FoodVal.TextSetAlignment(HYALIGN_Right);
	m_FoodVal.pos.Set(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f - 75.0f);
	m_FoodVal.alpha.Set(0.0f);

	m_Heat.TextSet("Heat");
	m_Heat.TextSetState(1);
	m_Heat.TextSetAlignment(HYALIGN_Left);
	m_Heat.pos.Set(100.0f, vWindowSize.y * 0.5f - 100.0f);
	m_Heat.alpha.Set(0.0f);
	m_HeatVal.TextSet("$10");
	m_HeatVal.TextSetState(1);
	m_HeatVal.TextSetAlignment(HYALIGN_Right);
	m_HeatVal.pos.Set(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f - 100.0f);
	m_HeatVal.alpha.Set(0.0f);

	m_BarLine.GetShape().SetAsLineSegment(glm::vec2(100.0f, vWindowSize.y * 0.5f - 110.0f), glm::vec2(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f - 110.0f));
	m_BarLine.SetLineThickness(5.0f);

	m_TotalVal.TextSet("$45");
	m_TotalVal.TextSetState(1);
	m_TotalVal.TextSetAlignment(HYALIGN_Right);
	m_TotalVal.pos.Set(vWindowSize.x - 100.0f, vWindowSize.y * 0.5f - 135.0f);
	m_TotalVal.alpha.Set(0.0f);

	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	SetEnabled(true);
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
	if(m_Food.alpha.Get() == 1.0f && m_Heat.alpha.Get() == 0.0f)
	{
		m_Heat.alpha.Tween(1.0f, fFADEIN_DUR);
		m_HeatVal.alpha.Tween(1.0f, fFADEIN_DUR);
	}
	if(m_Heat.alpha.Get() == 1.0f && m_TotalVal.alpha.Get() == 0.0f)
		m_TotalVal.alpha.Tween(1.0f, fFADEIN_DUR);
}
