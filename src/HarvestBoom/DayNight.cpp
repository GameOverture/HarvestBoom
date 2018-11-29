#include "pch.h"
#include "DayNight.h"
#include "World.h"
#include "Stamina.h"
#include "HarvestBoom.h"

#define DAYNIGHT_SIDEMARGIN 50.0f
#define DAYNIGHT_TOPMARGIN 50.0f

#define DAYNIGHT_DARKNESSAMT 0.7f

DayNight::DayNight(Stamina &staminaRef, HousePanel &housePanelRef, HyEntity2d *pParent) :	HyEntity2d(pParent),
																							m_StaminaRef(staminaRef),
																							m_HousePanelRef(housePanelRef),
																							m_fTime(0.0f),
																							m_EmblemEnt("UI", "DayNight", this),
																							m_Bar("UI", "DayNightBar", this),
																							m_DayNight(this),
																							m_MainText("Game", "Main", this),
																							m_eState(STATE_Off),
																							m_fElapsedTime(0.0f)
{
	UseWindowCoordinates();
	SetDisplayOrder(DISPLAYORDER_UI);
	m_MainText.SetTag(1); // Skips the fake pause initially, but not on any consecutive day
}

DayNight::~DayNight()
{
}

float DayNight::GetTime()
{
	return m_fTime;
}

bool DayNight::IsCycling()
{
	return m_eState == STATE_Cycling || m_eState == STATE_CountDown;
}

bool DayNight::IsNight()
{
	return m_eState == STATE_Night;
}

void DayNight::HideUI()
{
	m_EmblemEnt.alpha.Tween(0.0f, -1.0f);
	m_Bar.alpha.Tween(0.0f, -1.0f);
	m_StaminaRef.pos.Tween(-100.0f, 50.0f, 1.0f);
	m_HousePanelRef.HideEquipedUI();
}

void DayNight::Start()
{
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	m_fTime = 0.0f;

	

	m_MainText.SetEnabled(true);
	m_MainText.pos.Set(vWindowSize.x * 0.5f, vWindowSize.y * 0.5f);
	m_MainText.alpha.Set(0.0f);
	m_MainText.alpha.Tween(1.0f, 0.25f);
	m_MainText.scale.Set(0.001f, 0.001f);
	m_MainText.scale.Tween(0.8f, 0.8f, 0.5f, HyTween::CubeOut);

	switch(m_MainText.GetTag())
	{
	case 0:
		{
			std::string sText = "Day ";
			sText += std::to_string(Values::Get()->m_uiCurrentDay);

			m_MainText.TextSet(sText);
			m_DayNight.alpha.Tween(0.0f, 2.5f);
			m_MainText.scale.Tween(0.8f, 0.8f, 2.5f, HyTween::CubeOut);
		}
		break;
	case 1:	m_MainText.TextSet("Good Morning!");
		//HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_ROOSTER_CROWING);
		break;
	case 2:
		m_MainText.TextSet("Get Set...");
		break;
	case 3:
		m_MainText.TextSet("GO!");
		break;
	}

	m_eState = STATE_Intro;
}

void DayNight::FadeToPitchBlack()
{
	HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_NIGHT_TRANSITION);
	m_DayNight.alpha.Tween(1.0f, 3.0f);
}

bool DayNight::IsPitchBlack()
{
	return m_DayNight.alpha.Get() == 1.0f;
}

void DayNight::OffsetTime(float fTimeOffset)
{
	SetTime(m_fTime + fTimeOffset);
}

void DayNight::SetTime(float fTime)
{
	m_fTime = fTime;
	m_fTime = HyClamp(m_fTime, 0.0f, Values::Get()->m_fDAY_LENGTH);

	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();
	float fNormalized = m_fTime / Values::Get()->m_fDAY_LENGTH;
	m_EmblemEnt.pos.Set(DAYNIGHT_SIDEMARGIN + (fNormalized * (vWindowSize.x - (DAYNIGHT_SIDEMARGIN * 2.0f))), vWindowSize.y - DAYNIGHT_TOPMARGIN);
	m_EmblemEnt.GetLeaf().rot.Set(fNormalized * 180.0f);

	m_DayNight.alpha.Set(fNormalized * DAYNIGHT_DARKNESSAMT);
}

