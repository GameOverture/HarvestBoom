#include "pch.h"
#include "EquipButton.h"
#include "HousePanel.h"

EquipButton::EquipButton(const InfoPanelInit &infoPanelInitRef, HyEntity2d *pParent) :	InfoPanel(infoPanelInitRef, pParent)
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

	HousePanel *pThis = reinterpret_cast<HousePanel *>(pUserParam);
	pThis->Sync();
}
