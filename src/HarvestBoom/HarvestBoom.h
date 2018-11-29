#pragma once

#include "pch.h"
#include "Game.h"
#include "TitleScreen.h"

class HarvestBoom : public IHyApplication
{
	HyPrimitive2d				m_Splash;

	TitleScreen *				m_pTitleScrn;
	Game *						m_pGame;

	static LtGAudioSndBank *	sm_pSoundBank;

	enum GameState
	{
		GAMESTATE_Loading = 0,
		GAMESTATE_Title,
		GAMESTATE_TitleFade,
		GAMESTATE_Game
	};
	GameState					m_eGameState;

public:
	HarvestBoom(HarmonyInit &initStruct);
	virtual ~HarvestBoom();

	static LtGAudioSndBank *GetSndBank();
	Game *GetGame();

	void SetTitleScreen(TitleScreenType eTitleType);

	virtual bool Initialize() override;
	virtual bool Update() override;
	virtual void Shutdown() override;
};
