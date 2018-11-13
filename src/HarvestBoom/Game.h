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
class IPlant;

class Game : public HyEntity2d
{
	Player					m_Player;
	DayNight				m_DayNight;
	Stamina					m_Stamina;

	World					m_World;

	IntroPanel				m_IntroPanel;
	BillsPanel				m_BillsPanel;

	DebugGrid				m_DebugGrid;

	enum GameState
	{
		GAMESTATE_Init = 0,
		GAMESTATE_Intro,
		GAMESTATE_IntroHide,
		GAMESTATE_Playing,
		GAMESTATE_Bills,

	};
	GameState				m_eGameState;

	float					m_fElapsedTime;

public:
	Game();
	virtual ~Game();

	void Construct();

	void GameUpdate();
	void DebugUpdate();
};

