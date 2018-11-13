#pragma once
#include "pch.h"

#define PANEL_SIDEMARGIN 20.0f
#define PANEL_TOPMARGIN 50.0f

class IPanel : public HyEntity2d
{
protected:
	HyPrimitive2d			m_PanelFill;
	HyPrimitive2d			m_PanelFrameOutline;
	HyPrimitive2d			m_PanelFrame;

	glm::vec2				m_ptFrameVerts[4];
	bool					m_bCustomVerts;
	bool					m_bIsShowing;

public:
	IPanel(HyEntity2d *pParent);
	IPanel(std::vector<glm::vec2> frameVertList, HyEntity2d *pParent);
	virtual ~IPanel();

	virtual void Construct();

	virtual void Show();
	virtual void Hide();
	virtual bool IsTransition();
	bool IsShowing();

	float PanelWidth();
	float PanelHeight();
};

