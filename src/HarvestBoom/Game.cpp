#include "pch.h"
#include "Game.h"
#include "HarvestBoom.h"
#include "Player.h"
#include "IEnemy.h"

Game::Game() :	HyEntity2d(nullptr),
				m_Player(this),
				m_DayNight(this),
				m_Stamina(this),
				m_World(this),
				m_IntroPanel(this),
				m_BillsPanel(this),
				m_DebugGrid(this),
				m_eGameState(GAMESTATE_Init),
				m_fElapsedTime(0.0f)
{
	m_DebugGrid.SetEnabled(false);
	m_DebugGrid.SetDisplayOrder(DISPLAYORDER_DebugGrid);
	m_DayNight.SetDisplayOrder(DISPLAYORDER_UI);
	m_Stamina.SetDisplayOrder(DISPLAYORDER_UI);
}

Game::~Game()
{
}

// Invoke only once
void Game::Construct()
{
	m_DebugGrid.GetText().pos.Set(Hy_App().Window().GetWindowSize().x - 25, Hy_App().Window().GetWindowSize().y - 25);
	m_Stamina.pos.Set(50.0f, 50.0f);
	
	m_World.Construct();
	m_World.SetLevel();

	m_IntroPanel.Construct();
	m_BillsPanel.Construct();

	m_Player.SetPos(15, 10);
	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);
	pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));
	pCam->SetZoom(2.0f);

	m_Player.Sync();
}

void Game::GameUpdate()
{
	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);
	pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));
	pCam->SetZoom(2.0f);
	//float fZoom = 1.0f - (HyClamp(m_Player.GetMagnitude(), 0.0f, 100.0f) * 0.001f);
	//if(pCam->GetZoom() > fZoom)
	//	pCam->SetZoom(fZoom);
	//else if(m_Player.GetMagnitude() == 0.0f && pCam->scale.IsTweening() == false)
	//	pCam->scale.Tween(1.0f, 1.0f, 1.75f, HyTween::QuadInOut);

	switch(m_eGameState)
	{
	case GAMESTATE_Init:
#ifdef DEV_QUICKMODE
		m_eGameState = GAMESTATE_IntroHide;
#else
		m_fElapsedTime += Hy_UpdateStep();
		if(m_fElapsedTime > 1.0f)
		{
			m_IntroPanel.Show();
			m_eGameState = GAMESTATE_Intro;
		}
#endif
		break;

	case GAMESTATE_Intro:
		if(m_IntroPanel.IsTransition() == false)
		{
			if(Hy_App().Input().IsActionReleased(UseEquip))
			{
				m_IntroPanel.Hide();
				m_eGameState = GAMESTATE_IntroHide;
			}
		}
		break;

	case GAMESTATE_IntroHide:
		if(m_IntroPanel.IsTransition())
			break;

		m_DayNight.Start();
		m_eGameState = GAMESTATE_Playing;
		break;

	case GAMESTATE_Playing:
		if(m_DayNight.IsCycling())
		{
			m_Player.HandleInput();
			m_World.UpdatePlayer(m_Player);

			m_Stamina.Offset((0.0001f * m_Player.GetMagnitude()) * -Hy_UpdateStep());

			//if(Hy_App().Input().IsActionReleased(UseEquip) && m_Player.IsEquipped())
			//{
			//	IPlant *pNewPlant = new IPlant(&m_PlantManager);
			//	pNewPlant->SetPos(m_Player.GetPos());
			//	pNewPlant->Load();
			//	m_PlantList.push_back(pNewPlant);
			//}

			if(false)
			{
				m_BillsPanel.Show();
				m_eGameState = GAMESTATE_Bills;
			}
		}
		break;
		
	case GAMESTATE_Bills:
		if(m_BillsPanel.IsShowing() == false && m_BillsPanel.IsTransition() == false)
		{
			Values::Get()->m_uiCurrentDay++;
			if(Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
				m_eGameState = GAMESTATE_Sleep;
			else
				m_eGameState = GAMESTATE_Bugs;
		}
		break;

	case GAMESTATE_Bugs:
		break;

	case GAMESTATE_Sleep:
		m_World.SetLevel();
		break;
	}

	DebugUpdate();
}

void Game::DebugUpdate()
{
	if(Hy_App().Input().IsActionReleased(ToggleFPS))
	{
		if(Hy_Diagnostics().GetShowFlags() == 0)
			Hy_Diagnostics().Show(HYDIAG_ALL, 16.0f, Hy_App().Window().GetFramebufferSize().y - 16.0f);
		else
			Hy_Diagnostics().Show(HYDIAG_NONE, 16.0f, Hy_App().Window().GetFramebufferSize().y - 16.0f);
	}

	// Debug Grid
	if(Hy_App().Input().IsActionReleased(ToggleGrid))
		m_DebugGrid.SetEnabled(!m_DebugGrid.IsEnabled());

	std::string sDebugText = "Pos ";
	sDebugText += std::to_string(m_Player.GetPos().x);
	sDebugText += ",";
	sDebugText += std::to_string(m_Player.GetPos().y);
	m_DebugGrid.GetText().TextSet(sDebugText);
}
