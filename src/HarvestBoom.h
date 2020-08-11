#ifndef HarvestBoom_h__
#define HarvestBoom_h__

#include "Harmony/HyEngine.h"
#include "Game.h"
#include "TitleScreen.h"

class LtGAudioSndBank
{
public:
	void Play(int i) { }
	void Stop(int i) { }
};

class HarvestBoom : public HyEngine
{
	static HarvestBoom *		sm_pInstance;

	HyPrimitive2d				m_Splash;

	TitleScreen *				m_pTitleScrn;
	Game *						m_pGame;

	static LtGAudioSndBank		sm_SndBnk;

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

	static HarvestBoom *GetInstance();

	static LtGAudioSndBank *GetSndBank();

	Game *GetGame();
	void SetTitleScreen(TitleScreenType eTitleType);

	virtual bool OnUpdate() override;
};

#endif // HarvestBoom_h__
