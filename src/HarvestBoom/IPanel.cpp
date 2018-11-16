#include "pch.h"
#include "IPanel.h"

IPanel::IPanel(glm::vec2 vDimensions, HyEntity2d *pParent) :	HyEntity2d(pParent),
																m_vDimensions(vDimensions),
																m_PanelFill(this),
																m_PanelFrameOutline(this),
																m_PanelFrame(this)
{
	glm::vec2 ptFrameVerts[4];
	HySetVec(ptFrameVerts[0], 0.0f, 0.0f);
	HySetVec(ptFrameVerts[1], 0.0f, m_vDimensions.y);
	HySetVec(ptFrameVerts[2], m_vDimensions.x, m_vDimensions.y);
	HySetVec(ptFrameVerts[3], m_vDimensions.x, 0.0f);

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

/*virtual*/ void IPanel::Show()
{
	SetEnabled(true);
	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	pos.Tween(0.0f, 0.0f, 1.0f, HyTween::QuadOut, [this](IHyNode *pThis) { m_bIsShowing = true; });
}

/*virtual*/ void IPanel::Hide()
{
	if(IsShowing() == false || IsTransition())
		return;

	pos.Tween(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f, 1.0f, HyTween::QuadIn, [this](IHyNode *pThis) { SetEnabled(false); m_bIsShowing = false; });
}

/*virtual*/ bool IPanel::IsTransition()
{
	return pos.IsTweening();
}
