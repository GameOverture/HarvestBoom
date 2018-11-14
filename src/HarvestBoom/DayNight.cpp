#include "pch.h"
#include "DayNight.h"
#include "HarvestBoom.h"

#define DAYNIGHT_SIDEMARGIN 50.0f
#define DAYNIGHT_TOPMARGIN 50.0f

#define DAYNIGHT_DARKNESSAMT 0.7f

DayNight::DayNight(HyEntity2d *pParent) :	HyEntity2d(pParent),
											m_fTime(0.0f),
											m_Emblem("UI", "DayNight", this),
											m_Bar("UI", "DayNightBar", this),
											m_DayNight(this),
											m_MainText("Game", "Main", this),
											m_eState(STATE_Off)
{
	UseWindowCoordinates();
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

void DayNight::Start()
{
#ifdef DEV_QUICKMODE
	m_eState = STATE_Cycling;
#else
	m_MainText.SetEnabled(true);
	m_MainText.pos.Set(vWindowSize.x * 0.5f, vWindowSize.y * 0.5f);
	m_MainText.alpha.Set(0.0f);
	m_MainText.alpha.Tween(1.0f, 0.25f);
	m_MainText.scale.Set(0.001f, 0.001f);
	m_MainText.scale.Tween(0.8f, 0.8f, 0.5f, HyTween::CubeOut);

	switch(m_MainText.GetTag())
	{
	case 0:	m_MainText.TextSet("Good Morning!");
		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_ROOSTER_CROWING);
		break;
	case 1:	m_MainText.TextSet("Get Set...");	break;
	case 2:	m_MainText.TextSet("GO!");	break;
	}

	m_eState = STATE_Intro;
#endif
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
	m_Emblem.pos.Set(DAYNIGHT_SIDEMARGIN + (fNormalized * (vWindowSize.x - (DAYNIGHT_SIDEMARGIN * 2.0f))), vWindowSize.y - DAYNIGHT_TOPMARGIN);
	m_Emblem.rot.Set(fNormalized * 180.0f);

	m_DayNight.alpha.Set(fNormalized * DAYNIGHT_DARKNESSAMT);
}

/*virtual*/ void DayNight::OnLoaded() /*override*/
{
	glm::ivec2 vWindowSize = Hy_App().Window().GetWindowSize();

	m_DayNight.GetShape().SetAsBox(vWindowSize.x, vWindowSize.y);
	m_DayNight.topColor.Set(0.0f, 0.0f, 0.0f);
	m_DayNight.SetDisplayOrder(DISPLAYORDER_DayNight);
	m_DayNight.alpha.Set(0.0f);
	

	m_Bar.pos.Set(DAYNIGHT_SIDEMARGIN, vWindowSize.y - DAYNIGHT_TOPMARGIN);
	m_Bar.scale.Set(2.155f, 2.0f);

	m_Emblem.pos.Set(DAYNIGHT_SIDEMARGIN, vWindowSize.y - DAYNIGHT_TOPMARGIN);
	m_Emblem.scale.Set(2.0f, 2.0f);

	m_MainText.pos.Set(vWindowSize.x * 0.5f, vWindowSize.y * 0.5f);
	m_MainText.TextSetAlignment(HYALIGN_Center);

	SetScissor(0, vWindowSize.y - static_cast<int32>(DAYNIGHT_TOPMARGIN) - 4, vWindowSize.x, static_cast<uint32>(DAYNIGHT_TOPMARGIN));
	m_DayNight.ClearScissor(false);
	m_MainText.ClearScissor(false);

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
			if(m_MainText.GetTag() == 3)
			{
				HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_FARM_DAYTIME_16BIT);
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
			m_eState = STATE_Night;
		}

		break;

	case STATE_Night:
		break;
	}
}
