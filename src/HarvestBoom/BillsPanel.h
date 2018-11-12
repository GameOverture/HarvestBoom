#pragma once
#include "pch.h"

#include "IPanel.h"

class BillsPanel : public IPanel
{
	HyText2d				m_txtHarvest;

	HySprite2d				m_CornStock;
	HySprite2d				m_EggplantStock;
	HySprite2d				m_PumpkinStock;
	HyText2d				m_txtCorn;
	HyText2d				m_txtEggplant;
	HyText2d				m_txtPumpkin;

public:
	BillsPanel(HyEntity2d *pParent);
	virtual ~BillsPanel();

	virtual void Construct() override;
};
