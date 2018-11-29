#include "pch.h"
#include "Game.h"
#include "HarvestBoom.h"

Game::Game() :
	HyEntity2d(nullptr),
	m_Player(this),
	m_Stamina(this),
	m_World(this),
	m_IntroPanel(this),
	m_HousePanel(this),
	m_BillsPanel(this),
	m_DayNight(m_Stamina, m_HousePanel, this),
	m_BugAttack(m_World, this),
	m_DebugGrid(this),
	m_eGameState(GAMESTATE_Init),
	m_fElapsedTime(0.0f)
{
	m_World.SetupNewDay();
	
	m_DebugGrid.GetText().pos.Set(Hy_App().Window().GetWindowSize().x - 25, Hy_App().Window().GetWindowSize().y - 25);
	m_DebugGrid.SetEnabled(false);
	m_DebugGrid.SetDisplayOrder(DISPLAYORDER_DebugGrid);
	

	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);
	pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));
	pCam->SetZoom(2.0f);

	m_HousePanel.OnShow();
	m_HousePanel.OnHide();
}

Game::~Game()
{
}

void Game::Sync()
{
	m_Player.Sync();
	m_Stamina.Sync();
	m_HousePanel.Sync();
	m_BillsPanel.Sync();
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
			m_DayNight.Reset();
			m_Player.SetEnabled(true);
			m_Player.SetPos(PLAYER_STARTPOS);
			pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));

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
			int iCamPosX = static_cast<int>(m_Player.pos.X() * 2.0f);
			int iCamPosY = static_cast<int>(m_Player.pos.Y() * 2.0f);
			pCam->pos.Set(HyClamp(iCamPosX, 320, 730), HyClamp(iCamPosY, 240, 810));
			pCam->SetZoom(2.0f);
			//float fZoom = 1.0f - (HyClamp(m_Player.GetMagnitude(), 0.0f, 100.0f) * 0.001f);
			//if(pCam->GetZoom() > fZoom)
			//	pCam->SetZoom(fZoom);
			//else if(m_Player.GetMagnitude() == 0.0f && pCam->scale.IsTweening() == false)
			//	pCam->scale.Tween(1.0f, 1.0f, 1.75f, HyTween::QuadInOut);

			m_World.UpdatePlayer(m_Player, m_Stamina, m_HousePanel);
		}
		else
		{
			m_HousePanel.Hide();

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
			m_BillsPanel.Show();
			m_Player.SetEnabled(false);
			m_eGameState = GAMESTATE_Bills;
		}
		break;
		
	case GAMESTATE_Bills:
		if(m_BillsPanel.IsShown() == false && m_BillsPanel.IsTransition() == false)
		{
			if(Values::Get()->m_iSavings < 0 && Values::Get()->m_bCAN_GO_BANKRUPT)
				m_eGameState = GAMESTATE_GameOver;
			else
			{
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
		}
		break;

	case GAMESTATE_BugCameraPan:
		if(pCam->pos.IsTweening() == false)
		{
			m_BugAttack.Setup();
			m_eGameState = GAMESTATE_Bugs;
		}
		break;

	case GAMESTATE_Bugs: {
		if(m_BugAttack.BugUpdate() == false)
		{
			LtGAudioManager::GetInstance()->FadeMusicOut(1.0f);
			m_DayNight.FadeToPitchBlack();
			m_eGameState = GAMESTATE_Sleep;
		}

		const float fCameraPanSpeed = (TILE_SIZE * 2); // per second

		if(Hy_App().Input().IsActionDown(MoveUp))
			pCam->pos.Offset(0.0f, fCameraPanSpeed * Hy_UpdateStep());
		else if(Hy_App().Input().IsActionDown(MoveDown))
			pCam->pos.Offset(0.0f, -fCameraPanSpeed * Hy_UpdateStep());

		if(Hy_App().Input().IsActionDown(MoveLeft))
			pCam->pos.Offset(-fCameraPanSpeed * Hy_UpdateStep(), 0.0f);
		else if(Hy_App().Input().IsActionDown(MoveRight))
			pCam->pos.Offset(fCameraPanSpeed * Hy_UpdateStep(), 0.0f);
		
		break; }

	case GAMESTATE_Sleep:
		if(m_DayNight.IsPitchBlack())
		{
			Values::Get()->m_uiCurrentDay++;

			HarvestBoom::GetSndBank()->Stop(XACT_CUE_BASEGAME_FARM_ATTACK);
			m_Stamina.Reset();

			m_Player.SetEnabled(true);
			m_Player.SetPos(PLAYER_STARTPOS);
			pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));

			m_World.SetupNewDay();
			m_DayNight.Start();
			m_eGameState = GAMESTATE_Playing;
		}
		break;

	case GAMESTATE_GameOver:
		static_cast<HarvestBoom &>(Hy_App()).SetTitleScreen(TITLETYPE_GameOver);
		m_fElapsedTime = 0.0f;
		m_eGameState = GAMESTATE_Init;
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
