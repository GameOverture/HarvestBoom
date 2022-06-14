#include "pch.h"
#include "HousePanel.h"
#include "BillsPanel.h"

#define EQUIP_CTOR HyPanelInit("Game", "EquipButton"), "Game", "Small", 8, 5, 70, 35
#define BUY_CTOR HyPanelInit("Game", "BuyButton"), "Game", "Small", 8, 3, 65, 30

HousePanel::HousePanel(HyEntity2d *pParent) :
	HyUiContainer(HYORIEN_Vertical, HyPanelInit(550, 340, 4, HyColor(219, 164, 99), HyColor(219, 164, 99)), pParent),
	m_FoodStocks(false, this),
	m_SavingsVal("Game", "Small", this),
	m_DamagesVal("Game", "Small", this),
	m_BtnHoeEquip(EQUIP_CTOR, this),
	m_BtnHoeDecal("Equip", "Hoe", &m_BtnHoeEquip),
	m_BtnHarvestEquip(EQUIP_CTOR, this),
	m_BtnHarvestDecal("Equip", "Sythe", &m_BtnHarvestEquip),
	m_BtnCornEquip(EQUIP_CTOR, this),
	m_BtnCornDecal("Plant", "Corn", &m_BtnCornEquip),
	m_BtnCornBuy(BUY_CTOR, this),
	m_BtnEggplantEquip(EQUIP_CTOR, this),
	m_BtnEggplantDecal("Plant", "Eggplant", &m_BtnEggplantEquip),
	m_BtnEggplantBuy(BUY_CTOR, this),
	m_BtnPumpkinEquip(EQUIP_CTOR, this),
	m_BtnPumpkinDecal("Plant", "Pumpkin", &m_BtnPumpkinEquip),
	m_BtnPumpkinBuy(BUY_CTOR, this),
	m_BtnGernaiumEquip(EQUIP_CTOR, this),
	m_BtnGernaiumDecal("Plant", "Gernaium", &m_BtnGernaiumEquip),
	m_BtnGernaiumBuy(BUY_CTOR, this),
	m_BtnMarigoldEquip(EQUIP_CTOR, this),
	m_BtnMarigoldDecal("Plant", "Marigold", &m_BtnMarigoldEquip),
	m_BtnMarigoldBuy(BUY_CTOR, this),
	m_BtnVineEquip(EQUIP_CTOR, this),
	m_BtnVineDecal("Plant", "Vine", &m_BtnVineEquip),
	m_BtnVineBuy(BUY_CTOR, this),
	m_AirConditionText("Game", "Small", this)
{
	auto fpOnEquipClicked = [](HyButton *pBtn, void *pData)
	{
		Values::Get()->m_eEquipedItem = static_cast<EquipedItemType>(pBtn->GetTag());

		//if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		//	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FOOTSTEP_1);

		Values::Get()->Sync();
	};
	m_BtnHoeEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnHarvestEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnCornEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnEggplantEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnPumpkinEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnGernaiumEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnMarigoldEquip.SetButtonClickedCallback(fpOnEquipClicked);
	m_BtnVineEquip.SetButtonClickedCallback(fpOnEquipClicked);

	auto fpOnBuyClicked = [](HyButton *pBtn, void *pData)
	{
		//HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_BUYSTUFF);

		switch(static_cast<EquipedItemType>(pBtn->GetTag()))
		{
		case EQUIP_Corn:
			Values::Get()->m_iSavings -= Values::Get()->m_uiCOST_CORNSEEDS;
			Values::Get()->m_uiSeedsCorn++;
			break;
		case EQUIP_Eggplant:
			Values::Get()->m_iSavings -= Values::Get()->m_uiCOST_EGGPLANTSEEDS;
			Values::Get()->m_uiSeedsEggplant++;
			break;
		case EQUIP_Pumpkin:
			Values::Get()->m_iSavings -= Values::Get()->m_uiCOST_PUMPKINSEEDS;
			Values::Get()->m_uiSeedsPumpkin++;
			break;
		case EQUIP_Gernaium:
			Values::Get()->m_iSavings -= Values::Get()->m_uiCOST_GERNAIUMSEEDS;
			Values::Get()->m_uiSeedsGernaium++;
			break;
		case EQUIP_Marigold:
			Values::Get()->m_iSavings -= Values::Get()->m_uiCOST_MARIGOLDSEEDS;
			Values::Get()->m_uiSeedsMarigold++;
			break;
		case EQUIP_Vine:
			Values::Get()->m_iSavings -= Values::Get()->m_uiCOST_VINESEEDS;
			Values::Get()->m_uiSeedsVine++;
			break;

		default:
			break;
		}

		Values::Get()->Sync();
	};
	m_BtnCornBuy.SetButtonClickedCallback(fpOnBuyClicked);
	m_BtnEggplantBuy.SetButtonClickedCallback(fpOnBuyClicked);
	m_BtnPumpkinBuy.SetButtonClickedCallback(fpOnBuyClicked);
	m_BtnGernaiumBuy.SetButtonClickedCallback(fpOnBuyClicked);
	m_BtnMarigoldBuy.SetButtonClickedCallback(fpOnBuyClicked);
	m_BtnVineBuy.SetButtonClickedCallback(fpOnBuyClicked);


	SetDisplayOrder(DISPLAYORDER_Panel);
}

