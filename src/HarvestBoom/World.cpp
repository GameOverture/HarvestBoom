#include "pch.h"
#include "World.h"
#include "HarvestBoom.h"
#include "Player.h"
#include "IPlant.h"
#include "IEnemy.h"

#define DEBUG_GRID_SIZE 50

World::DebugGrid::DebugGrid(HyEntity2d *pParent) :	HyEntity2d(pParent),
													m_Text(HY_SYSTEM_FONT, this)
{
	m_Text.UseWindowCoordinates(0);
	m_Text.TextSetAlignment(HYALIGN_Right);
	
	m_DebugGridHorz.reserve(DEBUG_GRID_SIZE);
	m_DebugGridVert.reserve(DEBUG_GRID_SIZE);

	for(int32 i = -DEBUG_GRID_SIZE; i < DEBUG_GRID_SIZE; ++i)
	{
		m_DebugGridHorz.push_back(HY_NEW HyPrimitive2d(this));
		m_DebugGridHorz.back()->GetShape().SetAsLineSegment(glm::vec2(-1000.0f, i * TILE_SIZE), glm::vec2(1000.0f, i * TILE_SIZE));
		if(i == 0)
			m_DebugGridHorz.back()->topColor.Set(1.0f, 1.0f, 0.0f);
		else if(i % 5)
			m_DebugGridHorz.back()->topColor.Set(1.0f, 0.0f, 0.0f);
		else
			m_DebugGridHorz.back()->topColor.Set(1.0f, 1.0f, 1.0f);

		m_DebugGridVert.push_back(HY_NEW HyPrimitive2d(this));
		m_DebugGridVert.back()->GetShape().SetAsLineSegment(glm::vec2(i * TILE_SIZE, -1000.0f), glm::vec2(i * TILE_SIZE, 1000.0f));
		if(i == 0)
			m_DebugGridVert.back()->topColor.Set(1.0f, 1.0f, 0.0f);
		else if(i % 5)
			m_DebugGridVert.back()->topColor.Set(1.0f, 0.0f, 0.0f);
		else
			m_DebugGridVert.back()->topColor.Set(1.0f, 1.0f, 1.0f);
	}
	ReverseDisplayOrder(true);
}

World::World(HarvestBoom &gameRef) :	HyEntity2d(nullptr),
										m_GameRef(gameRef),
										m_Player(this),
										m_DayNight(this),
										m_Stamina(this),
										m_AreaManager(this),
										m_DebugGrid(this)
{
	m_DebugGrid.SetEnabled(false);
	m_DebugGrid.SetDisplayOrder(DISPLAYORDER_DebugGrid);
	m_DayNight.SetDisplayOrder(DISPLAYORDER_UI);
	m_Stamina.SetDisplayOrder(DISPLAYORDER_UI);
}

World::~World()
{
}

void World::ConstructLevel()
{
	m_DebugGrid.GetText().pos.Set(Hy_App().Window().GetWindowSize().x - 25, Hy_App().Window().GetWindowSize().y - 25);

	m_Stamina.pos.Set(50.0f, 50.0f);

	m_AreaManager.ResetTiles();
	m_AreaManager.ConstructLevel1();

	m_DayNight.Start();
}

/*virtual*/ void World::OnUpdate() /*override*/
{
	if(m_DayNight.IsCycling())
		m_Player.HandleInput();

	m_AreaManager.UpdatePlayer(m_Player);

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

	if(Hy_App().Input().IsActionReleased(ToggleGrid))
		m_DebugGrid.SetEnabled(!m_DebugGrid.IsEnabled());

	std::string sDebugText = "Pos ";
	sDebugText += std::to_string(m_Player.GetPos().x);
	sDebugText += ",";
	sDebugText += std::to_string(m_Player.GetPos().y);
	m_DebugGrid.GetText().TextSet(sDebugText);
}
