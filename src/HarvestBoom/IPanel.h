#pragma once
#include "pch.h"

class IPanel : public HyEntity2d
{
protected:
	glm::vec2				m_vDimensions;

	HyPrimitive2d			m_PanelFill;
	HyPrimitive2d			m_PanelFrameOutline;
	HyPrimitive2d			m_PanelFrame;

public:
	IPanel(glm::vec2 vDimensions, HyEntity2d *pParent);
	virtual ~IPanel();

	void Show();
	void Hide();

	virtual void OnShow() = 0;
	virtual void OnHide() = 0;
	virtual bool IsTransition() = 0;
	virtual bool IsShowing() = 0;
};

