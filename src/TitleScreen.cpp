#include "pch.h"
#include "TitleScreen.h"
#include "HarvestBoom.h"

extern const HarmonyInit &Hy_InitValues();
extern HyWindow &Hy_Window();
extern HyInput &Hy_Input();

TitleScreen::TitleScreen() :	HyEntity2d(nullptr),
								m_Panel("UI", "Title", this),
								m_TitleText("Game", "Main", this),
								m_PlayText("Game", "Small", this),
								m_QuitText("Game", "Small", this),
								m_Selector("Game", "Small", this),
								m_LegalBg(this),
								m_LegalText("Game", "Small", this),
								m_SfxSelector("UI", "Purchase", this)
{
	m_Panel.scale.Set(2.0f, 2.0f);

	m_TitleText.TextSet(Hy_InitValues().sGameName);
	m_TitleText.SetAsScaleBox(static_cast<float>(Hy_Window().GetWindowSize().x) - 50.0f, 100.0f, true);
	m_TitleText.pos.Set(25.0f, Hy_Window().GetWindowSize().y - 150.0f);
	m_TitleText.scale_pivot.Set(m_TitleText.TextGetBox().x * 0.5f, m_TitleText.TextGetBox().y * 0.5f);
	m_TitleText.scale.Set(0.2f, 0.2f);

	m_PlayText.pos.Set(Hy_Window().GetWindowSize().x * 0.5f, Hy_Window().GetWindowSize().y * 0.5f);
	m_PlayText.pos.Offset(0.0f, 50.0f);
	m_PlayText.SetVisible(false);

	m_QuitText.TextSet("Quit");
	m_QuitText.pos.Set(Hy_Window().GetWindowSize().x * 0.5f, Hy_Window().GetWindowSize().y * 0.5f - 30.0f);
	m_QuitText.pos.Offset(0.0f, 50.0f);
	m_QuitText.SetVisible(false);

	m_Selector.TextSet(">");
	m_Selector.pos.Set(m_PlayText.pos.Get());
	m_Selector.pos.Offset(-50.0f, 0.0f);
	m_Selector.SetVisible(false);

	m_LegalText.TextSetState(1);
	m_LegalText.TextSet("A Philly Game Mechanics Game Jam\nLicensed by Pretendo of America Inc.");
	m_LegalText.TextSetAlignment(HYALIGN_Center);
	m_LegalText.pos.Set(Hy_Window().GetWindowSize().x * 0.5f, 40.0f);

	m_LegalBg.SetAsBox(Hy_Window().GetWindowSize().x, 70);
	m_LegalBg.SetTint(0.0f, 0.0f, 0.0f);
	m_LegalBg.alpha.Set(0.4f);

	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_Title);
}

/*virtual*/ TitleScreen::~TitleScreen()
{
}

void TitleScreen::Start(TitleScreenType eTitleType)
{
	if(eTitleType == TITLETYPE_Start)
	{
		m_TitleText.TextSet(Hy_InitValues().sGameName);
		m_PlayText.TextSet("Start");
		m_Panel.AnimSetState(0);

		m_LegalText.alpha.Set(1.0f);
		m_LegalBg.alpha.Set(0.4f);
	}
	else if(eTitleType == TITLETYPE_GameOver)
	{
		m_TitleText.TextSet("Bankruptcy");
		m_PlayText.TextSet("Restart (not working)");
		m_Panel.AnimSetState(1);

		m_LegalText.alpha.Set(0.0f);
		m_LegalBg.alpha.Set(0.0f);
	}
	else if(eTitleType == TITLETYPE_WinGame)
	{
		m_TitleText.TextSet("You Win");
		m_PlayText.TextSet("Restart (not working)");
		m_Panel.AnimSetState(2);
	}

	alpha.Tween(1.0f, 0.5f);
	m_TitleText.scale.Set(0.2f, 0.2f);
	m_TitleText.scale.Tween(1.0f, 1.0f, 2.0f, HyTween::BounceOut);

	Values::Get()->Reset();
}

/*virtual*/ TitleScreenValue TitleScreen::GameUpdate() /*override*/
{
	if(m_TitleText.scale.IsAnimating())
		return TITLE_Nothing;

	m_PlayText.SetVisible(true);
	m_QuitText.SetVisible(true);
	m_Selector.SetVisible(true);

	if(Hy_Input().IsActionDown(MoveUp))
	{
		if(m_Selector.pos.Y() != m_PlayText.pos.Y())
		{
			m_SfxSelector.PlayOneShot(true);
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
			m_Selector.pos.Y(m_PlayText.pos.Y());
		}
	}
	else if(Hy_Input().IsActionDown(MoveDown))
	{
		if(m_Selector.pos.Y() != m_QuitText.pos.Y())
		{
			m_SfxSelector.PlayOneShot(true);
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
			m_Selector.pos.Y(m_QuitText.pos.Y());
		}
	}
	else if(Hy_Input().IsActionDown(UseEquip))
	{
		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
		return m_Selector.pos.Y() == m_PlayText.pos.Y() ? TITLE_Play : TITLE_Quit;
	}

	return TITLE_Nothing;
}
