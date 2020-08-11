#pragma once
#include "pch.h"

class IntroPanel : public IHy9Slice
{
	HyText2d				m_HeaderText;
	HyText2d				m_BodyText;

public:
	IntroPanel(HyEntity2d *pParent);
	virtual ~IntroPanel();

	virtual float OnShow() override;
	virtual void OnShown() override;
	virtual float OnHide() override;
	virtual void OnHidden() override;

	bool IntroUpdate();
};
