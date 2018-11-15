#include "pch.h"
#include "FoodStuffs.h"

FoodStuffs::FoodStuffs(HyEntity2d *pParent) :	IPanel(pParent),
												m_txtTitle("Game", "Small", this),
												m_CornIcon("Plant", "Corn", this),
												m_CornQuantity("Game", "Small", this),
												m_EggplantIcon("Plant", "Eggplant", this),
												m_EggplantQuantity("Game", "Small", this),
												m_PumpkinIcon("Plant", "Pumpkin", this),
												m_PumpkinQuantity("Game", "Small", this)
{
}

FoodStuffs::~FoodStuffs()
{
}

void FoodStuffs::Construct()
{
	const float fWidth = 175.0f;

	m_bCustomVerts = true;
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();
	HySetVec(m_ptFrameVerts[0], 0.0f, 0.0f);
	HySetVec(m_ptFrameVerts[1], 0.0f, 125.0f);
	HySetVec(m_ptFrameVerts[2], fWidth, 125.0f);
	HySetVec(m_ptFrameVerts[3], fWidth, 0.0f);

	IPanel::Construct();

	const float fQuantityX = fWidth - 15.0f;

	m_txtTitle.TextSetState(1);
	m_txtTitle.SetAsScaleBox(fWidth - 30.0f, 64.0f, true);
	m_txtTitle.TextSetAlignment(HYALIGN_Center);
	m_txtTitle.pos.Set(15.0f, 75.0f);

	m_CornQuantity.TextSetState(1);
	m_CornQuantity.pos.Set(fQuantityX, 60.0f);
	m_CornQuantity.TextSetAlignment(HYALIGN_Right);
	
	m_CornIcon.AnimSetState(PLANTSTATE_Harvest);
	m_CornIcon.pos.Set(10.0f, m_CornQuantity.pos.Y());

	m_EggplantQuantity.TextSetState(1);
	m_EggplantQuantity.pos.Set(fQuantityX, 35.0f);
	m_EggplantQuantity.TextSetAlignment(HYALIGN_Right);
	
	m_EggplantIcon.pos.Set(10.0f, m_EggplantQuantity.pos.Y());
	m_EggplantIcon.AnimSetState(PLANTSTATE_Harvest);

	m_PumpkinQuantity.TextSetState(1);
	m_PumpkinQuantity.pos.Set(fQuantityX, 10.0f);
	m_PumpkinQuantity.TextSetAlignment(HYALIGN_Right);

	m_PumpkinIcon.pos.Set(0.0f, m_PumpkinQuantity.pos.Y());
	m_PumpkinIcon.pos.Offset(10.0f, -5.0f);
	m_PumpkinIcon.scale.Set(0.8f, 0.8f);
	m_PumpkinIcon.AnimSetState(PLANTSTATE_Harvest);

	Sync();
}

void FoodStuffs::SetTitle(std::string sTitle)
{
	m_txtTitle.TextSet(sTitle);
}

void FoodStuffs::Sync()
{
	std::string sText = "* ";
	sText += std::to_string(Values::Get()->m_uiHarvestCorn);
	m_CornQuantity.TextSet(sText);

	sText = "* ";
	sText += std::to_string(Values::Get()->m_uiHarvestEggplant);
	m_EggplantQuantity.TextSet(sText);

	sText = "* ";
	sText += std::to_string(Values::Get()->m_uiHarvestPumpkin);
	m_PumpkinQuantity.TextSet(sText);
}
