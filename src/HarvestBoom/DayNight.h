#pragma once
#include "pch.h"

class DayNight : public HyEntity2d
{
	float				m_fTime;

	HySprite2d			m_Emblem;
	HySprite2d			m_Bar;

	HyPrimitive2d		m_DayNight;

	HyText2d			m_MainText;

	enum State
	{
		STATE_Off = 0,
		STATE_Intro,
		STATE_IntroBounce,
		STATE_IntroFade,
		STATE_Cycling,
		STATE_CountDown,
		STATE_Night
	};
	State				m_eState;
	
public:
	DayNight(HyEntity2d *pParent);
	virtual ~DayNight();

	float GetTime();
	bool IsCycling();

	void Start();

	void OffsetTime(float fTimeOffset);
	void SetTime(float fTime);

protected:
	virtual void OnLoaded() override;
	
	virtual void OnUpdate() override;
};

