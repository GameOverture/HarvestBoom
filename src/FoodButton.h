#pragma once
#include "pch.h"
#include "InfoPanel.h"

class FoodStuffs;

class FoodButton : public InfoPanel
{
	const PlantType		m_ePLANT_TYPE;
	bool				m_bIS_SELL_BTN;

	HyPrimitive2d		m_HoverRect;

public:
	FoodButton(PlantType ePlantType, bool bIsSellBtn, const char *szPanelPrefix, const char *szPanelName, HyEntity2d *pParent);

	void Sync();

private:
	virtual void OnMouseEnter() override;
	virtual void OnMouseLeave() override;
	virtual void OnMouseDown() override;
	virtual void OnMouseUp() override;
	virtual void OnMouseClicked() override;
};
