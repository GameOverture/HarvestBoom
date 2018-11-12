#pragma once
#include "pch.h"
#include "Player.h"
#include "DayNight.h"
#include "Stamina.h"
#include "World.h"
#include "BillsScreen.h"
#include "DebugGrid.h"

class HarvestBoom;
class IPlant;

class Game : public HyEntity2d
{
	Player					m_Player;
	DayNight				m_DayNight;
	Stamina					m_Stamina;

	World					m_World;
	BillsScreen				m_Bills;

	DebugGrid				m_DebugGrid;

	enum GameState
	{
		GAMESTATE_Bills = 0,
	};
	GameState				m_eGameState;

public:
	Game();
	virtual ~Game();

	void Construct();

	void GameUpdate();
	void DebugUpdate();
};

