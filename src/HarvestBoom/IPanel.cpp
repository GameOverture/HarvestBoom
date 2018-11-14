#include "pch.h"
#include "IPanel.h"

IPanel::IPanel(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_PanelFill(this),
										m_PanelFrameOutline(this),
										m_PanelFrame(this),
										m_bIsShowing(false),
										m_bCustomVerts(false)
{
	SetDisplayOrder(DISPLAYORDER_Panel);
	UseWindowCoordinates();
	SetEnabled(false);
}

IPanel::~IPanel()
{
}

/*virtual*/ void IPanel::Construct()
{
	if(m_bCustomVerts == false)
	{
		glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();
		HySetVec(m_ptFrameVerts[0], PANEL_SIDEMARGIN, PANEL_TOPMARGIN);
		HySetVec(m_ptFrameVerts[1], PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN);
		HySetVec(m_ptFrameVerts[2], vWindowSize.x - PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN);
		HySetVec(m_ptFrameVerts[3], vWindowSize.x - PANEL_SIDEMARGIN, PANEL_TOPMARGIN);
	}

	m_PanelFill.GetShape().SetAsBox(m_ptFrameVerts[3].x - m_ptFrameVerts[0].x, m_ptFrameVerts[1].y - m_ptFrameVerts[0].y);
	m_PanelFill.pos.Set(m_ptFrameVerts[0]);
	m_PanelFill.alpha.Set(0.9f);
	m_PanelFill.topColor.Set(0.0f, 0.0f, 0.0f);

	m_PanelFrameOutline.GetShape().SetAsLineLoop(m_ptFrameVerts, 4);
	m_PanelFrameOutline.SetLineThickness(8.0f);
	m_PanelFrameOutline.topColor.Set(190.0f / 255.0f, 100.0f / 255.0f, 32.0f / 255.0f);

	m_PanelFrame.GetShape().SetAsLineLoop(m_ptFrameVerts, 4);
	m_PanelFrame.SetLineThickness(4.0f);
	m_PanelFrame.topColor.Set(84.0f / 255.0f, 105.0f / 255.0f, 85.0f / 255.0f);
}

/*virtual*/ void IPanel::Show()
{
	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	pos.Tween(0.0f, 0.0f, 1.0f, HyTween::QuadOut, [this](IHyNode *pThis) { m_bIsShowing = true; });
}

/*virtual*/ void IPanel::Hide()
{
	pos.Tween(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f, 1.0f, HyTween::QuadIn, [this](IHyNode *pThis) { m_bIsShowing = false; });
}

/*virtual*/ bool IPanel::IsTransition()
{
	return pos.IsTweening();
}

bool IPanel::IsShowing()
{
	return m_bIsShowing;
}

float IPanel::PanelWidth()
{
	return m_ptFrameVerts[2].x - m_ptFrameVerts[1].x;
}

float IPanel::PanelHeight()
{
	return m_ptFrameVerts[2].y - m_ptFrameVerts[0].y;
}
