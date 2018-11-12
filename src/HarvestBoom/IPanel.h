#pragma once
#include "pch.h"

class IPanel : public HyEntity2d
{
protected:
	HyPrimitive2d			m_PanelFill;
	HyPrimitive2d			m_PanelFrameOutline;
	HyPrimitive2d			m_PanelFrame;

	glm::vec2				m_ptFrameVerts[4];

public:
	IPanel(HyEntity2d *pParent);
	virtual ~IPanel();

	virtual void Construct();

	void Show();
	void Hide();
	bool IsTransition();

	float PanelWidth();
	float PanelHeight();
};

