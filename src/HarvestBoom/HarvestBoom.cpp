#include "pch.h"
#include "HarvestBoom.h"
#include "Audio/LtGAudioLinks.h"

LtGAudioSndBank *HarvestBoom::sm_pSoundBank = nullptr;

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) : IHyApplication(initStruct),
													m_Splash(nullptr),
													m_pTitleScrn(nullptr),
													m_pGame(nullptr),
													m_eGameState(GAMESTATE_Loading)
{
	LtGAudioManager *pAudioManager = LtGAudioManager::GetInstance();
	pAudioManager->Init(initStruct);
	pAudioManager->LinkSoundandWaveInformation((const char ***)szWAVEDEPENDENCIES, (char **)szSOUNDBANKS);
	sm_pSoundBank = LtGAudioManager::GetInstance()->Load("basegame");

	Values::Init();
}

HarvestBoom::~HarvestBoom()
{
	delete m_pTitleScrn;
	delete m_pGame;
}

/*static*/ LtGAudioSndBank *HarvestBoom::GetSndBank()
{
	return sm_pSoundBank;
}

/*virtual*/ bool HarvestBoom::Initialize() /*override*/
{
	Window().CreateCamera2d();

	m_Splash.GetShape().SetAsBox(Window().GetWidth(), Window().GetHeight());
	m_Splash.Load();
	m_Splash.topColor.Set(0.0f, 0.0f, 0.0f);
	m_Splash.topColor.Tween(139.0f / 255.0f, 160.0f / 255.0f, 231.0f / 255.0f, 2.0f);
	m_Splash.SetDisplayOrder(DISPLAYORDER_Splash);

	Input().MapBtn(ToggleFPS, HYKEY_F);
	Input().MapBtn(ToggleGrid, HYKEY_G);
	Input().MapBtn(MoveUp, HYKEY_Up);
	Input().MapAlternativeBtn(MoveUp, HYKEY_W);
	Input().MapBtn(MoveRight, HYKEY_Right);
	Input().MapAlternativeBtn(MoveRight, HYKEY_D);
	Input().MapBtn(MoveDown, HYKEY_Down);
	Input().MapAlternativeBtn(MoveDown, HYKEY_S);
	Input().MapBtn(MoveLeft, HYKEY_Left);
	Input().MapAlternativeBtn(MoveLeft, HYKEY_A);
	Input().MapBtn(UseEquip, HYKEY_Space);
	Input().MapAlternativeBtn(UseEquip, HYKEY_Enter);

	m_pTitleScrn = HY_NEW TitleScreen();
	m_pTitleScrn->Load();

	m_pGame = HY_NEW Game();
	m_pGame->Load();

	return true;
}

/*virtual*/ bool HarvestBoom::Update() /*override*/
{
	switch(m_eGameState)
	{
	case GAMESTATE_Loading:
		if(m_pTitleScrn->IsLoaded())
		{
			m_pTitleScrn->Start();
			m_Splash.SetEnabled(false);
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FARM_WIN);

			m_eGameState = GAMESTATE_Title;
		}
		break;

	case GAMESTATE_Title:
		switch(m_pTitleScrn->GameUpdate())
		{
		case TITLE_Play:
			m_pTitleScrn->alpha.Tween(0.0f, 1.0f);
			m_eGameState = GAMESTATE_Game;
			break;

		case TITLE_Quit:
			return false;
		}
		break;

	case GAMESTATE_TitleFade:
		if(m_pTitleScrn->alpha.IsTweening() == false && m_pGame->IsLoaded())
			m_eGameState = GAMESTATE_Game;
		break;

	case GAMESTATE_Game:
		m_pGame->GameUpdate();
		break;
	}

	return true;
}

/*virtual*/ void HarvestBoom::Shutdown() /*override*/
{
}
