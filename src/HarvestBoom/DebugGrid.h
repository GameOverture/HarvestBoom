#pragma once
#include "pch.h"

class DebugGrid : public HyEntity2d
{
	HyText2d						m_Text;
	std::vector<HyPrimitive2d *>	m_DebugGridHorz;
	std::vector<HyPrimitive2d *>	m_DebugGridVert;

public:
	DebugGrid(HyEntity2d *pParent);
	virtual ~DebugGrid();

	HyText2d &GetText();
};

