#pragma once
#include "FoodStuffs.h"
#include "EquipButton.h"
#include "BuyButton.h"

class HousePanel : public HyUiContainer
{
	FoodStuffs		m_FoodStocks;

	HyText2d		m_SavingsVal;
	HyText2d		m_DamagesVal;

	HyButton		m_BtnHoeEquip;
	HySprite2d		m_BtnHoeDecal;
	HyButton		m_BtnHarvestEquip;
	HySprite2d		m_BtnHarvestDecal;
	HyButton		m_BtnCornEquip;
	HySprite2d		m_BtnCornDecal;
	HyButton		m_BtnCornBuy;
	HyButton		m_BtnEggplantEquip;
	HySprite2d		m_BtnEggplantDecal;
	HyButton		m_BtnEggplantBuy;
	HyButton		m_BtnPumpkinEquip;
	HySprite2d		m_BtnPumpkinDecal;
	HyButton		m_BtnPumpkinBuy;
	HyButton		m_BtnGernaiumEquip;
	HySprite2d		m_BtnGernaiumDecal;
	HyButton		m_BtnGernaiumBuy;
	HyButton		m_BtnMarigoldEquip;
	HySprite2d		m_BtnMarigoldDecal;
	HyButton		m_BtnMarigoldBuy;
	HyButton		m_BtnVineEquip;
	HySprite2d		m_BtnVineDecal;
	HyButton		m_BtnVineBuy;

	HyText2d		m_AirConditionText;

public:
	HousePanel(HyEntity2d *pParent);
	virtual ~HousePanel();

	void SetEquipedUI();
	void HideEquipedUI();

	void Sync();

protected:
	virtual void OnContainerUpdate() override;

	virtual float OnBeginShow() override;
	virtual void OnShown() override;
	virtual float OnBeginHide() override;
	virtual void OnHidden() override;
};
