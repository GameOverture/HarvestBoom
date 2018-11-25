#include "pch.h"
#include "FoodButton.h"
#include "FoodStuffs.h"
#include "HarvestBoom.h"

FoodButton::FoodButton(PlantType ePlantType, bool bIsSellBtn, const char *szPanelPrefix, const char *szPanelName, HyEntity2d *pParent) :
	InfoPanel(szPanelPrefix, szPanelName, HY_SYSTEM_FONT, 8, 3, 65, 30, pParent),
	m_ePLANT_TYPE(ePlantType),
	m_bIS_SELL_BTN(bIsSellBtn),
	m_eButtonState(BTNSTATE_Pressable)
{
}

void FoodButton::Sync(FoodStuffs &foodStuffsRef)
{
	bool bEnable = true;
	switch(m_ePLANT_TYPE)
	{
	case PLANTTYPE_Corn:
		bEnable = Values::Get()->m_uiHarvestCorn > 0;
		break;

	case PLANTTYPE_Eggplant:
		bEnable = Values::Get()->m_uiHarvestEggplant > 0;
		break;

	case PLANTTYPE_Pumpkin:
		bEnable = Values::Get()->m_uiHarvestPumpkin > 0;
		break;
	}

	if(bEnable)
	{
		EnableMouseInput(&foodStuffsRef);
		m_pPanel->SetTint(1.0f, 1.0f, 1.0f);
		m_eButtonState = BTNSTATE_Pressable;
	}
	else
	{
		DisableMouseInput();
		m_pPanel->SetTint(0.25f, 0.25f, 0.25f);
		m_eButtonState = BTNSTATE_Disabled;
	}
}

/*virtual*/ void FoodButton::OnMouseDown(void *pUserParam) /*override*/
{
	m_pPanel->SetTint(1.0f, 0.0f, 0.0f);
	m_eButtonState = BTNSTATE_Down;
}

/*virtual*/ void FoodButton::OnMouseUp(void *pUserParam) /*override*/
{
	m_pPanel->SetTint(1.0f, 1.0f, 1.0f);
	m_eButtonState = BTNSTATE_Pressable;
}

/*virtual*/ void FoodButton::OnMouseLeave(void *pUserParam) /*override*/
{
	m_pPanel->SetTint(1.0f, 1.0f, 1.0f);
	m_eButtonState = BTNSTATE_Pressable;
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
	
	FoodStuffs *pThis = reinterpret_cast<FoodStuffs *>(pUserParam);
	pThis->Sync();
}
