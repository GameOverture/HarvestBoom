#pragma once
#include "pch.h"

#include "IPanel.h"

class IntroPanel : public IPanel
{
	HyText2d				m_txtHeader;
	HyText2d				m_txtIntro;

public:
	IntroPanel(HyEntity2d *pParent);
	virtual ~IntroPanel();

	virtual void Construct() override;
};
