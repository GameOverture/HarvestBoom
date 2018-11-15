#pragma once
#include "pch.h"

class Stamina;
class World;

class DayNight : public HyEntity2d
{
	World &				m_WorldRef;
	Stamina &			m_StaminaRef;
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
		STATE_Outro,
		STATE_Night
	};
	State				m_eState;
	float				m_fElapsedTime;
	
public:
	DayNight(World &worldRef, Stamina &staminaRef, HyEntity2d *pParent);
	virtual ~DayNight();

	float GetTime();
	bool IsCycling();
	bool IsNight();

	void Reset();
	void Start();

	void OffsetTime(float fTimeOffset);
	void SetTime(float fTime);

protected:
	virtual void OnLoaded() override;
	
	virtual void OnUpdate() override;
};

