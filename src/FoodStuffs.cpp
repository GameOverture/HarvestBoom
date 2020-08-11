#include "pch.h"
#include "FoodStuffs.h"
#include "BillsPanel.h"

FoodStuffs::FoodStuffs(bool bIsSelling, HyEntity2d *pParent) :
	IHy9Slice(glm::vec2(160.0f, 150.0f), 10.0f, pParent),
	m_bIS_SELLING(bIsSelling),
	m_txtTitle("Game", "Small", this),
	m_CornBtn(PLANTTYPE_Corn, m_bIS_SELLING, "Plant", "Corn", this),
	m_EggplantBtn(PLANTTYPE_Eggplant, m_bIS_SELLING, "Plant", "Eggplant", this),
	m_PumpkinBtn(PLANTTYPE_Pumpkin, m_bIS_SELLING, "Plant", "Pumpkin", this)
{
	m_txtTitle.TextSet(m_bIS_SELLING ? "Click to sell" : "Click to eat");
	m_txtTitle.pos.Set(0.0f, 120.0f);
	m_txtTitle.TextSetState(1);
	m_txtTitle.SetAsScaleBox(GetWidth(false), GetHeight(false) - m_txtTitle.pos.Y(), true);
	m_txtTitle.TextSetAlignment(HYALIGN_Center);
	
	m_CornBtn.pos.Set(10.0f, 80.0f);
	m_CornBtn.GetPanelPtr()->AnimSetState(PLANTSTATE_Harvest);
	
	m_EggplantBtn.pos.Set(10.0f, 40.0f);
	m_EggplantBtn.GetPanelPtr()->AnimSetState(PLANTSTATE_Harvest);

	m_PumpkinBtn.pos.Set(10.0f, 0.0f);
	m_PumpkinBtn.GetPanelPtr()->AnimSetState(PLANTSTATE_Harvest);

	Sync();
}

FoodStuffs::~FoodStuffs()
{
}

void FoodStuffs::Sync()
{
	m_CornBtn.Sync();
	m_EggplantBtn.Sync();
	m_PumpkinBtn.Sync();
}

/*virtual*/ float FoodStuffs::OnShow() /*override*/
{
	return 0.0f;
}

/*virtual*/ void FoodStuffs::OnShown() /*override*/
{
}

/*virtual*/ float FoodStuffs::OnHide() /*override*/
{
	return 0.0f;
}

/*virtual*/ void FoodStuffs::OnHidden() /*override*/
{
}
