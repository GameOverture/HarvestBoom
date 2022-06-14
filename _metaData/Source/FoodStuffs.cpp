#include "pch.h"
#include "FoodStuffs.h"
#include "BillsPanel.h"

FoodStuffs::FoodStuffs(bool bIsSelling, HyEntity2d *pParent) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(160, 150, 10), pParent),
	m_bIS_SELLING(bIsSelling),
	m_Title(HyPanelInit(), "Game", "Small"),
	m_CornBtn(PLANTTYPE_Corn, m_bIS_SELLING, "Plant", "Corn", this),
	m_EggplantBtn(PLANTTYPE_Eggplant, m_bIS_SELLING, "Plant", "Eggplant", this),
	m_PumpkinBtn(PLANTTYPE_Pumpkin, m_bIS_SELLING, "Plant", "Pumpkin", this)
{
	m_Title.SetTextState(1);
	m_Title.SetText(m_bIS_SELLING ? "Click to sell" : "Click to eat");
	InsertWidget(m_Title);

	HyLayoutHandle hButtons = InsertLayout(HYORIEN_Horizontal);
	m_CornBtn.SetSpriteState(PLANTSTATE_Harvest);
	m_EggplantBtn.SetSpriteState(PLANTSTATE_Harvest);
	m_PumpkinBtn.SetSpriteState(PLANTSTATE_Harvest);
	InsertWidget(m_CornBtn, hButtons);
	InsertWidget(m_EggplantBtn, hButtons);
	InsertWidget(m_PumpkinBtn, hButtons);

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
