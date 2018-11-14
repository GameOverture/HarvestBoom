#include "pch.h"
#include "HarvestBoom.h"
#include "Audio/LtGAudioLinks.h"

LtGAudioSndBank *HarvestBoom::sm_pSoundBank = nullptr;

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) : IHyApplication(initStruct),
													m_eGameState(GAMESTATE_Loading)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize LgEntity's audio bank pointer
	LtGAudioManager *pAudioManager = LtGAudioManager::GetInstance();
	pAudioManager->Init(initStruct);
	pAudioManager->LinkSoundandWaveInformation((const char ***)szWAVEDEPENDENCIES, (char **)szSOUNDBANKS);
	sm_pSoundBank = LtGAudioManager::GetInstance()->Load("basegame");

	// TODO: Parse in values from hyproj to tune the game with data driven values
	Values::Init();
}

HarvestBoom::~HarvestBoom()
{
}

/*static*/ LtGAudioSndBank *HarvestBoom::GetSndBank()
{
	return sm_pSoundBank;
}

/*virtual*/ bool HarvestBoom::Initialize() /*override*/
{
	m_pCamera = Window().CreateCamera2d();

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

	m_TitleScrn.Construct();
	m_TitleScrn.Load();

	m_Game.Construct();
	m_Game.Load();

	return true;
}

/*virtual*/ bool HarvestBoom::Update() /*override*/
{
	switch(m_eGameState)
	{
	case GAMESTATE_Loading:
		if(m_TitleScrn.IsLoaded() && m_Game.IsLoaded())
		{
#ifdef DEV_QUICKMODE
			m_TitleScrn.SetEnabled(false);
			m_eGameState = GAMESTATE_Game;
#else
			m_TitleScrn.Start();
			m_eGameState = GAMESTATE_Title;
#endif
		}
		break;

	case GAMESTATE_Title: {
		TitleScreenValue eValue = m_TitleScrn.GameUpdate();
		if(TITLE_Play == eValue)
		{
			m_TitleScrn.alpha.Tween(0.0f, 1.0f);
			m_eGameState = GAMESTATE_Game;
		}
		else if(TITLE_Quit == eValue)
			return false;
		} break;

	case GAMESTATE_Game:
		if(m_TitleScrn.alpha.IsTweening())
			break;
		m_Game.GameUpdate();
		break;
	}

	return true;
}

/*virtual*/ void HarvestBoom::Shutdown() /*override*/
{
}
