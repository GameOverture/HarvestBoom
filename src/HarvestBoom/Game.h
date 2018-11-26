#pragma once
#include "pch.h"
#include "Player.h"
#include "Stamina.h"
#include "World.h"
#include "DayNight.h"
#include "IntroPanel.h"
#include "HousePanel.h"
#include "BillsPanel.h"
#include "DebugGrid.h"

class Game : public HyEntity2d
{
	Player					m_Player;
	Stamina					m_Stamina;
	World					m_World;
	IntroPanel				m_IntroPanel;
	HousePanel				m_HousePanel;
	BillsPanel				m_BillsPanel;
	DayNight				m_DayNight;

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

	void Sync();

	void GameUpdate();
	bool BugUpdate();
	void DebugUpdate();
};
