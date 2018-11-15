#include "pch.h"
#include "ContinueButton.h"
#include "BillsPanel.h"
#include "HarvestBoom.h"

ContinueButton::ContinueButton(const InfoPanelInit &infoPanelInitRef, HyEntity2d *pParent) :	InfoPanel(infoPanelInitRef, pParent)
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

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Down);
}

/*virtual*/ void ContinueButton::OnMouseUp(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Pressable);
}

/*virtual*/ void ContinueButton::OnMouseLeave(void *pUserParam) /*override*/
{
	if(IsUsed() == false)
		return;

	if(m_pPanel->AnimGetState() != BTNSTATE_Selected)
		m_pPanel->AnimSetState(BTNSTATE_Pressable);
}

/*virtual*/ void ContinueButton::OnMouseClicked(void *pUserParam) /*override*/
{
	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_MENU_CURSOR);

	BillsPanel *pThis = reinterpret_cast<BillsPanel *>(pUserParam);
	pThis->Hide();
}
