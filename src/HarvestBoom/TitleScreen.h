#pragma once
#include "pch.h"

class TitleScreen : public HyEntity2d
{
	HyPrimitive2d		m_Panel;
	HyText2d			m_Title;

	HyText2d			m_txtPlay;
	HyText2d			m_txtQuit;
	HyText2d			m_Selector;

	HyText2d			m_Legal;

public:
	TitleScreen();
	virtual ~TitleScreen();

	void Construct();

	TitleScreenValue GameUpdate();
};