HousePanel::~HousePanel()
{
}

void HousePanel::SetEquipedUI()
{
	glm::ivec2 vWindowSize = HyEngine::Window().GetWindowSize();

	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		m_BtnHoeEquip.ParentDetach();
		m_BtnHoeEquip.SetVisible(true);
		m_BtnHoeEquip.alpha.Set(0.0f);
		m_BtnHoeEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnHoeEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Harvest:
		m_BtnHarvestEquip.ParentDetach();
		m_BtnHarvestEquip.SetVisible(true);
		m_BtnHarvestEquip.alpha.Set(0.0f);
		m_BtnHarvestEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnHarvestEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Corn:
		m_BtnCornEquip.ParentDetach();
		m_BtnCornEquip.SetVisible(true);
		m_BtnCornEquip.alpha.Set(0.0f);
		m_BtnCornEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnCornEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Eggplant:
		m_BtnEggplantEquip.ParentDetach();
		m_BtnEggplantEquip.SetVisible(true);
		m_BtnEggplantEquip.alpha.Set(0.0f);
		m_BtnEggplantEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnEggplantEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Pumpkin:
		m_BtnPumpkinEquip.ParentDetach();
		m_BtnPumpkinEquip.SetVisible(true);
		m_BtnPumpkinEquip.alpha.Set(0.0f);
		m_BtnPumpkinEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnPumpkinEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Gernaium:
		m_BtnGernaiumEquip.ParentDetach();
		m_BtnGernaiumEquip.SetVisible(true);
		m_BtnGernaiumEquip.alpha.Set(0.0f);
		m_BtnGernaiumEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnGernaiumEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Marigold:
		m_BtnMarigoldEquip.ParentDetach();
		m_BtnMarigoldEquip.SetVisible(true);
		m_BtnMarigoldEquip.alpha.Set(0.0f);
		m_BtnMarigoldEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnMarigoldEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;
	case EQUIP_Vine:
		m_BtnVineEquip.ParentDetach();
		m_BtnVineEquip.SetVisible(true);
		m_BtnVineEquip.alpha.Set(0.0f);
		m_BtnVineEquip.alpha.Tween(1.0f, 0.5f);
		m_BtnVineEquip.pos.Set(vWindowSize.x - m_BtnHoeEquip.GetWidth() - 10.0f, 10.0f);
		break;

	default:
		break;
	}
}

