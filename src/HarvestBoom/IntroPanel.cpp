#include "pch.h"
#include "IntroPanel.h"

IntroPanel::IntroPanel(glm::vec2 vDimensions, HyEntity2d *pParent) :
	IPanel(vDimensions, pParent),
	m_HeaderText("Game", "Small", this),
	m_BodyText("Game", "Small", this)
{
	m_HeaderText.pos.Set(20.0f, GetHeight() - 85.0f);
	m_HeaderText.SetAsScaleBox(GetWidth() - 40.0f, 64.0f, true);
	m_HeaderText.TextSet("Welcome!");
	m_HeaderText.TextSetAlignment(HYALIGN_Center);

	m_BodyText.pos.Set(GetWidth() + 20.0f, GetHeight() - 128.0f);
	m_BodyText.TextSetState(1);
	m_BodyText.SetAsColumn(GetWidth() - 40.0f, true);
	m_BodyText.TextSet("You're a single tasking farming extraordinaire. With the grass in the front yard strangely receding away, you decide to exploit the situation and grow some crops to pay the bills.\n\nYou got all the tools to get started, so let's get to it!");


}

IntroPanel::~IntroPanel()
{
}

/*virtual*/ float IntroPanel::OnShow() /*override*/
{
}

/*virtual*/ void IntroPanel::OnShown() /*override*/
{
}

/*virtual*/ float IntroPanel::OnHide() /*override*/
{
	pos.Tween(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f, 1.0f, HyTween::QuadIn);
}

/*virtual*/ void IntroPanel::OnHidden() /*override*/
{
	pos.Set(-GetWidth() - 100.0f, 0.0f);
}

