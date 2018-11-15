#pragma once
#include "IPanel.h"
#include "FoodStuffs.h"
#include "EquipButton.h"
#include "BuyButton.h"

class HousePanel : public IPanel
{
	FoodStuffs		m_FoodStocks;

	HyText2d		m_SavingsVal;

	EquipButton		m_BtnHoeEquip;
	HySprite2d		m_BtnHoeDecal;
	EquipButton		m_BtnHarvestEquip;
	HySprite2d		m_BtnHarvestDecal;
	EquipButton		m_BtnCornEquip;
	HySprite2d		m_BtnCornDecal;
	BuyButton		m_BtnCornBuy;
	EquipButton		m_BtnEggplantEquip;
	HySprite2d		m_BtnEggplantDecal;
	BuyButton		m_BtnEggplantBuy;
	EquipButton		m_BtnPumpkinEquip;
	HySprite2d		m_BtnPumpkinDecal;
	BuyButton		m_BtnPumpkinBuy;
	EquipButton		m_BtnGernaiumEquip;
	HySprite2d		m_BtnGernaiumDecal;
	BuyButton		m_BtnGernaiumBuy;
	EquipButton		m_BtnMarigoldEquip;
	HySprite2d		m_BtnMarigoldDecal;
	BuyButton		m_BtnMarigoldBuy;
	EquipButton		m_BtnVineEquip;
	HySprite2d		m_BtnVineDecal;
	BuyButton		m_BtnVineBuy;

	HyText2d		m_AirConditionText;

public:
	HousePanel(const InfoPanelInit &equipInfoPanelInitRef, const InfoPanelInit &buyInfoPanelInitRef, HyEntity2d *pParent);
	virtual ~HousePanel();

	virtual void Construct() override;

	virtual void Show() override;
	virtual void Hide() override;
	virtual bool IsTransition() override;

	void SetEquipedUI();
	void HideEquipedUI();

	void Sync();

	virtual void OnUpdate() override;
};