void HousePanel::HideEquipedUI()
{
	glm::ivec2 vWindowSize = HyEngine::Window().GetWindowSize();

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
	m_SavingsVal.SetText(sText);

	if(Values::Get()->m_uiDamageCost > 0)
	{
		m_DamagesVal.alpha.Set(1.0f);
		sText = "Bug Damages $";
		sText += std::to_string(Values::Get()->m_uiDamageCost);
		m_DamagesVal.SetText(sText);
	}
	else
		m_DamagesVal.alpha.Set(0.0f);

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_BtnHoeEquip.SetAsHighlighted(eEquipedItem == EQUIP_Hoe);
	m_BtnHoeEquip.EnableMouseInput();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	m_BtnHarvestEquip.SetAsHighlighted(eEquipedItem == EQUIP_Harvest);
	m_BtnHarvestEquip.EnableMouseInput();

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsCorn);
	m_BtnCornEquip.SetText(sText);
	m_BtnCornEquip.SetAsHighlighted(eEquipedItem == EQUIP_Corn);
	m_BtnCornEquip.SetAsEnabled(Values::Get()->m_uiSeedsCorn > 0);

	m_BtnCornBuy.SetAsEnabled(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_CORNSEEDS));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsEggplant);
	m_BtnEggplantEquip.SetText(sText);
	m_BtnEggplantEquip.SetAsHighlighted(eEquipedItem == EQUIP_Eggplant);
	m_BtnEggplantEquip.SetAsEnabled(Values::Get()->m_uiSeedsEggplant > 0);

	m_BtnEggplantBuy.SetAsEnabled(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_EGGPLANTSEEDS));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsPumpkin);
	m_BtnPumpkinEquip.SetText(sText);
	m_BtnPumpkinEquip.SetAsHighlighted(eEquipedItem == EQUIP_Pumpkin);
	m_BtnPumpkinEquip.SetAsEnabled(Values::Get()->m_uiSeedsPumpkin > 0);

	m_BtnPumpkinBuy.SetAsEnabled(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_PUMPKINSEEDS));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsGernaium);
	m_BtnGernaiumEquip.SetText(sText);
	m_BtnGernaiumEquip.SetAsHighlighted(eEquipedItem == EQUIP_Gernaium);
	m_BtnGernaiumEquip.SetAsEnabled(Values::Get()->m_uiSeedsGernaium > 0);

	m_BtnGernaiumBuy.SetAsEnabled(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_GERNAIUMSEEDS));

	if(true)//Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
	{
		m_BtnGernaiumEquip.SetTint(HyColor(HIDDEN_BUTTON_TINT));
		//m_BtnGernaiumEquip.GetTextPtr()->SetVisible(false);
		m_BtnGernaiumBuy.SetTint(HyColor(HIDDEN_BUTTON_TINT));
		//m_BtnGernaiumBuy.GetTextPtr()->SetVisible(false);

		m_BtnGernaiumEquip.SetAsEnabled(false);
		m_BtnGernaiumBuy.SetAsEnabled(false);
	}
	else
	{
		//m_BtnGernaiumEquip.GetTextPtr()->SetVisible(true);
		m_BtnGernaiumEquip.SetTint(HyColor::White);
		//m_BtnGernaiumBuy.GetTextPtr()->SetVisible(true);
		m_BtnGernaiumBuy.SetTint(HyColor::White);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsMarigold);
	m_BtnMarigoldEquip.SetText(sText);
	m_BtnMarigoldEquip.SetAsHighlighted(eEquipedItem == EQUIP_Marigold);
	m_BtnMarigoldEquip.SetAsEnabled(Values::Get()->m_uiSeedsMarigold > 0);

	m_BtnMarigoldBuy.SetAsEnabled(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_MARIGOLDSEEDS));

	if(true)//Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
	{
		m_BtnMarigoldEquip.SetTint(HyColor(HIDDEN_BUTTON_TINT));
		//m_BtnMarigoldEquip.GetTextPtr()->SetVisible(false);
		m_BtnMarigoldBuy.SetTint(HyColor(HIDDEN_BUTTON_TINT));
		//m_BtnMarigoldBuy.GetTextPtr()->SetVisible(false);

		m_BtnMarigoldEquip.SetAsEnabled(false);
		m_BtnMarigoldBuy.SetAsEnabled(false);
	}
	else
	{
		//m_BtnMarigoldEquip.GetTextPtr()->SetVisible(true);
		m_BtnMarigoldEquip.SetTint(HyColor::White);
		//m_BtnMarigoldBuy.GetTextPtr()->SetVisible(true);
		m_BtnMarigoldBuy.SetTint(HyColor::White);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	sText = "Seeds ";
	sText += std::to_string(Values::Get()->m_uiSeedsVine);
	m_BtnVineEquip.SetText(sText);
	m_BtnVineEquip.SetAsHighlighted(eEquipedItem == EQUIP_Vine);
	m_BtnVineEquip.SetAsEnabled(Values::Get()->m_uiSeedsVine > 0);

	m_BtnVineBuy.SetAsEnabled(Values::Get()->m_iSavings >= static_cast<int32>(Values::Get()->m_uiCOST_VINESEEDS));

	if(true)//Values::Get()->m_uiCurrentDay < Values::Get()->m_uiENABLE_DEFENSE_DAY)
	{
		m_BtnVineEquip.SetTint(HyColor(HIDDEN_BUTTON_TINT));
		//m_BtnVineEquip.GetTextPtr()->SetVisible(false);
		m_BtnVineBuy.SetTint(HyColor(HIDDEN_BUTTON_TINT));
		//m_BtnVineBuy.GetTextPtr()->SetVisible(false);

		m_BtnVineEquip.SetAsEnabled(false);
		m_BtnVineBuy.SetAsEnabled(false);
	}
	else
	{
		//m_BtnVineEquip.GetTextPtr()->SetVisible(true);
		m_BtnVineEquip.SetTint(HyColor::White);
		//m_BtnVineBuy.GetTextPtr()->SetVisible(true);
		m_BtnVineBuy.SetTint(HyColor::White);
	}
}

