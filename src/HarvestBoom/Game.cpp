#include "pch.h"
#include "Game.h"
#include "HarvestBoom.h"
#include "Player.h"
#include "IPlant.h"
#include "IEnemy.h"

Game::Game() :	HyEntity2d(nullptr),
				m_Player(this),
				m_DayNight(this),
				m_Stamina(this),
				m_World(this),
				m_Bills(this),
				m_DebugGrid(this)
{
	m_DebugGrid.SetEnabled(false);
	m_DebugGrid.SetDisplayOrder(DISPLAYORDER_DebugGrid);
	m_DayNight.SetDisplayOrder(DISPLAYORDER_UI);
	m_Stamina.SetDisplayOrder(DISPLAYORDER_UI);
}

Game::~Game()
{
}

void Game::Construct()
{
	m_DebugGrid.GetText().pos.Set(Hy_App().Window().GetWindowSize().x - 25, Hy_App().Window().GetWindowSize().y - 25);
	m_Stamina.pos.Set(50.0f, 50.0f);
	
	m_World.Construct();
	m_World.SetAsLevel1();

	m_Bills.Construct();



	m_DayNight.Start();
}

void Game::GameUpdate()
{
	if(m_DayNight.IsCycling())
		m_Player.HandleInput();

	m_World.UpdatePlayer(m_Player);

	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);
	pCam->pos.Set(static_cast<int>(m_Player.pos.X() * 2.0f), static_cast<int>(m_Player.pos.Y() * 2.0f));
	pCam->SetZoom(2.0f);

	//float fZoom = 1.0f - (HyClamp(m_Player.GetMagnitude(), 0.0f, 100.0f) * 0.001f);
	//if(pCam->GetZoom() > fZoom)
	//	pCam->SetZoom(fZoom);
	//else if(m_Player.GetMagnitude() == 0.0f && pCam->scale.IsTweening() == false)
	//	pCam->scale.Tween(1.0f, 1.0f, 1.75f, HyTween::QuadInOut);

	m_Stamina.Offset((0.0001f * m_Player.GetMagnitude()) * -Hy_UpdateStep());

	//if(Hy_App().Input().IsActionReleased(UseEquip) && m_Player.IsEquipped())
	//{
	//	IPlant *pNewPlant = new IPlant(&m_PlantManager);
	//	pNewPlant->SetPos(m_Player.GetPos());
	//	pNewPlant->Load();
	//	m_PlantList.push_back(pNewPlant);
	//}

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
