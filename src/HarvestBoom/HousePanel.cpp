#include "pch.h"
#include "HousePanel.h"


HousePanel::HousePanel(HyEntity2d *pParent) :	IPanel(pParent),
												m_FoodStocks(this),
												m_Savings("Game", "Small", this),
												m_SavingsVal("Game", "Small", this)
{
}

HousePanel::~HousePanel()
{
}

/*virtual*/ void HousePanel::Construct() /*override*/
{
	m_bCustomVerts = true;
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();
	HySetVec(m_ptFrameVerts[0], PANEL_SIDEMARGIN + 100.0f, PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[1], PANEL_SIDEMARGIN + 100.0f, vWindowSize.y - PANEL_TOPMARGIN - 50.0f);
	HySetVec(m_ptFrameVerts[2], vWindowSize.x - PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN - 50.0f);
	HySetVec(m_ptFrameVerts[3], vWindowSize.x - PANEL_SIDEMARGIN, PANEL_TOPMARGIN);

	IPanel::Construct();

	m_FoodStocks.Construct();
	m_FoodStocks.pos.Set(m_ptFrameVerts[1].x + 30.0f, m_ptFrameVerts[1].y - 140.0f);

	m_Savings.TextSet("Savings");
	m_Savings.TextSetState(1);
	m_Savings.TextSetAlignment(HYALIGN_Left);
	m_Savings.pos.Set(m_ptFrameVerts[2]);
	m_Savings.pos.Offset(-200.0f, -30.0f);
	m_SavingsVal.TextSet("$45");
	m_SavingsVal.TextSetState(1);
	m_SavingsVal.TextSetAlignment(HYALIGN_Right);
	m_SavingsVal.pos.Set(m_ptFrameVerts[2]);
	m_SavingsVal.pos.Offset(-10.0f, -30.0f);
}

/*virtual*/ void HousePanel::Show() /*override*/
{
	SetEnabled(true);
	m_bIsShowing = true;
}

/*virtual*/ void HousePanel::Hide() /*override*/
{
	SetEnabled(false);
	m_bIsShowing = false;
}

/*virtual*/ bool HousePanel::IsTransition() /*override*/
{
	return false;
}