/*virtual*/ void HousePanel::OnContainerUpdate() /*override*/
{
	if(m_AirConditionText.IsVisible() && m_AirConditionText.pos.IsAnimating() == false)
		m_AirConditionText.pos.Tween(15.0f, m_AirConditionText.pos.Y(), 0.5f, HyTween::QuadOut, [this](IHyNode *) { m_AirConditionText.pos.Tween(0.0f, m_AirConditionText.pos.Y(), 0.5f, HyTween::QuadIn); });
}

/*virtual*/ float HousePanel::OnBeginShow() /*override*/
{
	const float fTransitionDur = 0.5f;

	rot.Set(90.0f);
	rot.Tween(0.0f, fTransitionDur, HyTween::QuadOut);
	alpha.Set(1.0f);

	pos.Set(static_cast<float>(HyEngine::Window().GetWidth()) - GetSize().x, 0.0f);
	rot_pivot.Set(static_cast<float>(HyEngine::Window().GetWindowSize().x), 0.0f);

	m_FoodStocks.Show();
	m_FoodStocks.pos.Set(0.0f + 50.0f, GetSize().y - 195.0f);

	m_SavingsVal.SetState(1);
	m_SavingsVal.SetTextAlignment(HYALIGN_Right);
	m_SavingsVal.pos.Set(GetSize().x - 10.0f, GetSize().y - 19.0f);

	m_DamagesVal.SetState(1);
	m_DamagesVal.SetTextAlignment(HYALIGN_Right);
	m_DamagesVal.pos.Set(GetSize().x - 10.0f, GetSize().y - 44.0f);
	m_DamagesVal.SetLayerColor(0, 1, HyColor(PAY_COLORS), HyColor(PAY_COLORS));

	const float fButtonSideMargin = 5.0f;
	const float fButtonBotMargin = 35.0f;
	const float fButtonOffsetX = 90.0f;
	const float fButtonOffsetY = 110.0f;

	const float fDecalOffsetX = 20.0f;
	const float fDecalOffsetY = 10.0f;

	const float fBuyButtonOffsetY = -30.0f;

	ChildAppend(m_BtnHoeEquip);
	m_BtnHoeEquip.SetText("  Hoe  ");
	m_BtnHoeEquip.SetTextState(1);
	m_BtnHoeEquip.alpha.Set(1.0f);
	//m_BtnHoeEquip.pos.Set(GetSize().x, 0);
	//m_BtnHoeEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 2.5f), fButtonBotMargin + (fButtonOffsetY * 1.0f)  + 70.0f);
	m_BtnHoeEquip.SetTag(EQUIP_Hoe);

	m_BtnHoeDecal.pos.Set(0.0f, 0.0f);
	m_BtnHoeDecal.pos.Offset(fDecalOffsetX + 19.0f, fDecalOffsetY + 25.0f);
	m_BtnHoeDecal.scale.Set(2.0f, 2.0f);
	//m_BtnHoeEquip.GetTextPtr()->SetDisplayOrder(m_BtnHoeDecal.GetDisplayOrder() + 1);
	
	ChildAppend(m_BtnHarvestEquip);
	m_BtnHarvestEquip.SetText("Harvest");
	m_BtnHarvestEquip.SetTextState(1);
	m_BtnHarvestEquip.alpha.Set(1.0f);
	//m_BtnHarvestEquip.pos.Set(GetSize().x, 0);
	//m_BtnHarvestEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 1.5f), fButtonBotMargin + (fButtonOffsetY * 1.0f) + 70.0f);
	m_BtnHarvestEquip.SetTag(EQUIP_Harvest);

	m_BtnHarvestDecal.pos.Set(0.0f, 0.0f);
	m_BtnHarvestDecal.pos.Offset(fDecalOffsetX + 10.0f, fDecalOffsetY + 25.0f);
	m_BtnHarvestDecal.scale.Set(2.0f, 2.0f);
	//m_BtnHarvestEquip.GetTextPtr()->SetDisplayOrder(m_BtnHarvestDecal.GetDisplayOrder() + 1);

	ChildAppend(m_BtnCornEquip);
	m_BtnCornEquip.alpha.Set(1.0f);
	m_BtnCornEquip.SetTextState(1);
	//m_BtnCornEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	//m_BtnCornEquip.pos.Set(GetSize().x, 0);
	//m_BtnCornEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 3.0f), fButtonBotMargin + (fButtonOffsetY * 1.0f));
	m_BtnCornEquip.SetTag(EQUIP_Corn);

	m_BtnCornDecal.SetState(PLANTSTATE_Harvest);
	m_BtnCornDecal.pos.Set(0.0f, 0.0f);
	m_BtnCornDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnCornDecal.scale.Set(2.0f, 2.0f);
	//m_BtnCornEquip.GetTextPtr()->SetDisplayOrder(m_BtnCornDecal.GetDisplayOrder() + 1);

	std::string sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_CORNSEEDS);
	m_BtnCornBuy.SetText(sText);
	m_BtnCornBuy.SetTextState(1);
	//m_BtnCornBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnCornBuy.pos.Set(m_BtnCornEquip.pos);
	m_BtnCornBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnCornBuy.SetTag(EQUIP_Corn);
	m_BtnCornBuy.SetTint(HyColor::Green);

	ChildAppend(m_BtnEggplantEquip);
	m_BtnEggplantEquip.alpha.Set(1.0f);
	m_BtnEggplantEquip.SetTextState(1);
	//m_BtnEggplantEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnEggplantEquip.pos.Set(GetSize().x, 0);
	m_BtnEggplantEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 2.0f), fButtonBotMargin + (fButtonOffsetY * 1.0f));
	m_BtnEggplantEquip.SetTag(EQUIP_Eggplant);

	m_BtnEggplantDecal.SetState(PLANTSTATE_Harvest);
	m_BtnEggplantDecal.pos.Set(0.0f, 0.0f);
	m_BtnEggplantDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnEggplantDecal.scale.Set(2.0f, 2.0f);
	//m_BtnEggplantEquip.GetTextPtr()->SetDisplayOrder(m_BtnEggplantDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_EGGPLANTSEEDS);
	m_BtnEggplantBuy.SetText(sText);
	m_BtnEggplantBuy.SetTextState(1);
	//m_BtnEggplantBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnEggplantBuy.pos.Set(m_BtnEggplantEquip.pos);
	m_BtnEggplantBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnEggplantBuy.SetTag(EQUIP_Eggplant);
	m_BtnEggplantBuy.SetTint(HyColor(0.0f, 1.0f, 0.0f));

	ChildAppend(m_BtnPumpkinEquip);
	m_BtnPumpkinEquip.alpha.Set(1.0f);
	m_BtnPumpkinEquip.SetTextState(1);
	//m_BtnPumpkinEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnPumpkinEquip.pos.Set(GetSize().x, 0);
	m_BtnPumpkinEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 1.0f), fButtonBotMargin + (fButtonOffsetY * 1.0f));
	m_BtnPumpkinEquip.SetTag(EQUIP_Pumpkin);

	m_BtnPumpkinDecal.SetState(PLANTSTATE_Harvest);
	m_BtnPumpkinDecal.pos.Set(0.0f, 0.0f);
	m_BtnPumpkinDecal.pos.Offset(fDecalOffsetX - 4.0f, fDecalOffsetY + 10.0f);
	m_BtnPumpkinDecal.scale.Set(1.3f, 1.3f);
	//m_BtnPumpkinEquip.GetTextPtr()->SetDisplayOrder(m_BtnPumpkinDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_PUMPKINSEEDS);
	m_BtnPumpkinBuy.SetText(sText);
	m_BtnPumpkinBuy.SetTextState(1);
	//m_BtnPumpkinBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnPumpkinBuy.pos.Set(m_BtnPumpkinEquip.pos);
	m_BtnPumpkinBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnPumpkinBuy.SetTag(EQUIP_Pumpkin);
	m_BtnPumpkinBuy.SetTint(HyColor(0.0f, 1.0f, 0.0f));

	ChildAppend(m_BtnGernaiumEquip);
	m_BtnGernaiumEquip.alpha.Set(1.0f);
	m_BtnGernaiumEquip.SetTextState(1);
	//m_BtnGernaiumEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnGernaiumEquip.pos.Set(GetSize().x, 0);
	m_BtnGernaiumEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 3.0f), fButtonBotMargin);
	m_BtnGernaiumEquip.SetTag(EQUIP_Gernaium);

	m_BtnGernaiumDecal.SetState(PLANTSTATE_Harvest);
	m_BtnGernaiumDecal.pos.Set(0.0f, 0.0f);
	m_BtnGernaiumDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnGernaiumDecal.scale.Set(2.0f, 2.0f);
	//m_BtnGernaiumEquip.GetTextPtr()->SetDisplayOrder(m_BtnGernaiumDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_GERNAIUMSEEDS);
	m_BtnGernaiumBuy.SetText(sText);
	m_BtnGernaiumBuy.SetTextState(1);
	//m_BtnGernaiumBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnGernaiumBuy.pos.Set(m_BtnGernaiumEquip.pos);
	m_BtnGernaiumBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnGernaiumBuy.SetTag(EQUIP_Gernaium);
	m_BtnGernaiumBuy.SetTint(HyColor(0.0f, 1.0f, 0.0f));

	ChildAppend(m_BtnMarigoldEquip);
	m_BtnMarigoldEquip.alpha.Set(1.0f);
	m_BtnMarigoldEquip.SetTextState(1);
	//m_BtnMarigoldEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnMarigoldEquip.pos.Set(GetSize().x, 0);
	m_BtnMarigoldEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 2.0f), fButtonBotMargin);
	m_BtnMarigoldEquip.SetTag(EQUIP_Marigold);

	m_BtnMarigoldDecal.SetState(PLANTSTATE_Harvest);
	m_BtnMarigoldDecal.pos.Set(0.0f, 0.0f);
	m_BtnMarigoldDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	m_BtnMarigoldDecal.scale.Set(2.0f, 2.0f);
	//m_BtnMarigoldEquip.GetTextPtr()->SetDisplayOrder(m_BtnMarigoldDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_MARIGOLDSEEDS);
	m_BtnMarigoldBuy.SetText(sText);
	m_BtnMarigoldBuy.SetTextState(1);
	//m_BtnMarigoldBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnMarigoldBuy.pos.Set(m_BtnMarigoldEquip.pos);
	m_BtnMarigoldBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnMarigoldBuy.SetTag(EQUIP_Marigold);
	m_BtnMarigoldBuy.SetTint(HyColor(0.0f, 1.0f, 0.0f));

	ChildAppend(m_BtnVineEquip);
	m_BtnVineEquip.alpha.Set(1.0f);
	m_BtnVineEquip.SetTextState(1);
	//m_BtnVineEquip.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnVineEquip.pos.Set(GetSize().x, 0);
	m_BtnVineEquip.pos.Offset(-fButtonSideMargin - (fButtonOffsetX * 1.0f), fButtonBotMargin);
	m_BtnVineEquip.SetTag(EQUIP_Vine);

	m_BtnVineDecal.SetState(PLANTSTATE_Harvest);
	m_BtnVineDecal.pos.Set(0.0f, 0.0f);
	m_BtnVineDecal.pos.Offset(fDecalOffsetX, fDecalOffsetY);
	//m_BtnVineEquip.GetTextPtr()->SetDisplayOrder(m_BtnVineDecal.GetDisplayOrder() + 1);

	sText = "Buy $";
	sText += std::to_string(Values::Get()->m_uiCOST_VINESEEDS);
	m_BtnVineBuy.SetText(sText);
	m_BtnVineBuy.SetTextState(1);
	//m_BtnVineBuy.GetTextPtr()->TextSetAlignment(HYALIGN_Center);
	m_BtnVineBuy.pos.Set(m_BtnVineEquip.pos);
	m_BtnVineBuy.pos.Offset(0.0f, fBuyButtonOffsetY);
	m_BtnVineBuy.SetTag(EQUIP_Vine);
	m_BtnVineBuy.SetTint(HyColor(0.0f, 1.0f, 0.0f));

	m_AirConditionText.SetText("< A/C bonus!");
	m_AirConditionText.SetState(1);
	m_AirConditionText.SetLayerColor(0, 1, HyColor(145, 176, 219), HyColor(0, 111, 255));
	//m_AirConditionText.TextSetAlignment(HYALIGN_Left);
	m_AirConditionText.pos.Set(0.0f, 0.0f);
	m_AirConditionText.pos.Offset(0.0f, 75.0f);
	m_AirConditionText.alpha.Set(Values::Get()->m_bAirConditioning ? 1.0f : 0.0f);

	Sync();

	return fTransitionDur;
}

/*virtual*/ void HousePanel::OnShown() /*override*/
{
}

/*virtual*/ float HousePanel::OnBeginHide() /*override*/
{
	rot.Tween(90.0f, 0.5f, HyTween::QuadOut);
	return 0.5f;
}

/*virtual*/ void HousePanel::OnHidden() /*override*/
{
	SetEquipedUI();
}
