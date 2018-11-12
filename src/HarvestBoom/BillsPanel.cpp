#include "pch.h"
#include "BillsPanel.h"

BillsPanel::BillsPanel(HyEntity2d *pParent) :	IPanel(pParent),
												m_txtHarvest("Game", "Small", this),
												m_CornStock("Plant", "Corn", this),
												m_EggplantStock("Plant", "Eggplant", this),
												m_PumpkinStock("Plant", "Pumpkin", this),
												m_txtCorn("Game", "Small", this),
												m_txtEggplant("Game", "Small", this),
												m_txtPumpkin("Game", "Small", this)
{
}

BillsPanel::~BillsPanel()
{
}

void BillsPanel::Construct()
{
	IPanel::Construct();
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Harvest
	m_txtHarvest.TextSet("Food Stuffs:");
	m_txtHarvest.pos.Set(m_ptFrameVerts[1].x + 50.0f, m_ptFrameVerts[1].y - 50.0f);

	m_txtCorn.TextSetState(1);
	m_txtCorn.pos.Set(m_ptFrameVerts[1].x + 100.0f, m_ptFrameVerts[1].y - 75.0f);
	m_txtCorn.TextSet("* 5");
	m_CornStock.AnimSetState(PLANTSTATE_Harvest);
	m_CornStock.pos.Set(m_ptFrameVerts[1].x + 50.0f, m_txtCorn.pos.Y());

	m_txtEggplant.TextSetState(1);
	m_txtEggplant.pos.Set(m_ptFrameVerts[1].x + 100.0f, m_ptFrameVerts[1].y - 100.0f);
	m_txtEggplant.TextSet("* 10");
	m_EggplantStock.pos.Set(m_ptFrameVerts[1].x + 50.0f, m_txtEggplant.pos.Y());
	m_EggplantStock.AnimSetState(PLANTSTATE_Harvest);

	m_txtPumpkin.TextSetState(1);
	m_txtPumpkin.pos.Set(m_ptFrameVerts[1].x + 100.0f, m_ptFrameVerts[1].y - 125.0f);
	m_txtPumpkin.TextSet("* 2");
	m_PumpkinStock.pos.Set(m_ptFrameVerts[1].x + 50.0f, m_txtPumpkin.pos.Y());
	m_PumpkinStock.pos.Offset(0.0f, -10.0f);
	m_PumpkinStock.scale.Set(0.8f, 0.8f);
	m_PumpkinStock.AnimSetState(PLANTSTATE_Harvest);

	UseWindowCoordinates();
}