/*virtual*/ void DayNight::OnLoaded() /*override*/
{
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	m_DayNight.GetShape().SetAsBox(vWindowSize.x, vWindowSize.y);
	m_DayNight.topColor.Set(0.0f, 0.0f, 0.0f);
	m_DayNight.SetDisplayOrder(DISPLAYORDER_DayNight);
	m_DayNight.alpha.Set(0.0f);
	
	m_EmblemEnt.pos.Set(DAYNIGHT_SIDEMARGIN, vWindowSize.y - DAYNIGHT_TOPMARGIN);

	m_Bar.scale.Y(2.0f);
	m_Bar.pos.Set(15.0f, vWindowSize.y - DAYNIGHT_TOPMARGIN);

	m_EmblemEnt.scale.Set(2.0f, 2.0f);

	m_MainText.pos.Set(vWindowSize.x * 0.5f, vWindowSize.y * 0.5f);
	m_MainText.TextSetAlignment(HYALIGN_Center);

	m_EmblemEnt.SetScissor(-50, 0, 100, 50);

	HideUI();
	Load();
}

/*virtual*/ void DayNight::OnUpdate() /*override*/
{
	switch(m_eState)
	{
	case STATE_Off:
		break;
	case STATE_Intro:
		if(m_MainText.scale.IsTweening() == false)
		{
			m_MainText.scale.Tween(0.6f, 0.6f, 0.5f, HyTween::QuadIn);
			m_eState = STATE_IntroBounce;
		}
		break;
	case STATE_IntroBounce:
		if(m_MainText.scale.IsTweening() == false)
		{
			m_MainText.alpha.Tween(0.0f, 1.0f, HyTween::QuadIn);
			m_eState = STATE_IntroFade;
		}
		break;

	case STATE_IntroFade:
		if(m_MainText.scale.IsTweening() == false)
		{
			m_MainText.SetTag(m_MainText.GetTag() + 1);
			if(m_MainText.GetTag() == 4)
			{
				m_MainText.SetTag(0);

				HarvestBoom::GetSndBank()->Stop(XACT_CUE_BASEGAME_FARM_WIN);
				LtGAudioManager::GetInstance()->RestoreMusicVol();
				HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_DAY_90SEC);

				m_Bar.alpha.Tween(1.0f, 1.0f);
				m_EmblemEnt.alpha.Tween(1.0f, 1.0f);
				m_StaminaRef.pos.Tween(20.0f, 50.0f, 1.0f, HyTween::QuadOut);
				m_HousePanelRef.SetEquipedUI();

				m_eState = STATE_Cycling;
			}
			else
				Start();
		}
		break;

	case STATE_Cycling:
		OffsetTime(Hy_UpdateStep());
		if(Values::Get()->m_fDAY_LENGTH - m_fTime < 10.0f)
		{
			m_MainText.pos.Y(Hy_App().Window().GetWindowSize().y - 100.0f);
			m_MainText.SetEnabled(true);
			m_MainText.alpha.Set(1.0f);
			m_MainText.scale.Set(1.0f, 1.0f);
			m_MainText.TextSet("10");

			m_eState = STATE_CountDown;
		}
		break;

	case STATE_CountDown:
		OffsetTime(Hy_UpdateStep());
		m_MainText.TextSet(std::to_string(1 + static_cast<int32>(Values::Get()->m_fDAY_LENGTH - m_fTime)));

		if(m_fTime == Values::Get()->m_fDAY_LENGTH)
		{
			m_MainText.TextSet("Finish!");
			m_MainText.pos.Set(Hy_App().Window().GetWindowSize().x * 0.5f, Hy_App().Window().GetWindowSize().y * 0.5f);
			m_MainText.scale.Set(0.001f, 0.001f);
			m_MainText.scale.Tween(1.0f, 1.0f, 0.5f, HyTween::QuadOut);

			m_fElapsedTime = 0.0f;
			m_eState = STATE_Outro;
		}
		break;

	case STATE_Outro:
		if(m_MainText.scale.IsTweening() == false && m_MainText.alpha.Get() == 1.0f)
		{
			m_fElapsedTime += Hy_UpdateStep();
			if(m_fElapsedTime > 2.0f)
				m_MainText.alpha.Tween(0.0f, 1.0f, HyTween::QuadIn);
		}
		
		if(m_MainText.alpha.Get() == 0.0f)
		{
			HarvestBoom::GetSndBank()->Stop(XACT_CUE_BASEGAME_DAY_90SEC);
			m_eState = STATE_Night;
		}
		break;

	case STATE_Night:
		break;
	}
}
