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
								m_LegalText("Game", "Small", this),
								m_SfxSelector("UI", "Purchase", this)
{
	m_Panel.scale.Set(2.0f, 2.0f);

	m_TitleText.SetText(HyEngine::InitValues().sGameName);
	m_TitleText.SetAsScaleBox(static_cast<float>(HyEngine::Window().GetWindowSize().x) - 50.0f, 100.0f, true);
	m_TitleText.pos.Set(25.0f, HyEngine::Window().GetWindowSize().y - 150.0f);
	m_TitleText.scale_pivot.Set(m_TitleText.GetTextBoxDimensions().x * 0.5f, m_TitleText.GetTextBoxDimensions().y * 0.5f);
	m_TitleText.scale.Set(0.2f, 0.2f);

	m_PlayText.pos.Set(HyEngine::Window().GetWindowSize().x * 0.5f, HyEngine::Window().GetWindowSize().y * 0.5f);
	m_PlayText.pos.Offset(0.0f, 50.0f);
	m_PlayText.SetVisible(false);

	m_QuitText.SetText("Quit");
	m_QuitText.pos.Set(HyEngine::Window().GetWindowSize().x * 0.5f, HyEngine::Window().GetWindowSize().y * 0.5f - 30.0f);
	m_QuitText.pos.Offset(0.0f, 50.0f);
	m_QuitText.SetVisible(false);

	m_Selector.SetText(">");
	m_Selector.pos.Set(m_PlayText.pos.Get());
	m_Selector.pos.Offset(-50.0f, 0.0f);
	m_Selector.SetVisible(false);

	m_LegalText.SetState(1);
	m_LegalText.SetText("A Philly Game Mechanics Game Jam\nLicensed by Pretendo of America Inc.");
	m_LegalText.SetTextAlignment(HYALIGN_Center);
	m_LegalText.pos.Set(HyEngine::Window().GetWindowSize().x * 0.5f, 40.0f);

	m_LegalBg.shape.SetAsBox(HyEngine::Window().GetWindowSize().x, 70);
	m_LegalBg.SetTint(HyColor::Black);
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
		m_TitleText.SetText(HyEngine::InitValues().sGameName);
		m_PlayText.SetText("Start");
		m_Panel.SetState(0);

		m_LegalText.alpha.Set(1.0f);
		m_LegalBg.alpha.Set(0.4f);
	}
	else if(eTitleType == TITLETYPE_GameOver)
	{
		m_TitleText.SetText("Bankruptcy");
		m_PlayText.SetText("Restart (not working)");
		m_Panel.SetState(1);

		m_LegalText.alpha.Set(0.0f);
		m_LegalBg.alpha.Set(0.0f);
	}
	else if(eTitleType == TITLETYPE_WinGame)
	{
		m_TitleText.SetText("You Win");
		m_PlayText.SetText("Restart (not working)");
		m_Panel.SetState(2);
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

	if(HyEngine::Input().IsActionDown(MoveUp))
	{
		if(m_Selector.pos.Y() != m_PlayText.pos.Y())
		{
			m_SfxSelector.PlayOneShot(true);
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
			m_Selector.pos.Y(m_PlayText.pos.Y());
		}
	}
	else if(HyEngine::Input().IsActionDown(MoveDown))
	{
		if(m_Selector.pos.Y() != m_QuitText.pos.Y())
		{
			m_SfxSelector.PlayOneShot(true);
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
			m_Selector.pos.Y(m_QuitText.pos.Y());
		}
	}
	else if(HyEngine::Input().IsActionDown(UseEquip))
	{
		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);
		return m_Selector.pos.Y() == m_PlayText.pos.Y() ? TITLE_Play : TITLE_Quit;
	}

	return TITLE_Nothing;
}
