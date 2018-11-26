#include "pch.h"
#include "ContinueButton.h"
#include "BillsPanel.h"
#include "HarvestBoom.h"

ContinueButton::ContinueButton(HyEntity2d *pParent) :	InfoPanel("Game", "EquipButton", "Game", "Small", 4, 20, 70, 35, pParent)
{

}

bool ContinueButton::IsUsed()
{
	return m_pPanel != nullptr;
}

/*virtual*/ void ContinueButton::OnMouseDown(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		m_pPanel->AnimSetState(HYBUTTONSTATE_Down);
}

/*virtual*/ void ContinueButton::OnMouseUp(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		m_pPanel->AnimSetState(HYBUTTONSTATE_Pressable);
}

/*virtual*/ void ContinueButton::OnMouseLeave(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != HYBUTTONSTATE_Selected)
		m_pPanel->AnimSetState(HYBUTTONSTATE_Pressable);
}

/*virtual*/ void ContinueButton::OnMouseClicked(void *pUserParam) /*override*/
{
	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);

	BillsPanel *pThis = reinterpret_cast<BillsPanel *>(pUserParam);
	pThis->Hide();
}
