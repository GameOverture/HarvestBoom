#include "pch.h"
#include "HousePanel.h"
#include "BillsPanel.h"

extern HyWindow &Hy_Window();

HousePanel::HousePanel(HyEntity2d *pParent) :
	IHy9Slice(glm::vec2(550.0f, 340.0f), 4.0f, pParent),
	m_FoodStocks(false, this),
	m_SavingsVal("Game", "Small", this),
	m_DamagesVal("Game", "Small", this),
	m_BtnHoeEquip(this),
	m_BtnHoeDecal("Equip", "Hoe", &m_BtnHoeEquip),
	m_BtnHarvestEquip(this),
	m_BtnHarvestDecal("Equip", "Sythe", &m_BtnHarvestEquip),
	m_BtnCornEquip(this),
	m_BtnCornDecal("Plant", "Corn", &m_BtnCornEquip),
	m_BtnCornBuy(this),
	m_BtnEggplantEquip(this),
	m_BtnEggplantDecal("Plant", "Eggplant", &m_BtnEggplantEquip),
	m_BtnEggplantBuy(this),
	m_BtnPumpkinEquip(this),
	m_BtnPumpkinDecal("Plant", "Pumpkin", &m_BtnPumpkinEquip),
	m_BtnPumpkinBuy(this),
	m_BtnGernaiumEquip(this),
	m_BtnGernaiumDecal("Plant", "Gernaium", &m_BtnGernaiumEquip),
	m_BtnGernaiumBuy(this),
	m_BtnMarigoldEquip(this),
	m_BtnMarigoldDecal("Plant", "Marigold", &m_BtnMarigoldEquip),
	m_BtnMarigoldBuy(this),
	m_BtnVineEquip(this),
	m_BtnVineDecal("Plant", "Vine", &m_BtnVineEquip),
	m_BtnVineBuy(this),
	m_AirConditionText("Game", "Small", this)
{
	GetFill().SetTint(219.0f / 255.0f, 164.0f / 255.0f, 99.0f / 255.0f);
	GetBorder().SetTint(219.0f / 255.0f, 164.0f / 255.0f, 99.0f / 255.0f);//SetTint(254.0f / 255.0f, 243.0f / 255.0f, 192.0f / 255.0f);
	GetFill().alpha.Set(0.6f);
	SetDisplayOrder(DISPLAYORDER_Panel);
}

HousePanel::~HousePanel()
{
}

void HousePanel::SetEquipedUI()
{
	glm::ivec2 vWindowSize = Hy_Window().GetWindowSize();

	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		m_BtnHoeEquip.ParentDetach();
		m_BtnHoeEquip.SetVisible(true);
		m_BtnHoeEquip.alpha.Set(0.0f);
		m_BtnHoeEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnHoeEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Harvest:
		m_BtnHarvestEquip.ParentDetach();
		m_BtnHarvestEquip.SetVisible(true);
		m_BtnHarvestEquip.alpha.Set(0.0f);
		m_BtnHarvestEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnHarvestEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Corn:
		m_BtnCornEquip.ParentDetach();
		m_BtnCornEquip.SetVisible(true);
		m_BtnCornEquip.alpha.Set(0.0f);
		m_BtnCornEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnCornEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Eggplant:
		m_BtnEggplantEquip.ParentDetach();
		m_BtnEggplantEquip.SetVisible(true);
		m_BtnEggplantEquip.alpha.Set(0.0f);
		m_BtnEggplantEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnEggplantEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Pumpkin:
		m_BtnPumpkinEquip.ParentDetach();
		m_BtnPumpkinEquip.SetVisible(true);
		m_BtnPumpkinEquip.alpha.Set(0.0f);
		m_BtnPumpkinEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnPumpkinEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Gernaium:
		m_BtnGernaiumEquip.ParentDetach();
		m_BtnGernaiumEquip.SetVisible(true);
		m_BtnGernaiumEquip.alpha.Set(0.0f);
		m_BtnGernaiumEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnGernaiumEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Marigold:
		m_BtnMarigoldEquip.ParentDetach();
		m_BtnMarigoldEquip.SetVisible(true);
		m_BtnMarigoldEquip.alpha.Set(0.0f);
		m_BtnMarigoldEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnMarigoldEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Vine:
		m_BtnVineEquip.ParentDetach();
		m_BtnVineEquip.SetVisible(true);
		m_BtnVineEquip.alpha.Set(0.0f);
		m_BtnVineEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnVineEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetPanelPtr()->AnimGetCurFrameWidth() - 10.0f, 10.0f);
		break;

	default:
		break;
	}
}

