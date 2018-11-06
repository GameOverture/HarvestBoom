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

World::World(HarvestBoom &gameRef) :	HyEntity2d(nullptr),
										m_GameRef(gameRef),
										m_Player(this),
										m_pHome(nullptr),
										m_pDirt(nullptr),
										m_pShed(nullptr),
										m_AreaManager(this)
{
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
	DeleteArea();

	m_pHome = new AreaStructure(&m_AreaManager);
	m_pHome->SetSize(200, 150);
	m_pHome->pos.Set(-100.0f, -75.0f);

	m_pShed = new AreaStructure(&m_AreaManager);
	m_pShed->SetSize(150, 75);
	m_pShed->pos.Set(150.0f, 75.0f);

	m_pDirt = new AreaDirt(&m_AreaManager);
	m_pDirt->SetSize(1000, 3000);
	m_pDirt->pos.Set(-500.0f, -1500.0f);

	m_Fence[0] = new AreaImpassable(&m_AreaManager);
	m_Fence[0]->SetSize(750, 30);
	m_Fence[0]->pos.Set(-400.0f, 200.0f);

	m_Fence[1] = new AreaImpassable(&m_AreaManager);
	m_Fence[1]->SetSize(30, 750);
	m_Fence[1]->pos.Set(-400.0f, -450.0f);

	m_Fence[2] = new AreaImpassable(&m_AreaManager);
	m_Fence[2]->SetSize(30, 750);
	m_Fence[2]->pos.Set(400.0f, -450.0f);

	m_Fence[3] = new AreaImpassable(&m_AreaManager);
	m_Fence[3]->SetSize(750, 30);
	m_Fence[3]->pos.Set(-400.0f, -450.0f);
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
		pNewPlant->pos.Set(m_Player.pos);
		pNewPlant->Load();
		m_PlantList.push_back(pNewPlant);
	}
}
