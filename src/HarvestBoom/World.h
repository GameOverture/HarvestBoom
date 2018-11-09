#pragma once
#include "pch.h"
#include "Player.h"
#include "DayNight.h"
#include "Stamina.h"

class HarvestBoom;
class AreaStructure;
class AreaDirt;
class AreaImpassable;
class IPlant;

class World : public HyEntity2d
{
	HarvestBoom &			m_GameRef;
	
	Player					m_Player;
	DayNight				m_DayNight;
	Stamina					m_Stamina;

	AreaDirt *				m_pDirt;
	AreaStructure *			m_pHome;
	AreaStructure *			m_pShed;
	AreaImpassable *		m_FenceTop;
	AreaImpassable *		m_FenceLeft;
	AreaImpassable *		m_FenceRight;
	HyEntity2d				m_AreaManager;

	std::vector<IPlant *>	m_PlantList;
	HyEntity2d				m_PlantManager;

	class DebugGrid : public HyEntity2d
	{
		HyText2d						m_Text;
		std::vector<HyPrimitive2d *>	m_DebugGridHorz;
		std::vector<HyPrimitive2d *>	m_DebugGridVert;
	public:
		DebugGrid(HyEntity2d *pParent);
		HyText2d &GetText() { return m_Text; }
	};
	DebugGrid				m_DebugGrid;

public:
	World(HarvestBoom &gameRef);
	virtual ~World();

	void DeleteArea();
	void ConstructLevel();

	virtual void OnUpdate() override;
};