void HousePanel::HideEquipedUI()
{
	glm::ivec2 vWindowSize = Hy_Window().GetWindowSize();

	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		if(m_BtnHoeEquip.pos.IsAnimating() == false)
			m_BtnHoeEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Harvest:
		if(m_BtnHarvestEquip.pos.IsAnimating() == false)
			m_BtnHarvestEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Corn:
		if(m_BtnCornEquip.pos.IsAnimating() == false)
			m_BtnCornEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Eggplant:
		if(m_BtnEggplantEquip.pos.IsAnimating() == false)
			m_BtnEggplantEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Pumpkin:
		if(m_BtnPumpkinEquip.pos.IsAnimating() == false)
			m_BtnPumpkinEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Gernaium:
		if(m_BtnGernaiumEquip.pos.IsAnimating() == false)
			m_BtnGernaiumEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Marigold:
		if(m_BtnMarigoldEquip.pos.IsAnimating() == false)
			m_BtnMarigoldEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;
	case EQUIP_Vine:
		if(m_BtnVineEquip.pos.IsAnimating() == false)
			m_BtnVineEquip.pos.Tween(vWindowSize.x + 100.0f, 10.0f, 1.0f, HyTween::QuadIn);
		break;

	default:
		break;
	}
}

#define HIDDEN_BUTTON_TINT 0.1f, 0.1f, 0.1f
void HousePanel::Sync()
{
	m_FoodStocks.Sync();

	EquipedItemType eEquipedItem = Values::Get()->m_eEquipedItem;

	std::string sText = "Savings $";
	sText += std::to_string(Values::Get()->m_iSavings);
	m_SavingsVal.TextSet(sText);

	if(Values::Get()->m_uiDamageCost > 0)
	{
		m_DamagesVal.alpha.Set(1.0f);
		sText = "Bug Damages $";
		sText += std::to_string(Values::Get()->m_uiDamageCost);
		m_DamagesVal.TextSet(sText);
	}
	else
		m_DamagesVal.alpha.Set(0.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(eEquipedItem == EQUIP_Hoe)
		m_BtnHoeEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
		m_BtnHoeEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	m_BtnHoeEquip.EnableMouseInput();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	if(eEquipedItem == EQUIP_Harvest)
		m_BtnHarvestEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
		m_BtnHarvestEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	m_BtnHarvestEquip.EnableMouseInput();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsCorn);
	m_BtnCornEquip.GetTextPtr()->TextSet(sText);
	if(eEquipedItem == EQUIP_Corn)
		m_BtnCornEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
	{
		if(Values::Get()->m_uiSeedsCorn > 0)
		{
			m_BtnCornEquip.EnableMouseInput();
			m_BtnCornEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
		}
		else
		{
			m_BtnCornEquip.DisableMouseInput();
			m_BtnCornEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
		}
	}

	if(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_CORNSEEDS))
	{
		m_BtnCornBuy.EnableMouseInput();
		m_BtnCornBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	}
	else
	{
		m_BtnCornBuy.DisableMouseInput();
		m_BtnCornBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsEggplant);
	m_BtnEggplantEquip.GetTextPtr()->TextSet(sText);
	if(eEquipedItem == EQUIP_Eggplant)
		m_BtnEggplantEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
	{
		if(Values::Get()->m_uiSeedsEggplant > 0)
		{
			m_BtnEggplantEquip.EnableMouseInput();
			m_BtnEggplantEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
		}
		else
		{
			m_BtnEggplantEquip.DisableMouseInput();
			m_BtnEggplantEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
		}
	}

	if(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_EGGPLANTSEEDS))
	{
		m_BtnEggplantBuy.EnableMouseInput();
		m_BtnEggplantBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	}
	else
	{
		m_BtnEggplantBuy.DisableMouseInput();
		m_BtnEggplantBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsPumpkin);
	m_BtnPumpkinEquip.GetTextPtr()->TextSet(sText);
	if(eEquipedItem == EQUIP_Pumpkin)
		m_BtnPumpkinEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
	{
		if(Values::Get()->m_uiSeedsPumpkin > 0)
		{
			m_BtnPumpkinEquip.EnableMouseInput();
			m_BtnPumpkinEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
		}
		else
		{
			m_BtnPumpkinEquip.DisableMouseInput();
			m_BtnPumpkinEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
		}
	}

	if(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_PUMPKINSEEDS))
	{
		m_BtnPumpkinBuy.EnableMouseInput();
		m_BtnPumpkinBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	}
	else
	{
		m_BtnPumpkinBuy.DisableMouseInput();
		m_BtnPumpkinBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsGernaium);
	m_BtnGernaiumEquip.GetTextPtr()->TextSet(sText);
	if(eEquipedItem == EQUIP_Gernaium)
		m_BtnGernaiumEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
	{
		if(Values::Get()->m_uiSeedsGernaium > 0)
		{
			m_BtnGernaiumEquip.EnableMouseInput();
			m_BtnGernaiumEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
		}
		else
		{
			m_BtnGernaiumEquip.DisableMouseInput();
			m_BtnGernaiumEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
		}
	}

	if(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_GERNAIUMSEEDS))
	{
		m_BtnGernaiumBuy.EnableMouseInput();
		m_BtnGernaiumBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	}
	else
	{
		m_BtnGernaiumBuy.DisableMouseInput();
		m_BtnGernaiumBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
	}

	if(true)//Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
	{
		m_BtnGernaiumEquip.SetTint(HIDDEN_BUTTON_TINT);
		m_BtnGernaiumEquip.GetTextPtr()->SetVisible(false);
		m_BtnGernaiumBuy.SetTint(HIDDEN_BUTTON_TINT);
		m_BtnGernaiumBuy.GetTextPtr()->SetVisible(false);

		m_BtnGernaiumEquip.DisableMouseInput();
		m_BtnGernaiumBuy.DisableMouseInput();
	}
	else
	{
		m_BtnGernaiumEquip.GetTextPtr()->SetVisible(true);
		m_BtnGernaiumEquip.SetTint(1.0f, 1.0f, 1.0f);
		m_BtnGernaiumBuy.GetTextPtr()->SetVisible(true);
		m_BtnGernaiumBuy.SetTint(1.0f, 1.0f, 1.0f);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsMarigold);
	m_BtnMarigoldEquip.GetTextPtr()->TextSet(sText);
	if(eEquipedItem == EQUIP_Marigold)
		m_BtnMarigoldEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
	{
		if(Values::Get()->m_uiSeedsMarigold > 0)
		{
			m_BtnMarigoldEquip.EnableMouseInput();
			m_BtnMarigoldEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
		}
		else
		{
			m_BtnMarigoldEquip.DisableMouseInput();
			m_BtnMarigoldEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
		}
	}

	if(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_MARIGOLDSEEDS))
	{
		m_BtnMarigoldBuy.EnableMouseInput();
		m_BtnMarigoldBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	}
	else
	{
		m_BtnMarigoldBuy.DisableMouseInput();
		m_BtnMarigoldBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
	}

	if(true)//Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
	{
		m_BtnMarigoldEquip.SetTint(HIDDEN_BUTTON_TINT);
		m_BtnMarigoldEquip.GetTextPtr()->SetVisible(false);
		m_BtnMarigoldBuy.SetTint(HIDDEN_BUTTON_TINT);
		m_BtnMarigoldBuy.GetTextPtr()->SetVisible(false);

		m_BtnMarigoldEquip.DisableMouseInput();
		m_BtnMarigoldBuy.DisableMouseInput();
	}
	else
	{
		m_BtnMarigoldEquip.GetTextPtr()->SetVisible(true);
		m_BtnMarigoldEquip.SetTint(1.0f, 1.0f, 1.0f);
		m_BtnMarigoldBuy.GetTextPtr()->SetVisible(true);
		m_BtnMarigoldBuy.SetTint(1.0f, 1.0f, 1.0f);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsVine);
	m_BtnVineEquip.GetTextPtr()->TextSet(sText);
	if(eEquipedItem == EQUIP_Vine)
		m_BtnVineEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Selected);
	else
	{
		if(Values::Get()->m_uiSeedsVine > 0)
		{
			m_BtnVineEquip.EnableMouseInput();
			m_BtnVineEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
		}
		else
		{
			m_BtnVineEquip.DisableMouseInput();
			m_BtnVineEquip.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
		}
	}

	if(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_VINESEEDS))
	{
		m_BtnVineBuy.EnableMouseInput();
		m_BtnVineBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Pressable);
	}
	else
	{
		m_BtnVineBuy.DisableMouseInput();
		m_BtnVineBuy.GetPanelPtr()->AnimSetState(HYBUTTONSTATE_Disabled);
	}

	if(true)//Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
	{
		m_BtnVineEquip.SetTint(HIDDEN_BUTTON_TINT);
		m_BtnVineEquip.GetTextPtr()->SetVisible(false);
		m_BtnVineBuy.SetTint(HIDDEN_BUTTON_TINT);
		m_BtnVineBuy.GetTextPtr()->SetVisible(false);

		m_BtnVineEquip.DisableMouseInput();
		m_BtnVineBuy.DisableMouseInput();
	}
	else
	{
		m_BtnVineEquip.GetTextPtr()->SetVisible(true);
		m_BtnVineEquip.SetTint(1.0f, 1.0f, 1.0f);
		m_BtnVineBuy.GetTextPtr()->SetVisible(true);
		m_BtnVineBuy.SetTint(1.0f, 1.0f, 1.0f);
	}
}

