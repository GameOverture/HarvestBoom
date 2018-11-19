#include "pch.h"
#include "FoodStuffs.h"

FoodStuffs::FoodStuffs(HyEntity2d *pParent) :
	IHy9Slice(glm::vec2(175.0f, 125.0f), 10.0f, pParent),
	m_txtTitle("Game", "Small", this),
	m_CornIcon("Plant", "Corn", this),
	m_CornQuantity("Game", "Small", this),
	m_EggplantIcon("Plant", "Eggplant", this),
	m_EggplantQuantity("Game", "Small", this),
	m_PumpkinIcon("Plant", "Pumpkin", this),
	m_PumpkinQuantity("Game", "Small", this)
{
	m_txtTitle.TextSetState(1);
	m_txtTitle.SetAsScaleBox(GetWidth(false), 64.0f, true);
	m_txtTitle.TextSetAlignment(HYALIGN_Center);
	m_txtTitle.pos.Set(15.0f, 75.0f);

	m_CornQuantity.TextSetState(1);
	m_CornQuantity.pos.Set(GetWidth(false), 60.0f);
	m_CornQuantity.TextSetAlignment(HYALIGN_Right);
	
	m_CornIcon.AnimSetState(PLANTSTATE_Harvest);
	m_CornIcon.pos.Set(10.0f, m_CornQuantity.pos.Y());

	m_EggplantQuantity.TextSetState(1);
	m_EggplantQuantity.pos.Set(GetWidth(false), 35.0f);
	m_EggplantQuantity.TextSetAlignment(HYALIGN_Right);
	
	m_EggplantIcon.pos.Set(10.0f, m_EggplantQuantity.pos.Y());
	m_EggplantIcon.AnimSetState(PLANTSTATE_Harvest);

	m_PumpkinQuantity.TextSetState(1);
	m_PumpkinQuantity.pos.Set(GetWidth(false), 10.0f);
	m_PumpkinQuantity.TextSetAlignment(HYALIGN_Right);

	m_PumpkinIcon.pos.Set(0.0f, m_PumpkinQuantity.pos.Y());
	m_PumpkinIcon.pos.Offset(10.0f, -5.0f);
	m_PumpkinIcon.scale.Set(0.8f, 0.8f);
	m_PumpkinIcon.AnimSetState(PLANTSTATE_Harvest);

	Sync();
}

FoodStuffs::~FoodStuffs()
{
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
