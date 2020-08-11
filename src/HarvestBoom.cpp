#include "pch.h"
#include "HarvestBoom.h"

extern HyWindow &Hy_Window();
extern HyInput &Hy_Input();

HarvestBoom * HarvestBoom::sm_pInstance = nullptr;
LtGAudioSndBank HarvestBoom::sm_SndBnk;

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_eGameState(GAMESTATE_Loading)
{
	sm_pInstance = this;
	Values::Init();

	Hy_Window().CreateCamera2d();

	m_Splash.SetAsBox(Hy_Window().GetWidth(), Hy_Window().GetHeight());
	m_Splash.Load();
	m_Splash.topColor.Set(0.0f, 0.0f, 0.0f);
	m_Splash.topColor.Tween(139.0f / 255.0f, 160.0f / 255.0f, 231.0f / 255.0f, 2.0f);
	m_Splash.SetDisplayOrder(DISPLAYORDER_Splash);

	Hy_Input().MapBtn(ToggleFPS, HYKEY_F);
	Hy_Input().MapBtn(ToggleGrid, HYKEY_G);
	Hy_Input().MapBtn(MoveUp, HYKEY_Up);
	Hy_Input().MapAlternativeBtn(MoveUp, HYKEY_W);
	Hy_Input().MapBtn(MoveRight, HYKEY_Right);
	Hy_Input().MapAlternativeBtn(MoveRight, HYKEY_D);
	Hy_Input().MapBtn(MoveDown, HYKEY_Down);
	Hy_Input().MapAlternativeBtn(MoveDown, HYKEY_S);
	Hy_Input().MapBtn(MoveLeft, HYKEY_Left);
	Hy_Input().MapAlternativeBtn(MoveLeft, HYKEY_A);
	Hy_Input().MapBtn(UseEquip, HYKEY_Space);
	Hy_Input().MapAlternativeBtn(UseEquip, HYKEY_Enter);

	m_pTitleScrn = HY_NEW TitleScreen();
	m_pTitleScrn->Load();

	m_pGame = HY_NEW Game();
	m_pGame->Load();
}

HarvestBoom::~HarvestBoom()
{
	delete m_pTitleScrn;
	delete m_pGame;
}

/*static*/ HarvestBoom *HarvestBoom::GetInstance()
{
	return sm_pInstance;
}

/*static*/ LtGAudioSndBank *HarvestBoom::GetSndBank()
{
	return &sm_SndBnk;
}

Game *HarvestBoom::GetGame()
{
	return m_pGame;
}

void HarvestBoom::SetTitleScreen(TitleScreenType eTitleType)
{
	m_pTitleScrn->Start(eTitleType);
	m_Splash.SetVisible(false);
	HarvestBoom::GetSndBank()->Stop(XACT_CUE_BASEGAME_DAY_90SEC);
	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FARM_WIN);
	
	m_eGameState = GAMESTATE_Title;
}

/*virtual*/ bool HarvestBoom::OnUpdate() /*override*/
{
	switch(m_eGameState)
	{
	case GAMESTATE_Loading:
		if(m_pTitleScrn->IsLoaded())
		{
			SetTitleScreen(TITLETYPE_Start);
		}
		break;

	case GAMESTATE_Title:
		switch(m_pTitleScrn->GameUpdate())
		{
		case TITLE_Play:
			m_pTitleScrn->alpha.Tween(0.0f, 1.0f);
			m_pGame->SetupNewDay();
			m_eGameState = GAMESTATE_Game;
			break;

		case TITLE_Quit:
			return false;
		}
		break;

	case GAMESTATE_TitleFade:
		if(m_pTitleScrn->alpha.IsAnimating() == false && m_pGame->IsLoaded())
			m_eGameState = GAMESTATE_Game;
		break;

	case GAMESTATE_Game:
		m_pGame->GameUpdate();
		break;
	}

	return true;
}
