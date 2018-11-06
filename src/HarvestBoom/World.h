#pragma once
#include "pch.h"
#include "Player.h"

class HarvestBoom;
class AreaStructure;
class AreaDirt;
class AreaImpassable;
class IPlant;

class World : public HyEntity2d
{
	HarvestBoom &			m_GameRef;
	
	Player					m_Player;

	AreaStructure *			m_pHome;
	AreaDirt *				m_pDirt;
	AreaStructure *			m_pShed;
	AreaImpassable *		m_Fence[4];
	HyEntity2d				m_AreaManager;

	std::vector<IPlant *>	m_PlantList;
	HyEntity2d				m_PlantManager;

public:
	World(HarvestBoom &gameRef);
	virtual ~World();

	void DeleteArea();
	void ConstructLevel();

	virtual void OnUpdate() override;
};

