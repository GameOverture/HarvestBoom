#pragma once
#include "pch.h"

class IntroPanel : public HyUiContainer
{
	HyLabel				m_HeaderText;
	HyLabel				m_BodyText;

public:
	IntroPanel(HyEntity2d *pParent);
	virtual ~IntroPanel();

	virtual float OnBeginShow() override;
	virtual void OnShown() override;
	virtual float OnBeginHide() override;
	virtual void OnHidden() override;

	bool IntroUpdate();
};
