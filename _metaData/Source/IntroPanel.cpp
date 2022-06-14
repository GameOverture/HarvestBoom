#include "pch.h"
#include "IntroPanel.h"

IntroPanel::IntroPanel(HyEntity2d *pParent) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(600, 380, 10), pParent),
	m_HeaderText(HyPanelInit(), "Game", "Small", this),
	m_BodyText(HyPanelInit(), "Game", "Small", this)
{
	//m_HeaderText.pos.Set(20.0f, GetHeight(false) - 85.0f);
	//m_HeaderText.SetAsScaleBox(GetWidth(false) - 40.0f, 64.0f, true);
	m_HeaderText.SetText("Welcome!");
	//m_HeaderText.TextSetAlignment(HYALIGN_Center);
	InsertWidget(m_HeaderText);

	//m_BodyText.pos.Set(20.0f, GetHeight(false) - 128.0f);
	m_BodyText.SetText("You're a single tasking farming extraordinaire. With the grass in the front yard strangely receding away more each day, you decide to exploit the situation and harvest some crops to pay the bills.\n\nYou got all the tools to get started, so let's get to it!");
	m_BodyText.SetTextState(1);
	//m_BodyText.SetAsColumn(GetWidth(false) - 40.0f);
	InsertWidget(m_BodyText);
	
	//GetFill().alpha.Set(0.5f);
	SetDisplayOrder(DISPLAYORDER_Panel);
}

IntroPanel::~IntroPanel()
{
}

/*virtual*/ float IntroPanel::OnBeginShow() /*override*/
{
	
	//m_BodyText.TextSetAlignment(HYALIGN_Left);

	pos.Set(-GetSize().x, 20);
	pos.Tween(20.0f, 20.0f, 1.0f, HyTween::QuadOut);
	return 1.0f;
}

/*virtual*/ void IntroPanel::OnShown() /*override*/
{
}

/*virtual*/ float IntroPanel::OnBeginHide() /*override*/
{
	pos.Tween(-GetSize().x, 20, 1.0f, HyTween::QuadIn);
	return 1.0f;
}

/*virtual*/ void IntroPanel::OnHidden() /*override*/
{
}


bool IntroPanel::IntroUpdate()
{
	if(HyEngine::Input().IsActionReleased(UseEquip))
	{
		if(m_BodyText.GetTag() == 0)
		{
			m_BodyText.SetTag(1);
			//m_BodyText.TextSetAlignment(HYALIGN_Center);
			m_BodyText.SetText("WASD = move\n\nSpacebar = use equipped item\n\nGo into your house to manage items.\n\nBe sure to save enough money to pay your bills each day! Survive for 7 days.");
		}
		else
			return true;
	}

	return false;
}
