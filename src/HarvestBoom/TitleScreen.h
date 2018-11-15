#pragma once
#include "pch.h"

class TitleScreen : public HyEntity2d
{
	HyPrimitive2d		m_Splash;

	HySprite2d			m_Panel;
	HyText2d			m_Title;

	HyText2d			m_txtPlay;
	HyText2d			m_txtQuit;
	HyText2d			m_Selector;

	HyPrimitive2d		m_LegalBg;
	HyText2d			m_Legal;

public:
	TitleScreen(glm::ivec2 vResolution);
	virtual ~TitleScreen();

	void Construct();
	void Start();

	TitleScreenValue GameUpdate();
};

