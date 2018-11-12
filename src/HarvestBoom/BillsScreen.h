#pragma once
#include "pch.h"

class BillsScreen : public HyEntity2d
{
	HyPrimitive2d			m_PanelFill;
	HyPrimitive2d			m_PanelFrameOutline;
	HyPrimitive2d			m_PanelFrame;


	HyText2d				m_txtHarvest;

	HySprite2d				m_CornStock;
	HySprite2d				m_EggplantStock;
	HySprite2d				m_PumpkinStock;
	HyText2d				m_txtCorn;
	HyText2d				m_txtEggplant;
	HyText2d				m_txtPumpkin;

public:
	BillsScreen(HyEntity2d *pParent);
	virtual ~BillsScreen();

	void Construct();
};
