#include "pch.h"
#include "BuyButton.h"
#include "HousePanel.h"

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
	//LgParam stateId;
	//GetTelnet()->GetParamData(CP_N_STATE, stateId);

	//// Bet cannot be changed during a recall replay
	//if(stateId.GetIntVal() == BCKEND_RECALL_REPLAY)
	//	return;

	//LgDenom *pDenom = reinterpret_cast<LgDenom *>(pUserParam);
	//switch(m_eBtnType)
	//{
	//case LGDENOM_IncBtn:
	//	pDenom->OnIncrementDenomBtn();
	//	break;

	//case LGDENOM_DecBtn:
	//	pDenom->OnDecrementDenomBtn();
	//	break;
	//	
	//case LGDENOM_SelBtn:
	//	pDenom->OnSelectDenomBtn(static_cast<uint32>(GetTag()));
	//	break;
	//}
}
