#include "pch.h"
#include "TitleScreen.h"

TitleScreen::TitleScreen() :	HyEntity2d(nullptr),
								m_Panel(this),
								m_Title("Game", "Main", this),
								m_txtPlay("Game", "Small", this),
								m_txtQuit("Game", "Small", this),
								m_Selector("Game", "Small", this),
								m_Legal("Game", "Small", this)
{
}

TitleScreen::~TitleScreen()
{
}

void TitleScreen::Construct()
{
	m_Panel.GetShape().SetAsBox(Hy_App().Window().GetWindowSize().x, Hy_App().Window().GetWindowSize().y);
	m_Panel.topColor.Set(0.2f, 0.2f, 0.2f);

	m_Title.TextSet(Hy_App().GameName());
	m_Title.SetAsScaleBox(static_cast<float>(Hy_App().Window().GetWindowSize().x) - 50.0f, 100.0f, true);
	m_Title.pos.Set(25.0f, Hy_App().Window().GetWindowSize().y - 150.0f);
	m_Title.scale_pivot.Set(m_Title.TextGetBox().x * 0.5f, m_Title.TextGetBox().y * 0.5f);
	m_Title.scale.Set(0.001f, 0.001f);

	m_txtPlay.TextSet("Start");
	m_txtPlay.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f);
	m_txtPlay.SetEnabled(false);

	m_txtQuit.TextSet("Quit");
	m_txtQuit.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f - 30.0f);
	m_txtQuit.SetEnabled(false);

	m_Selector.TextSet(">");
	m_Selector.pos.Set(m_txtPlay.pos.Get());
	m_Selector.pos.Offset(-50.0f, 0.0f);
	m_Selector.SetEnabled(false);

	m_Legal.TextSetState(1);
	m_Legal.TextSet("A Philly Game Mechanics Game Jam\nLicensed by Pretendo of America Inc.");
	m_Legal.TextSetAlignment(HYALIGN_Center);
	m_Legal.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, 40.0f);

	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Title);
}

void TitleScreen::Start()
{
	m_Title.scale.Set(0.001f, 0.001f);
	m_Title.scale.Tween(1.0f, 1.0f, 2.0f, HyTween::BounceOut);
}

/*virtual*/ TitleScreenValue TitleScreen::GameUpdate() /*override*/
{
	if(m_Title.scale.IsTweening())
		return TITLE_Nothing;

	m_txtPlay.SetEnabled(true);
	m_txtQuit.SetEnabled(true);
	m_Selector.SetEnabled(true);

	if(Hy_App().Input().IsActionDown(MoveUp))
		m_Selector.pos.Y(m_txtPlay.pos.Y());
	else if(Hy_App().Input().IsActionDown(MoveDown))
		m_Selector.pos.Y(m_txtQuit.pos.Y());
	else if(Hy_App().Input().IsActionDown(UseEquip))
		return m_Selector.pos.Y() == m_txtPlay.pos.Y() ? TITLE_Play : TITLE_Quit;

	return TITLE_Nothing;
}
