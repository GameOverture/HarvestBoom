#include "pch.h"
#include "World.h"
#include "HarvestBoom.h"
#include "Player.h"
#include "IPlant.h"
#include "IEnemy.h"
#include "AreaAsphalt.h"
#include "AreaDirt.h"
#include "AreaImpassable.h"
#include "AreaStructure.h"

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
										m_pHome(nullptr),
										m_pDirt(nullptr),
										m_pShed(nullptr),
										m_AreaManager(this),
										m_DebugGrid(this)
{
	m_DebugGrid.SetEnabled(false);
	m_DebugGrid.SetDisplayOrder(9999);
}

World::~World()
{
	DeleteArea();
}

void World::DeleteArea()
{
	while(m_AreaManager.ChildCount() > 0)
		delete m_AreaManager.ChildGet(0);	// Deleting a IHyNode will remove itself from the parent
}

void World::ConstructLevel()
{
	m_DebugGrid.GetText().pos.Set(Hy_App().Window().GetWindowSize().x - 25, Hy_App().Window().GetWindowSize().y - 25);

	DeleteArea();

	m_pDirt = new AreaDirt(&m_AreaManager);
	m_pDirt->SetSize(1000, 1000);
	m_pDirt->SetPos(-500, -500);

	m_pHome = new AreaStructure(&m_AreaManager);
	m_pHome->SetSize(11, 6);
	m_pHome->SetPos(-5, 0);

	m_pShed = new AreaStructure(&m_AreaManager);
	m_pShed->SetSize(4, 3);
	m_pShed->SetPos(8, 5);

	m_FenceTop = new AreaImpassable(&m_AreaManager);
	m_FenceTop->SetSize(28, 1);
	m_FenceTop->SetPos(-12, 12);

	m_FenceLeft = new AreaImpassable(&m_AreaManager);
	m_FenceLeft->SetSize(1, 50);
	m_FenceLeft->SetPos(-12, -38);

	m_FenceRight = new AreaImpassable(&m_AreaManager);
	m_FenceRight->SetSize(1, 50);
	m_FenceRight->SetPos(15, -38);
}

/*virtual*/ void World::OnUpdate() /*override*/
{
	m_pHome->CollisionTest(m_Player);

	if(m_pShed->CollisionTest(m_Player))
		m_Player.Equip();

	HyCamera2d *pCam = Hy_App().Window().GetCamera2d(0);
	pCam->pos.Set(m_Player.pos);

	float fZoom = 1.0f - (HyClamp(m_Player.GetMagnitude(), 0.0f, 100.0f) * 0.001f);
	if(pCam->GetZoom() > fZoom)
		pCam->SetZoom(fZoom);
	else if(m_Player.GetMagnitude() == 0.0f && pCam->scale.IsTweening() == false)
		pCam->scale.Tween(1.0f, 1.0f, 1.75f, HyTween::QuadInOut);

	if(Hy_App().Input().IsActionReleased(UseEquip) && m_Player.IsEquipped())
	{
		IPlant *pNewPlant = new IPlant(&m_PlantManager);
		pNewPlant->SetPos(m_Player.GetPos());
		pNewPlant->Load();
		m_PlantList.push_back(pNewPlant);
	}

	if(Hy_App().Input().IsActionReleased(ToggleGrid))
		m_DebugGrid.SetEnabled(!m_DebugGrid.IsEnabled());

	std::string sDebugText = "Pos ";
	sDebugText += std::to_string(m_Player.GetPos().x);
	sDebugText += ",";
	sDebugText += std::to_string(m_Player.GetPos().y);
	m_DebugGrid.GetText().TextSet(sDebugText);
}
