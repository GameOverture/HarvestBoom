#include "pch.h"
#include "FoodStocks.h"


FoodStocks::FoodStocks(HyEntity2d *pParent) :	HyEntity2d(pParent),
												m_txtTitle("Game", "Small", this),
												m_CornStock("Plant", "Corn", this),
												m_EggplantStock("Plant", "Eggplant", this),
												m_PumpkinStock("Plant", "Pumpkin", this),
												m_txtCorn("Game", "Small", this),
												m_txtEggplant("Game", "Small", this),
												m_txtPumpkin("Game", "Small", this)
{
}


FoodStocks::~FoodStocks()
{
}

void FoodStocks::Construct()
{
	//m_txtTitle.TextSetState(1);
	m_txtTitle.TextSet("Food Stuffs:");
	m_txtTitle.SetAsScaleBox(150.0f, 64.0f, true);
	m_txtTitle.TextSetAlignment(HYALIGN_Center);
	m_txtTitle.pos.Set(0.0f, 65.0f);

	m_txtCorn.TextSetState(1);
	m_txtCorn.pos.Set(60.0f, 60.0f);
	m_txtCorn.TextSet("* 5");
	m_CornStock.AnimSetState(PLANTSTATE_Harvest);
	m_CornStock.pos.Set(10.0f, m_txtCorn.pos.Y());

	m_txtEggplant.TextSetState(1);
	m_txtEggplant.pos.Set(60.0f, 35.0f);
	m_txtEggplant.TextSet("* 10");
	m_EggplantStock.pos.Set(10.0f, m_txtEggplant.pos.Y());
	m_EggplantStock.AnimSetState(PLANTSTATE_Harvest);

	m_txtPumpkin.TextSetState(1);
	m_txtPumpkin.pos.Set(60.0f, 10.0f);
	m_txtPumpkin.TextSet("* 2");
	m_PumpkinStock.pos.Set(0.0f, m_txtPumpkin.pos.Y());
	m_PumpkinStock.pos.Offset(10.0f, -5.0f);
	m_PumpkinStock.scale.Set(0.8f, 0.8f);
	m_PumpkinStock.AnimSetState(PLANTSTATE_Harvest);
}
