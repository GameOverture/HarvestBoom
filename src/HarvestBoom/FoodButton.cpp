#include "pch.h"
#include "FoodButton.h"
#include "FoodStuffs.h"
#include "HarvestBoom.h"

FoodButton::FoodButton(PlantType ePlantType, bool bIsSellBtn, const char *szPanelPrefix, const char *szPanelName, HyEntity2d *pParent) :
	InfoPanel(szPanelPrefix, szPanelName, "Game", "Small", 8, 3, 65, 30, pParent),
	m_ePLANT_TYPE(ePlantType),
	m_bIS_SELL_BTN(bIsSellBtn),
	m_HoverRect(this)
{
	GetTextPtr()->TextSetState(1);
	GetTextPtr()->pos.Set(70.0f, 0.0f);
	GetTextPtr()->TextSetAlignment(HYALIGN_Right);
	m_HoverRect.GetShape().SetAsBox(140.0f, 35.0f);
	m_HoverRect.SetWireframe(true);
	m_HoverRect.SetTint(1.0f, 0.0f, 0.0f);
	m_HoverRect.SetEnabled(false);
}

void FoodButton::Sync()
{
	std::string sText = "* ";

	bool bEnable = true;
	switch(m_ePLANT_TYPE)
	{
	case PLANTTYPE_Corn:
		sText += std::to_string(Values::Get()->m_uiHarvestCorn);
		GetTextPtr()->TextSet(sText);
		GetPanelPtr()->pos.Set(10.0f, -5.0f);
		bEnable = Values::Get()->m_uiHarvestCorn > 0;
		break;

	case PLANTTYPE_Eggplant:
		sText += std::to_string(Values::Get()->m_uiHarvestEggplant);
		GetTextPtr()->TextSet(sText);
		GetPanelPtr()->pos.Set(10.0f, -5.0f);
		bEnable = Values::Get()->m_uiHarvestEggplant > 0;
		break;

	case PLANTTYPE_Pumpkin:
		sText += std::to_string(Values::Get()->m_uiHarvestPumpkin);
		GetTextPtr()->TextSet(sText);
		bEnable = Values::Get()->m_uiHarvestPumpkin > 0;
		break;
	}

	if(bEnable)
	{
		EnableMouseInput();
		m_pPanel->SetTint(1.0f, 1.0f, 1.0f);
	}
	else
	{
		DisableMouseInput();
		m_pPanel->SetTint(0.25f, 0.25f, 0.25f);
		m_HoverRect.SetEnabled(false);
	}
}

/*virtual*/ void FoodButton::OnMouseEnter(void *pUserParam) /*override*/
{
	m_HoverRect.SetEnabled(true);
}

/*virtual*/ void FoodButton::OnMouseLeave(void *pUserParam) /*override*/
{
	m_HoverRect.SetEnabled(false);

	m_pPanel->SetTint(1.0f, 1.0f, 1.0f);
}

/*virtual*/ void FoodButton::OnMouseDown(void *pUserParam) /*override*/
{
	m_pPanel->SetTint(1.0f, 0.0f, 0.0f);
}

/*virtual*/ void FoodButton::OnMouseUp(void *pUserParam) /*override*/
{
	m_pPanel->SetTint(1.0f, 1.0f, 1.0f);
}

/*virtual*/ void FoodButton::OnMouseClicked(void *pUserParam) /*override*/
{
	switch(m_ePLANT_TYPE)
	{
	case PLANTTYPE_Corn:
		Values::Get()->m_uiHarvestCorn--;
		if(m_bIS_SELL_BTN)
		{
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_BUYSTUFF);
			Values::Get()->m_uiHarvestSoldAmt += Values::Get()->m_uiHARVEST_CORNVALUE;
		}
		else
			Values::Get()->m_fStamina = HyClamp(Values::Get()->m_fStamina + Values::Get()->m_fSTAMINA_EATCORNMODIFIER, 0.0f, 1.0f);
		break;

	case PLANTTYPE_Eggplant:
		Values::Get()->m_uiHarvestEggplant--;
		if(m_bIS_SELL_BTN)
		{
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_BUYSTUFF);
			Values::Get()->m_uiHarvestSoldAmt += Values::Get()->m_uiHARVEST_EGGPLANTVALUE;
		}
		else
			Values::Get()->m_fStamina = HyClamp(Values::Get()->m_fStamina + Values::Get()->m_fSTAMINA_EATEGGPLANTMODIFIER, 0.0f, 1.0f);
		break;

	case PLANTTYPE_Pumpkin:
		Values::Get()->m_uiHarvestPumpkin--;
		if(m_bIS_SELL_BTN)
		{
			HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_BUYSTUFF);
			Values::Get()->m_uiHarvestSoldAmt += Values::Get()->m_uiHARVEST_PUMPKINVALUE;
		}
		else
			Values::Get()->m_fStamina = HyClamp(Values::Get()->m_fStamina + Values::Get()->m_fSTAMINA_EATPUMPKINMODIFIER, 0.0f, 1.0f);
		break;
	}

	Values::Get()->Sync();
}
