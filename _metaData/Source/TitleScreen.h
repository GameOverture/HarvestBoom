#pragma once
#include "pch.h"

class TitleScreen : public HyEntity2d
{
	HySprite2d			m_Panel;
	HyText2d			m_TitleText;

	HyText2d			m_PlayText;
	HyText2d			m_QuitText;
	HyText2d			m_Selector;

	HyPrimitive2d		m_LegalBg;
	HyText2d			m_LegalText;

	HyAudio2d			m_SfxSelector;

public:
	TitleScreen();
	virtual ~TitleScreen();

	void Start(TitleScreenType eTitleType);
	TitleScreenValue GameUpdate();
};

