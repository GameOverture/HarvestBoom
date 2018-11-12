#include "pch.h"
#include "IPanel.h"

#define PANEL_SIDEMARGIN 20.0f
#define PANEL_TOPMARGIN 50.0f

IPanel::IPanel(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_PanelFill(this),
										m_PanelFrameOutline(this),
										m_PanelFrame(this)
{
}

IPanel::~IPanel()
{
}

/*virtual*/ void IPanel::Construct()
{
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	m_PanelFill.GetShape().SetAsBox(vWindowSize.x - (PANEL_SIDEMARGIN * 2.0f), vWindowSize.y - (PANEL_TOPMARGIN * 2.0f));
	m_PanelFill.pos.Set(PANEL_SIDEMARGIN, PANEL_TOPMARGIN);
	m_PanelFill.alpha.Set(0.9f);
	m_PanelFill.topColor.Set(0.0f, 0.0f, 0.0f);

	HySetVec(m_ptFrameVerts[0], PANEL_SIDEMARGIN, PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[1], PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[2], vWindowSize.x - PANEL_SIDEMARGIN, vWindowSize.y - PANEL_TOPMARGIN);
	HySetVec(m_ptFrameVerts[3], vWindowSize.x - PANEL_SIDEMARGIN, PANEL_TOPMARGIN);

	m_PanelFrameOutline.GetShape().SetAsLineLoop(m_ptFrameVerts, 4);
	m_PanelFrameOutline.SetLineThickness(8.0f);
	m_PanelFrameOutline.topColor.Set(0.0f, 1.0f, 0.f);

	m_PanelFrame.GetShape().SetAsLineLoop(m_ptFrameVerts, 4);
	m_PanelFrame.SetLineThickness(4.0f);
	m_PanelFrame.topColor.Set(84.0f / 255.0f, 105.0f / 255.0f, 85.0f / 255.0f);

	pos.Set(static_cast<float>(-vWindowSize.x), 0.0f);
}

void IPanel::Show()
{
	pos.Set(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f);
	pos.Tween(0.0f, 0.0f, 1.0f, HyTween::QuadOut);
}

void IPanel::Hide()
{
	pos.Tween(static_cast<float>(-Hy_App().Window().GetWindowSize().x), 0.0f, 1.0f, HyTween::QuadIn);
}

bool IPanel::IsTransition()
{
	return pos.IsTweening();
}

float IPanel::PanelWidth()
{
	return m_ptFrameVerts[2].x - m_ptFrameVerts[1].x;
}

float IPanel::PanelHeight()
{
	return m_ptFrameVerts[2].y - m_ptFrameVerts[0].y;
}
