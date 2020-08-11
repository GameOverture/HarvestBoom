#include "pch.h"
#include "DebugGrid.h"

#define DEBUG_GRID_SIZE 50

DebugGrid::DebugGrid(HyEntity2d *pParent) :	HyEntity2d(pParent),
											m_DebugText(HY_SYSTEM_FONT, this)
{
	m_DebugText.UseWindowCoordinates(0);
	m_DebugText.TextSetAlignment(HYALIGN_Right);
	
	m_DebugGridHorz.reserve(DEBUG_GRID_SIZE);
	m_DebugGridVert.reserve(DEBUG_GRID_SIZE);

	for(int32 i = -DEBUG_GRID_SIZE; i < DEBUG_GRID_SIZE; ++i)
	{
		m_DebugGridHorz.push_back(HY_NEW HyPrimitive2d(this));
		m_DebugGridHorz.back()->SetAsLineSegment(glm::vec2(-1000.0f, i * TILE_SIZE), glm::vec2(1000.0f, i * TILE_SIZE));
		if(i == 0)
			m_DebugGridHorz.back()->topColor.Set(1.0f, 1.0f, 0.0f);
		else if(i % 5)
			m_DebugGridHorz.back()->topColor.Set(1.0f, 0.0f, 0.0f);
		else
			m_DebugGridHorz.back()->topColor.Set(1.0f, 1.0f, 1.0f);

		m_DebugGridVert.push_back(HY_NEW HyPrimitive2d(this));
		m_DebugGridVert.back()->SetAsLineSegment(glm::vec2(i * TILE_SIZE, -1000.0f), glm::vec2(i * TILE_SIZE, 1000.0f));
		if(i == 0)
			m_DebugGridVert.back()->topColor.Set(1.0f, 1.0f, 0.0f);
		else if(i % 5)
			m_DebugGridVert.back()->topColor.Set(1.0f, 0.0f, 0.0f);
		else
			m_DebugGridVert.back()->topColor.Set(1.0f, 1.0f, 1.0f);
	}
	ReverseDisplayOrder(true);
}

/*virtual*/ DebugGrid::~DebugGrid()
{
}

HyText2d &DebugGrid::GetText()
{
	return m_DebugText;
}
