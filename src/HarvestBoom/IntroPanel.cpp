#include "pch.h"
#include "IntroPanel.h"

IntroPanel::IntroPanel(HyEntity2d *pParent) :	IPanel(pParent),
												m_txtHeader("Game", "Small", this),
												m_txtIntro("Game", "Small", this)
{
}

IntroPanel::~IntroPanel()
{
}

void IntroPanel::Construct()
{
	IPanel::Construct();

	float fWidth = m_ptFrameVerts[2].x;

	m_txtHeader.pos.Set(m_ptFrameVerts[1].x + 20.0f, m_ptFrameVerts[1].y - 85.0f);
	m_txtHeader.SetAsScaleBox(PanelWidth() - 40.0f, 64.0f, true);
	m_txtHeader.TextSet("Welcome!");
	m_txtHeader.TextSetAlignment(HYALIGN_Center);

	m_txtIntro.pos.Set(m_ptFrameVerts[1].x + 20.0f, m_ptFrameVerts[1].y - 128.0f);
	m_txtIntro.TextSetState(1);
	m_txtIntro.SetAsColumn(PanelWidth() - 40.0f, true);
	m_txtIntro.TextSet("You're a single tasking farming extraordinaire. With the grass in the front yard strangely receding away, you decide to exploit the situation and grow some crops to pay the bills.\n\nYou got all the tools to get started, so let's get to it!");

	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	SetEnabled(true);
}
