#include "pch.h"
#include "IPanel.h"

IPanel::IPanel(glm::vec2 vDimensions, HyEntity2d *pParent) :
	HyEntity2d(pParent),
	m_vDIMENSIONS(vDimensions),
	m_fElapsedTime(0.0f),
	m_ePanelState(PANELSTATE_Hidden),
	m_PanelFill(this),
	m_PanelFrameOutline(this),
	m_PanelFrame(this)
{
	glm::vec2 ptFrameVerts[4];
	HySetVec(ptFrameVerts[0], 0.0f, 0.0f);
	HySetVec(ptFrameVerts[1], 0.0f, m_vDIMENSIONS.y);
	HySetVec(ptFrameVerts[2], m_vDIMENSIONS.x, m_vDIMENSIONS.y);
	HySetVec(ptFrameVerts[3], m_vDIMENSIONS.x, 0.0f);

	m_PanelFill.GetShape().SetAsBox(ptFrameVerts[3].x - ptFrameVerts[0].x, ptFrameVerts[1].y - ptFrameVerts[0].y);
	m_PanelFill.pos.Set(ptFrameVerts[0]);
	m_PanelFill.alpha.Set(0.9f);
	m_PanelFill.topColor.Set(0.0f, 0.0f, 0.0f);

	m_PanelFrameOutline.GetShape().SetAsLineLoop(ptFrameVerts, 4);
	m_PanelFrameOutline.SetLineThickness(8.0f);
	m_PanelFrameOutline.topColor.Set(190.0f / 255.0f, 100.0f / 255.0f, 32.0f / 255.0f);

	m_PanelFrame.GetShape().SetAsLineLoop(ptFrameVerts, 4);
	m_PanelFrame.SetLineThickness(4.0f);
	m_PanelFrame.topColor.Set(84.0f / 255.0f, 105.0f / 255.0f, 85.0f / 255.0f);

	SetDisplayOrder(DISPLAYORDER_Panel);
	UseWindowCoordinates();
	SetEnabled(false);
}

IPanel::~IPanel()
{
}

float IPanel::GetWidth()
{
	return m_vDIMENSIONS.x;
}

float IPanel::GetHeight()
{
	return m_vDIMENSIONS.y;
}

/*virtual*/ void IPanel::Show()
{
	if(IsShown() || IsTransition())
		return;

	SetEnabled(true);
	m_fElapsedTime = OnShow();
	m_ePanelState = PANELSTATE_Showing;
}

/*virtual*/ void IPanel::Hide()
{
	if(IsShown() == false || IsTransition())
		return;

	m_fElapsedTime = OnHide();
	m_ePanelState = PANELSTATE_Hiding;
}

bool IPanel::IsTransition()
{
	return m_ePanelState == PANELSTATE_Showing || m_ePanelState == PANELSTATE_Hiding;
}

bool IPanel::IsShown()
{
	return m_ePanelState == PANELSTATE_Shown;
}

/*virtual*/ void IPanel::OnUpdate() /*override*/
{
	if(m_fElapsedTime > 0.0f)
	{
		m_fElapsedTime -= Hy_UpdateStep();
		return;
	}

	switch(m_ePanelState)
	{
	case PANELSTATE_Showing:
		m_ePanelState = PANELSTATE_Shown;
		OnShown();
		break;

	case PANELSTATE_Hiding:
		m_ePanelState = PANELSTATE_Hidden;
		SetEnabled(false);
		OnHidden();
		break;
	}

	m_fElapsedTime = 0.0f;
}
