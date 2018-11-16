#include "pch.h"
#include "TitleScreen.h"
#include "HarvestBoom.h"

TitleScreen::TitleScreen() :	HyEntity2d(nullptr),
								m_Panel("UI", "Title", this),
								m_TitleText("Game", "Main", this),
								m_PlayText("Game", "Small", this),
								m_QuitText("Game", "Small", this),
								m_Selector("Game", "Small", this),
								m_LegalBg(this),
								m_LegalText("Game", "Small", this)
{
	m_Panel.scale.Set(2.0f, 2.0f);

	m_TitleText.TextSet(Hy_App().GameName());
	m_TitleText.SetAsScaleBox(static_cast<float>(Hy_App().Window().GetWindowSize().x) - 50.0f, 100.0f, true);
	m_TitleText.pos.Set(25.0f, Hy_App().Window().GetWindowSize().y - 150.0f);
	m_TitleText.scale_pivot.Set(m_TitleText.TextGetBox().x * 0.5f, m_TitleText.TextGetBox().y * 0.5f);
	m_TitleText.scale.Set(0.001f, 0.001f);

	m_PlayText.TextSet("Start");
	m_PlayText.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f);
	m_PlayText.pos.Offset(0.0f, 50.0f);
	m_PlayText.SetEnabled(false);

	m_QuitText.TextSet("Quit");
	m_QuitText.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f - 30.0f);
	m_QuitText.pos.Offset(0.0f, 50.0f);
	m_QuitText.SetEnabled(false);

	m_Selector.TextSet(">");
	m_Selector.pos.Set(m_PlayText.pos.Get());
	m_Selector.pos.Offset(-50.0f, 0.0f);
	m_Selector.SetEnabled(false);

	m_LegalText.TextSetState(1);
	m_LegalText.TextSet("A Philly Game Mechanics Game Jam\nLicensed by Pretendo of America Inc.");
	m_LegalText.TextSetAlignment(HYALIGN_Center);
	m_LegalText.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, 40.0f);

	m_LegalBg.GetShape().SetAsBox(Hy_App().Window().GetWindowSize().x, 70);
	m_LegalBg.SetTint(0.0f, 0.0f, 0.0f);
	m_LegalBg.alpha.Set(0.4f);

	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Title);
}

/*virtual*/ TitleScreen::~TitleScreen()
{
}

void TitleScreen::Start()
{
	m_TitleText.scale.Set(0.001f, 0.001f);
	m_TitleText.scale.Tween(1.0f, 1.0f, 2.0f, HyTween::BounceOut);
}

/*virtual*/ TitleScreenValue TitleScreen::GameUpdate() /*override*/
{
	if(m_TitleText.scale.IsTweening())
		return TITLE_Nothing;

	m_PlayText.SetEnabled(true);
	m_QuitText.SetEnabled(true);
	m_Selector.SetEnabled(true);

	if(Hy_App().Input().IsActionDown(MoveUp))
	{
		if(m_Selector.pos.Y() != m_PlayText.pos.Y())
		{
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
			m_Selector.pos.Y(m_PlayText.pos.Y());
		}
	}
	else if(Hy_App().Input().IsActionDown(MoveDown))
	{
		if(m_Selector.pos.Y() != m_QuitText.pos.Y())
		{
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
			m_Selector.pos.Y(m_QuitText.pos.Y());
		}
	}
	else if(Hy_App().Input().IsActionDown(UseEquip))
	{
		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
		return m_Selector.pos.Y() == m_PlayText.pos.Y() ? TITLE_Play : TITLE_Quit;
	}

	return TITLE_Nothing;
}
