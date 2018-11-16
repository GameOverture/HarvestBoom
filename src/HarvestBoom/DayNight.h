#pragma once
#include "pch.h"

class Stamina;
class HousePanel;

class DayNight : public HyEntity2d
{
	Stamina &						m_StaminaRef;
	HousePanel &					m_HousePanelRef;
	float							m_fTime;

	HyEntityLeaf2d<HySprite2d>		m_EmblemEnt;
	HySprite2d						m_Bar;

	HyPrimitive2d					m_DayNight;

	HyText2d						m_MainText;

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
	DayNight(Stamina &staminaRef, HousePanel &housePanelRef, HyEntity2d *pParent);
	virtual ~DayNight();

	float GetTime();
	bool IsCycling();
	bool IsNight();

	void HideUI();
	void Start();

	void FadeToPitchBlack();
	bool IsPitchBlack();

	void OffsetTime(float fTimeOffset);
	void SetTime(float fTime);

protected:
	virtual void OnLoaded() override;
	
	virtual void OnUpdate() override;
};

