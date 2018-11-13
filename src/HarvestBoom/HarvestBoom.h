#pragma once

#include "pch.h"
#include "Game.h"
#include "TitleScreen.h"

#define DEV_QUICKMODE

class HarvestBoom : public IHyApplication
{
	static LtGAudioSndBank *	sm_pSoundBank;

	enum GameState
	{
		GAMESTATE_Loading = 0,
		GAMESTATE_Title,
		GAMESTATE_Game
	};
	GameState		m_eGameState;

	HyCamera2d *	m_pCamera;

	TitleScreen		m_TitleScrn;
	Game			m_Game;

public:
	HarvestBoom(HarmonyInit &initStruct);
	virtual ~HarvestBoom();

	static LtGAudioSndBank *GetSndBank();

	virtual bool Initialize() override;
	virtual bool Update() override;
	virtual void Shutdown() override;
};
