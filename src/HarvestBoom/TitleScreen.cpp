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

	m_txtPlay.TextSet("Start");
	m_txtPlay.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f);

	m_txtQuit.TextSet("Quit");
	m_txtQuit.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f - 30.0f);

	m_Selector.TextSet(">");
	m_Selector.pos.Set(m_txtPlay.pos.Get());
	m_Selector.pos.Offset(-50.0f, 0.0f);

	m_Legal.TextSetState(1);
	m_Legal.TextSet("A Philly Game Mechanics Game Jam\nLicensed by Pretendo of America Inc.");
	m_Legal.TextSetAlignment(HYALIGN_Center);
	m_Legal.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, 40.0f);

	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Title);
}

/*virtual*/ TitleScreenValue TitleScreen::GameUpdate() /*override*/
{
	if(Hy_App().Input().IsActionDown(MoveUp))
		m_Selector.pos.Y(m_txtPlay.pos.Y());
	else if(Hy_App().Input().IsActionDown(MoveDown))
		m_Selector.pos.Y(m_txtQuit.pos.Y());
	else if(Hy_App().Input().IsActionDown(UseEquip))
		return m_Selector.pos.Y() == m_txtPlay.pos.Y() ? TITLE_Play : TITLE_Quit;

	return TITLE_Nothing;
}
