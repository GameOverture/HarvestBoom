#include "pch.h"
#include "HarvestBoom.h"

HarvestBoom * HarvestBoom::sm_pInstance = nullptr;

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) :
	HyEngine(initStruct),
	m_eGameState(GAMESTATE_Loading)
{
	sm_pInstance = this;
	Values::Init();

	HyEngine::Window().CreateCamera2d();

	m_Splash.shape.SetAsBox(HyEngine::Window().GetWidth(), HyEngine::Window().GetHeight());
	m_Splash.topColor.Set(0.0f, 0.0f, 0.0f);
	m_Splash.topColor.Tween(139.0f / 255.0f, 160.0f / 255.0f, 231.0f / 255.0f, 2.0f);
	m_Splash.SetDisplayOrder(DISPLAYORDER_Splash);

	HyEngine::Input().MapBtn(ToggleFPS, HYKEY_F);
	HyEngine::Input().MapBtn(ToggleGrid, HYKEY_G);
	HyEngine::Input().MapBtn(MoveUp, HYKEY_Up);
	HyEngine::Input().MapAlternativeBtn(MoveUp, HYKEY_W);
	HyEngine::Input().MapBtn(MoveRight, HYKEY_Right);
	HyEngine::Input().MapAlternativeBtn(MoveRight, HYKEY_D);
	HyEngine::Input().MapBtn(MoveDown, HYKEY_Down);
	HyEngine::Input().MapAlternativeBtn(MoveDown, HYKEY_S);
	HyEngine::Input().MapBtn(MoveLeft, HYKEY_Left);
	HyEngine::Input().MapAlternativeBtn(MoveLeft, HYKEY_A);
	HyEngine::Input().MapBtn(UseEquip, HYKEY_Space);
	HyEngine::Input().MapAlternativeBtn(UseEquip, HYKEY_Enter);

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
	return &sm_pInstance->m_SndBnk;
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
			HyLog("LOADING COMPLETE!");
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

		default:
			break;
		}
		break;

	//case GAMESTATE_TitleFade:
	//	if(m_pTitleScrn->alpha.IsAnimating() == false && m_pGame->IsLoaded())
	//		m_eGameState = GAMESTATE_Game;
	//	break;

	case GAMESTATE_Game:
		m_pGame->GameUpdate();
		break;

	default:
		break;
	}

	return true;
}
