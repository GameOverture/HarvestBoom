#pragma once
#include "pch.h"
#include "IPanel.h"

class IntroPanel : public IPanel
{
	HyText2d				m_HeaderText;
	HyText2d				m_BodyText;

public:
	IntroPanel(glm::vec2 vDimensions, HyEntity2d *pParent);
	virtual ~IntroPanel();

	virtual float OnShow() override;
	virtual void OnShown() override;
	virtual float OnHide() override;
	virtual void OnHidden() override;
};
