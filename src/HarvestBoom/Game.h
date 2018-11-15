#pragma once
#include "pch.h"
#include "Player.h"
#include "DayNight.h"
#include "Stamina.h"
#include "World.h"
#include "IntroPanel.h"
#include "BillsPanel.h"
#include "DebugGrid.h"

class HarvestBoom;
class Plant;

class Game : public HyEntity2d
{
	Player					m_Player;
	Stamina					m_Stamina;
	World					m_World;
	DayNight				m_DayNight;

	IntroPanel				m_IntroPanel;
	BillsPanel				m_BillsPanel;

	DebugGrid				m_DebugGrid;

	enum GameState
	{
		GAMESTATE_Init = 0,
		GAMESTATE_Intro,
		GAMESTATE_IntroHide,
		GAMESTATE_Playing,
		GAMESTATE_GoHome,
		GAMESTATE_Bills,
		GAMESTATE_BugCameraPan,
		GAMESTATE_Bugs,
		GAMESTATE_Sleep,
	};
	GameState				m_eGameState;
	float					m_fElapsedTime;

	enum BugState
	{
		BUGSTATE_CreateBugs = 0,
		BUGSTATE_March,

	};
	BugState				m_eBugState;

public:
	Game();
	virtual ~Game();

	void Construct();

	void GameUpdate();
	bool BugUpdate();
	void DebugUpdate();
};
