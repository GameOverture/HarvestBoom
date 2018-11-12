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

	m_txtHeader.pos.Set(m_ptFrameVerts[1].x + 20.0f, m_ptFrameVerts[1].y - 64.0f);
	m_txtHeader.SetAsScaleBox(PanelWidth() - 40.0f, 64.0f, true);
	m_txtHeader.TextSet("Welcome!");

	m_txtIntro.pos.Set(m_ptFrameVerts[1].x + 20.0f, m_ptFrameVerts[1].y - 128.0f);
	m_txtIntro.TextSetState(1);
	m_txtIntro.SetAsColumn(PanelWidth() - 40.0f, true);
	m_txtIntro.TextSet("This is intro text. Mike please fill this in");

	UseWindowCoordinates();
}
