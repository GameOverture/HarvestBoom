#include "pch.h"
#include "BuyButton.h"
#include "HousePanel.h"
#include "HarvestBoom.h"

BuyButton::BuyButton(const InfoPanelInit &infoPanelInitRef, HyEntity2d *pParent) :	InfoPanel(infoPanelInitRef, pParent)
{

}

bool BuyButton::IsUsed()
{
	return m_pPanel != nullptr;
}

/*virtual*/ void BuyButton::OnMouseDown(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Down);
}

/*virtual*/ void BuyButton::OnMouseUp(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Pressable);
}

/*virtual*/ void BuyButton::OnMouseLeave(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Pressable);
}

/*virtual*/ void BuyButton::OnMouseClicked(void *pUserParam) /*override*/
{
	HousePanel *pThis = reinterpret_cast<HousePanel *>(pUserParam);

	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_BUYSTUFF);

	switch(static_cast<EquipedItemType>(GetTag()))
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
	}
	
	pThis->Sync();
}
