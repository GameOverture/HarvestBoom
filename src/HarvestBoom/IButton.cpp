#include "pch.h"
#include "EquipButton.h"
#include "HousePanel.h"
#include "HarvestBoom.h"

EquipButton::EquipButton(HyEntity2d *pParent) :	InfoPanel("Game", "EquipButton", "Game", "Small", 8, 5, 70, 35, pParent)
{

}

bool EquipButton::IsUsed()
{
	return m_pPanel != nullptr;
}

/*virtual*/ void EquipButton::OnMouseDown(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Down);
}

/*virtual*/ void EquipButton::OnMouseUp(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Pressable);
}

/*virtual*/ void EquipButton::OnMouseLeave(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Pressable);
}

/*virtual*/ void EquipButton::OnMouseClicked(void *pUserParam) /*override*/
{
	Values::Get()->m_eEquipedItem = static_cast<EquipedItemType>(GetTag());

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FOOTSTEP_1);

	HousePanel *pThis = reinterpret_cast<HousePanel *>(pUserParam);
	pThis->Sync();
}
