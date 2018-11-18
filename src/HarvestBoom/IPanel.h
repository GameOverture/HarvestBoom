#pragma once
#include "pch.h"

class IPanel : public HyEntity2d
{
	const glm::vec2			m_vDIMENSIONS;
	float					m_fElapsedTime;

	enum PanelState
	{
		PANELSTATE_Hidden = 0,
		PANELSTATE_Showing,
		PANELSTATE_Shown,
		PANELSTATE_Hiding
	};
	PanelState				m_ePanelState;

protected:
	HyPrimitive2d			m_PanelFill;
	HyPrimitive2d			m_PanelFrameOutline;
	HyPrimitive2d			m_PanelFrame;

public:
	IPanel(glm::vec2 vDimensions, HyEntity2d *pParent);
	virtual ~IPanel();

	float GetWidth();
	float GetHeight();

	void Show();
	void Hide();

	bool IsTransition();
	bool IsShown();

	virtual float OnShow() = 0;	// Returns the duration (in seconds) of the shown transition
	virtual void OnShown() = 0;
	virtual float OnHide() = 0;	// Returns the duration (in seconds) of the hide transition
	virtual void OnHidden() = 0;

protected:
	virtual void OnUpdate() override;
};

