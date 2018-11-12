#include "pch.h"
#include "BillsScreen.h"

#define BILLSSCREEN_SIDEMARGIN 20.0f
#define BILLSSCREEN_TOPMARGIN 50.0f

BillsScreen::BillsScreen(HyEntity2d *pParent) : HyEntity2d(pParent),
												m_PanelFill(this),
												m_PanelFrameOutline(this),
												m_PanelFrame(this),
												m_txtHarvest("Game", "Small", this),
												m_CornStock("Plant", "Corn", this),
												m_EggplantStock("Plant", "Eggplant", this),
												m_PumpkinStock("Plant", "Pumpkin", this),
												m_txtCorn("Game", "Small", this),
												m_txtEggplant("Game", "Small", this),
												m_txtPumpkin("Game", "Small", this)
{
}

BillsScreen::~BillsScreen()
{
}

void BillsScreen::Construct()
{
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Panel
	m_PanelFill.GetShape().SetAsBox(vWindowSize.x - (BILLSSCREEN_SIDEMARGIN * 2.0f), vWindowSize.y - (BILLSSCREEN_TOPMARGIN * 2.0f));
	m_PanelFill.pos.Set(BILLSSCREEN_SIDEMARGIN, BILLSSCREEN_TOPMARGIN);
	m_PanelFill.alpha.Set(0.9f);
	m_PanelFill.topColor.Set(0.0f, 0.0f, 0.0f);

	glm::vec2 ptFrameVerts[4];
	HySetVec(ptFrameVerts[0], BILLSSCREEN_SIDEMARGIN, BILLSSCREEN_TOPMARGIN);
	HySetVec(ptFrameVerts[1], BILLSSCREEN_SIDEMARGIN, vWindowSize.y - BILLSSCREEN_TOPMARGIN);
	HySetVec(ptFrameVerts[2], vWindowSize.x - BILLSSCREEN_SIDEMARGIN, vWindowSize.y - BILLSSCREEN_TOPMARGIN);
	HySetVec(ptFrameVerts[3], vWindowSize.x - BILLSSCREEN_SIDEMARGIN, BILLSSCREEN_TOPMARGIN);

	m_PanelFrameOutline.GetShape().SetAsLineLoop(ptFrameVerts, 4);
	m_PanelFrameOutline.SetLineThickness(8.0f);
	m_PanelFrameOutline.topColor.Set(0.0f, 1.0f, 0.f);

	m_PanelFrame.GetShape().SetAsLineLoop(ptFrameVerts, 4);
	m_PanelFrame.SetLineThickness(4.0f);
	m_PanelFrame.topColor.Set(84.0f / 255.0f, 105.0f / 255.0f, 85.0f / 255.0f);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Harvest
	m_txtHarvest.TextSet("Food Stuffs:");
	m_txtHarvest.pos.Set(ptFrameVerts[1].x + 50.0f, ptFrameVerts[1].y - 50.0f);

	m_txtCorn.TextSetState(1);
	m_txtCorn.pos.Set(ptFrameVerts[1].x + 100.0f, ptFrameVerts[1].y - 75.0f);
	m_txtCorn.TextSet("* 5");
	m_CornStock.AnimSetState(PLANTSTATE_Harvest);
	m_CornStock.pos.Set(ptFrameVerts[1].x + 50.0f, m_txtCorn.pos.Y());

	m_txtEggplant.TextSetState(1);
	m_txtEggplant.pos.Set(ptFrameVerts[1].x + 100.0f, ptFrameVerts[1].y - 100.0f);
	m_txtEggplant.TextSet("* 10");
	m_EggplantStock.pos.Set(ptFrameVerts[1].x + 50.0f, m_txtEggplant.pos.Y());
	m_EggplantStock.AnimSetState(PLANTSTATE_Harvest);

	m_txtPumpkin.TextSetState(1);
	m_txtPumpkin.pos.Set(ptFrameVerts[1].x + 100.0f, ptFrameVerts[1].y - 125.0f);
	m_txtPumpkin.TextSet("* 2");
	m_PumpkinStock.pos.Set(ptFrameVerts[1].x + 50.0f, m_txtPumpkin.pos.Y());
	m_PumpkinStock.pos.Offset(0.0f, -10.0f);
	m_PumpkinStock.scale.Set(0.8f, 0.8f);
	m_PumpkinStock.AnimSetState(PLANTSTATE_Harvest);

	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Panel);
}