/*virtual*/ void HousePanel::OnUpdate() /*override*/
{
	IHy9Slice::OnUpdate();
	if(m_AirConditionText.IsVisible() && m_AirConditionText.pos.IsAnimating() == false)
		m_AirConditionText.pos.Tween(15.0f, m_AirConditionText.pos.Y(), 0.5f, HyTween::QuadOut, [this](IHyNode *) { m_AirConditionText.pos.Tween(0.0f, m_AirConditionText.pos.Y(), 0.5f, HyTween::QuadIn); });
}

/*virtual*/ float HousePanel::OnShow() /*override*/
{
	const float fTransitionDur = 0.5f;

	rot.Set(90.0f);
	rot.Tween(0.0f, fTransitionDur, HyTween::QuadOut);
	alpha.Set(1.0f);

	pos.Set(static_cast<float>(Hy_Window().GetWidth()) - GetWidth(false), 0.0f);
	rot_pivot.Set(static_cast<float>(Hy_Window().GetWindowSize().x), 0.0f);

	m_FoodStocks.Show();
	m_FoodStocks.pos.Set(0.0f + 50.0f, GetHeight(false) - 195.0f);

	m_SavingsVal.TextSetState(1);
	m_SavingsVal.TextSetAlignment(HYALIGN_Right);
	m_SavingsVal.pos.Set(GetWidth(false) - 10.0f, GetHeight(false) - 19.0f);

	m_DamagesVal.TextSetState(1);
	m_DamagesVal.TextSetAlignment(HYALIGN_Right);
	m_DamagesVal.pos.Set(GetWidth(false) - 10.0f, GetHeight(false) - 44.0f);
	m_DamagesVal.TextSetLayerColor(0, 1, PAY_COLORS);

	const float fButtonSideMargin = 5.0f;
	const float fButtonBotMargin = 35.0f;
	const float fButtonOffsetX = 90.0f;
	const float fButtonOffsetY = 110.0f;

	const float fDecalOffsetX = 20.0f;
	const float fDecalOffsetY = 10.0f;

	const float fBuyButtonOffsetY = -30.0f;

	ChildAppend(m_BtnHoeEquip);
	m_BtnHoeEquip.GetTextPtr()->TextSet("  Hoe  ");
	m_BtnHoeEquip.GetTextPtr()->TextSetState(1);
	m_BtnHoeEquip.alpha.Set(1.0f);
	m_BtnHoeEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnHoeEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 2.5f), fButtonBotMargin + (fButtonOffsetY * 1.0f)  + 70.0f);
	m_BtnHoeEquip.SetTag(EQUIP_Hoe);

	m_BtnHoeDecal.pos.Set(0.0f, 0.0f);
	m_BtnHoeDecal.pos.Offset(fDecalOffsetX + 19.0f, fDecalOffsetY + 25.0f);
	m_BtnHoeDecal.scale.Set(2.0f, 2.0f);
	m_BtnHoeEquip.GetTextPtr()->SetDisplayOrder(m_BtnHoeDecal.GetDisplayOrder() + 1);
	
	ChildAppend(m_BtnHarvestEquip);
	m_BtnHarvestEquip.GetTextPtr()->TextSet("Harvest");
	m_BtnHarvestEquip.GetTextPtr()->TextSetState(1);
	m_BtnHarvestEquip.alpha.Set(1.0f);
	m_BtnHarvestEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnHarvestEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 1.5f), fButtonBotMargin + (fButtonOffsetY * 1.0f) + 70.0f);
	m_BtnHarvestEquip.SetTag(EQUIP_Harvest);

	m_BtnHarvestDecal.pos.Set(0.0f, 0.0f);
	m_BtnHarvestDecal.pos.Offset(fDecalOffsetX + 10.0f, fDecalOffsetY + 25.0f);
	m_BtnHarvestDecal.scale.Set(2.0f, 2.0f);
	m_BtnHarvestEquip.GetTextPtr()->SetDisplayOrder(m_BtnHarvestDecal.GetDisplayOrder() + 1);

	ChildAppend(m_BtnCornEquip);
	m_BtnCornEquip.alpha.Set(1.0f);
	m_BtnCornEquip.GetTextPtr()->TextSetState(1);
	m_BtnCornEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnCornEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnCornEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 3.0f), fButtonBotMargin + (fButtonOffsetY * 1.0f));
	m_BtnCornEquip.SetTag(EQUIP_Corn);

	m_BtnCornDecal.AnimSetState(PLANTSTATE_Harvest);
	m_BtnCornDecal.pos.Set(0.0f, 0.0f);
	m_BtnCornDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnCornDecal.scale.Set(2.0f, 2.0f);
	m_BtnCornEquip.GetTextPtr()->SetDisplayOrder(m_BtnCornDecal.GetDisplayOrder() + 1);

	std::string sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_CORNSEEDS);
	m_BtnCornBuy.GetTextPtr()->TextSet(sText);
	m_BtnCornBuy.GetTextPtr()->TextSetState(1);
	m_BtnCornBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnCornBuy.pos.Set(m_BtnCornEquip.pos);
	m_BtnCornBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnCornBuy.SetTag(EQUIP_Corn);
	m_BtnCornBuy.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);

	ChildAppend(m_BtnEggplantEquip);
	m_BtnEggplantEquip.alpha.Set(1.0f);
	m_BtnEggplantEquip.GetTextPtr()->TextSetState(1);
	m_BtnEggplantEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnEggplantEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnEggplantEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 2.0f), fButtonBotMargin + (fButtonOffsetY * 1.0f));
	m_BtnEggplantEquip.SetTag(EQUIP_Eggplant);

	m_BtnEggplantDecal.AnimSetState(PLANTSTATE_Harvest);
	m_BtnEggplantDecal.pos.Set(0.0f, 0.0f);
	m_BtnEggplantDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnEggplantDecal.scale.Set(2.0f, 2.0f);
	m_BtnEggplantEquip.GetTextPtr()->SetDisplayOrder(m_BtnEggplantDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_EGGPLANTSEEDS);
	m_BtnEggplantBuy.GetTextPtr()->TextSet(sText);
	m_BtnEggplantBuy.GetTextPtr()->TextSetState(1);
	m_BtnEggplantBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnEggplantBuy.pos.Set(m_BtnEggplantEquip.pos);
	m_BtnEggplantBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnEggplantBuy.SetTag(EQUIP_Eggplant);
	m_BtnEggplantBuy.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);

	ChildAppend(m_BtnPumpkinEquip);
	m_BtnPumpkinEquip.alpha.Set(1.0f);
	m_BtnPumpkinEquip.GetTextPtr()->TextSetState(1);
	m_BtnPumpkinEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnPumpkinEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnPumpkinEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 1.0f), fButtonBotMargin + (fButtonOffsetY * 1.0f));
	m_BtnPumpkinEquip.SetTag(EQUIP_Pumpkin);

	m_BtnPumpkinDecal.AnimSetState(PLANTSTATE_Harvest);
	m_BtnPumpkinDecal.pos.Set(0.0f, 0.0f);
	m_BtnPumpkinDecal.pos.Offset(fDecalOffsetX - 4.0f, fDecalOffsetY + 10.0f);
	m_BtnPumpkinDecal.scale.Set(1.3f, 1.3f);
	m_BtnPumpkinEquip.GetTextPtr()->SetDisplayOrder(m_BtnPumpkinDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_PUMPKINSEEDS);
	m_BtnPumpkinBuy.GetTextPtr()->TextSet(sText);
	m_BtnPumpkinBuy.GetTextPtr()->TextSetState(1);
	m_BtnPumpkinBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnPumpkinBuy.pos.Set(m_BtnPumpkinEquip.pos);
	m_BtnPumpkinBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnPumpkinBuy.SetTag(EQUIP_Pumpkin);
	m_BtnPumpkinBuy.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);

	ChildAppend(m_BtnGernaiumEquip);
	m_BtnGernaiumEquip.alpha.Set(1.0f);
	m_BtnGernaiumEquip.GetTextPtr()->TextSetState(1);
	m_BtnGernaiumEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnGernaiumEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnGernaiumEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 3.0f), fButtonBotMargin);
	m_BtnGernaiumEquip.SetTag(EQUIP_Gernaium);

	m_BtnGernaiumDecal.AnimSetState(PLANTSTATE_Harvest);
	m_BtnGernaiumDecal.pos.Set(0.0f, 0.0f);
	m_BtnGernaiumDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnGernaiumDecal.scale.Set(2.0f, 2.0f);
	m_BtnGernaiumEquip.GetTextPtr()->SetDisplayOrder(m_BtnGernaiumDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_GERNAIUMSEEDS);
	m_BtnGernaiumBuy.GetTextPtr()->TextSet(sText);
	m_BtnGernaiumBuy.GetTextPtr()->TextSetState(1);
	m_BtnGernaiumBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnGernaiumBuy.pos.Set(m_BtnGernaiumEquip.pos);
	m_BtnGernaiumBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnGernaiumBuy.SetTag(EQUIP_Gernaium);
	m_BtnGernaiumBuy.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);

	ChildAppend(m_BtnMarigoldEquip);
	m_BtnMarigoldEquip.alpha.Set(1.0f);
	m_BtnMarigoldEquip.GetTextPtr()->TextSetState(1);
	m_BtnMarigoldEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnMarigoldEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnMarigoldEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 2.0f), fButtonBotMargin);
	m_BtnMarigoldEquip.SetTag(EQUIP_Marigold);

	m_BtnMarigoldDecal.AnimSetState(PLANTSTATE_Harvest);
	m_BtnMarigoldDecal.pos.Set(0.0f, 0.0f);
	m_BtnMarigoldDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnMarigoldDecal.scale.Set(2.0f, 2.0f);
	m_BtnMarigoldEquip.GetTextPtr()->SetDisplayOrder(m_BtnMarigoldDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_MARIGOLDSEEDS);
	m_BtnMarigoldBuy.GetTextPtr()->TextSet(sText);
	m_BtnMarigoldBuy.GetTextPtr()->TextSetState(1);
	m_BtnMarigoldBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnMarigoldBuy.pos.Set(m_BtnMarigoldEquip.pos);
	m_BtnMarigoldBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnMarigoldBuy.SetTag(EQUIP_Marigold);
	m_BtnMarigoldBuy.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);

	ChildAppend(m_BtnVineEquip);
	m_BtnVineEquip.alpha.Set(1.0f);
	m_BtnVineEquip.GetTextPtr()->TextSetState(1);
	m_BtnVineEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnVineEquip.pos.Set(GetWidth(false), 0.0f);
	m_BtnVineEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 1.0f), fButtonBotMargin);
	m_BtnVineEquip.SetTag(EQUIP_Vine);

	m_BtnVineDecal.AnimSetState(PLANTSTATE_Harvest);
	m_BtnVineDecal.pos.Set(0.0f, 0.0f);
	m_BtnVineDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnVineEquip.GetTextPtr()->SetDisplayOrder(m_BtnVineDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_VINESEEDS);
	m_BtnVineBuy.GetTextPtr()->TextSet(sText);
	m_BtnVineBuy.GetTextPtr()->TextSetState(1);
	m_BtnVineBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnVineBuy.pos.Set(m_BtnVineEquip.pos);
	m_BtnVineBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnVineBuy.SetTag(EQUIP_Vine);
	m_BtnVineBuy.GetPanelPtr()->SetTint(0.0f, 1.0f, 0.0f);

	m_AirConditionText.TextSet("< A/C bonus!");
	m_AirConditionText.TextSetState(1);
	m_AirConditionText.TextSetLayerColor(0, 1, 145.0f / 255.0f, 176.0f / 255.0f, 219.0f / 255.0f, 0.0f, 111.0f / 255.0f, 1.0f);
	m_AirConditionText.TextSetAlignment(HYALIGN_Left);
	m_AirConditionText.pos.Set(0.0f, 0.0f);
	m_AirConditionText.pos.Offset(0.0f, 75.0f);
	m_AirConditionText.alpha.Set(Values::Get()->m_bAirConditioning ? 1.0f : 0.0f);

	Sync();

	return fTransitionDur;
}

/*virtual*/ void HousePanel::OnShown() /*override*/
{
}

/*virtual*/ float HousePanel::OnHide() /*override*/
{
	rot.Tween(90.0f, 0.5f, HyTween::QuadOut);
	return 0.5f;
}

/*virtual*/ void HousePanel::OnHidden() /*override*/
{
	SetEquipedUI();
}
