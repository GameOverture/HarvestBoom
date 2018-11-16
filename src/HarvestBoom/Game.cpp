#include "pch.h"
#include "Game.h"
#include "HarvestBoom.h"
#include "Player.h"
#include "IEnemy.h"

Game::Game() :	HyEntity2d(nullptr),
				m_Player(this),
				m_Stamina(this),
				m_World(this),
				m_DayNight(m_World, m_Stamina, this),
				m_IntroPanel(this),
				m_BillsPanel(this),
				m_DebugGrid(this),
				m_eGameState(GAMESTATE_Init),
				m_fElapsedTime(0.0f)
{
	m_World.Construct();
	m_World.SetLevel();

	m_IntroPanel.Construct();
	m_BillsPanel.Construct();
	
	m_DebugGrid.GetText().pos.Set(Hy_App().Window().GetWindowSize().x - 25, Hy_App().Window().GetWindowSize().y - 25);
	m_DebugGrid.SetEnabled(false);
	m_DebugGrid.SetDisplayOrder(DISPLAYORDER_DebugGrid);
	

	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);
	pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));
	pCam->SetZoom(2.0f);
}

Game::~Game()
{
}

void Game::GameUpdate()
{
	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);

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
				LtGAudioManager::GetInstance()->FadeMusicOut(1.0f);
				
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
			pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));
			pCam->SetZoom(2.0f);
			//float fZoom = 1.0f - (HyClamp(m_Player.GetMagnitude(), 0.0f, 100.0f) * 0.001f);
			//if(pCam->GetZoom() > fZoom)
			//	pCam->SetZoom(fZoom);
			//else if(m_Player.GetMagnitude() == 0.0f && pCam->scale.IsTweening() == false)
			//	pCam->scale.Tween(1.0f, 1.0f, 1.75f, HyTween::QuadInOut);


			m_Player.HandleInput();
			m_World.UpdatePlayer(m_Player, m_Stamina);
		}
		else
		{
			m_World.Reset();
			m_Player.ZeroVelocity();
		}
		
		if(m_DayNight.IsNight())
		{
			pCam->pos.Tween(TILE_SIZE * 12 * 2, TILE_SIZE * 14 * 2, 1.5f, HyTween::QuadInOut);

			m_World.CleanupTiles();
			m_DayNight.HideUI();
			m_eGameState = GAMESTATE_GoHome;
		}
		break;

	case GAMESTATE_GoHome:
		if(pCam->pos.IsTweening() == false)
		{
			m_BillsPanel.Construct();
			m_BillsPanel.Show();
			m_Player.SetEnabled(false);
			m_eGameState = GAMESTATE_Bills;
		}
		break;
		
	case GAMESTATE_Bills:
		if(m_BillsPanel.IsShowing() == false && m_BillsPanel.IsTransition() == false)
		{
			Values::Get()->m_uiCurrentDay++;
			if(Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
			{
				m_DayNight.FadeToPitchBlack();
				m_eGameState = GAMESTATE_Sleep;
			}
			else
			{
				HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FARM_ATTACK);
				pCam->pos.Tween(TILE_SIZE * 12 * 2, TILE_SIZE * 6 * 2, 5.0f, HyTween::QuadInOut);
				m_eGameState = GAMESTATE_BugCameraPan;
			}
		}
		break;

	case GAMESTATE_BugCameraPan:
		if(pCam->pos.IsTweening() == false)
			m_eGameState = GAMESTATE_Bugs;
		break;

	case GAMESTATE_Bugs:
		if(BugUpdate() == false)
		{
			LtGAudioManager::GetInstance()->FadeMusicOut(1.0f);
			m_DayNight.FadeToPitchBlack();
			m_eGameState = GAMESTATE_Sleep;
		}
		break;

	case GAMESTATE_Sleep:
		if(m_DayNight.IsPitchBlack())
		{
			m_Player.SetEnabled(true);
			m_Player.SetPos(PLAYER_STARTPOS);
			pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));

			m_World.SetLevel();
			m_DayNight.Start();
			m_eGameState = GAMESTATE_Playing;
		}
		break;
	}

	DebugUpdate();
}

bool Game::BugUpdate()
{

	return true;
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
