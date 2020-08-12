#include "pch.h"
#include "ContinueButton.h"
#include "BillsPanel.h"
#include "HarvestBoom.h"

ContinueButton::ContinueButton(HyEntity2d *pParent) :
	HyInfoPanel("Game", "EquipButton", "Game", "Small", 3, 15, 72, 45, pParent)
{

}

bool ContinueButton::IsUsed()
{
	return m_pPanel != nullptr;
}

/*virtual*/ void ContinueButton::OnMouseDown() /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		m_pPanel->AnimSetState(HYBUTTONSTATE_Down);
}

/*virtual*/ void ContinueButton::OnMouseUp() /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		m_pPanel->AnimSetState(HYBUTTONSTATE_Pressable);
}

/*virtual*/ void ContinueButton::OnMouseLeave() /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		m_pPanel->AnimSetState(HYBUTTONSTATE_Pressable);
}

/*virtual*/ void ContinueButton::OnMouseClicked() /*override*/
{
	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);

	BillsPanel *pThis = reinterpret_cast<BillsPanel *>(ParentGet());
	pThis->Hide();
}
