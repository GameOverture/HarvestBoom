#include "pch.h"
#include "EquipButton.h"
#include "HousePanel.h"
#include "HarvestBoom.h"
//
//EquipButton::EquipButton(HyEntity2d *pParent) :
//	HyInfoPanel("Game", "EquipButton", "Game", "Small", 8, 5, 70, 35, pParent)
//{
//
//}
//
//bool EquipButton::IsUsed()
//{
//	return m_pPanel != nullptr;
//}
//
///*virtual*/ void EquipButton::OnMouseDown() /*override*/
//{
//	if(IsUsed() == false)
//		return;
//
//	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
//		m_pPanel->AnimSetState(HYBUTTONSTATE_Down);
//}
//
///*virtual*/ void EquipButton::OnMouseUp() /*override*/
//{
//	if(IsUsed() == false)
//		return;
//
//	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
//		m_pPanel->AnimSetState(HYBUTTONSTATE_Pressable);
//}
//
///*virtual*/ void EquipButton::OnMouseLeave() /*override*/
//{
//	if(IsUsed() == false)
//		return;
//
//	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
//		m_pPanel->AnimSetState(HYBUTTONSTATE_Pressable);
//}
//
///*virtual*/ void EquipButton::OnMouseClicked() /*override*/
//{
//	Values::Get()->m_eEquipedItem = static_cast<EquipedItemType>(GetTag());
//
//	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
//		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FOOTSTEP_1);
//
//	Values::Get()->Sync();
//}
