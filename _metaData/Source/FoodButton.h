#pragma once
#include "pch.h"

class FoodStuffs;

class FoodButton : public HyButton
{
	const PlantType		m_ePLANT_TYPE;
	bool				m_bIS_SELL_BTN;

	HyPrimitive2d		m_HoverRect;

public:
	FoodButton(PlantType ePlantType, bool bIsSellBtn, const char *szPanelPrefix, const char *szPanelName, HyEntity2d *pParent);

	void Sync();
	void OnFoodBtnClicked();
};
