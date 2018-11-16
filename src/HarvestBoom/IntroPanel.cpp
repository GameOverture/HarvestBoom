#include "pch.h"
#include "IntroPanel.h"

#define PANEL_SIDEMARGIN 20.0f
#define PANEL_TOPMARGIN 50.0f

	HySetVec(m_ptFrameVerts[0], PANEL_SIDEMARGIN, PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[1], PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[2], vWindowSize.x - PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[3], vWindowSize.x - PANEL_SIDEMARGIN, PANEL_TOPMARGIN);

IntroPanel::IntroPanel(HyEntity2d *pParent) :	IPanel(pParent),
												m_HeaderText("Game", "Small", this),
												m_BodyText("Game", "Small", this)
{
}

IntroPanel::~IntroPanel()
{
}

void IntroPanel::Construct()
{
	IPanel::Construct();

	float fWidth = m_ptFrameVerts[2].x;

	m_HeaderText.pos.Set(m_ptFrameVerts[1].x + 20.0f, m_ptFrameVerts[1].y - 85.0f);
	m_HeaderText.SetAsScaleBox(PanelWidth() - 40.0f, 64.0f, true);
	m_HeaderText.TextSet("Welcome!");
	m_HeaderText.TextSetAlignment(HYALIGN_Center);

	m_BodyText.pos.Set(m_ptFrameVerts[1].x + 20.0f, m_ptFrameVerts[1].y - 128.0f);
	m_BodyText.TextSetState(1);
	m_BodyText.SetAsColumn(PanelWidth() - 40.0f, true);
	m_BodyText.TextSet("You're a single tasking farming extraordinaire. With the grass in the front yard strangely receding away, you decide to exploit the situation and grow some crops to pay the bills.\n\nYou got all the tools to get started, so let's get to it!");

	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	SetEnabled(true);
}
