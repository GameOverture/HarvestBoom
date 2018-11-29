#include "pch.h"
#include "Bug.h"
#include "Plant.h"
#include "World.h"
#include "Tile.h"
#include "HarvestBoom.h"

Bug::Bug(BugType eBugType, World &worldRef, HyEntity2d *pParent) :
	HyEntityLeaf2d<HySprite2d>("Game", "Bug", pParent),
	m_eBUG_TYPE(eBugType),
	m_WorldRef(worldRef),
	m_fDeferTimer(0.0f),
	m_bIsColliable(false),
	m_eBugAction(BUGACTION_Nothing),
	m_fStomach(0.0f),
	m_bIsGoingHome(false)
{
	m_Leaf.AnimSetState(m_eBUG_TYPE);
}

Bug::~Bug()
{
}

BugType Bug::GetBugType() const
{
	return m_eBUG_TYPE;
}

float Bug::GetHealth()
{
	return topColor.Y();
}

void Bug::OffsetHealth(float fOffset)
{
	SetHealth(GetHealth() + fOffset);
}

void Bug::SetHealth(float fHealth)
{
	fHealth = HyClamp(fHealth, 0.0f, 1.0f);
	SetTint(1.0f, fHealth, fHealth);
}

float Bug::GetStomach()
{
	return m_fStomach;
}

void Bug::OffsetStomach(float fOffset)
{
	SetStomach(GetStomach() + fOffset);
}

void Bug::SetStomach(float fStomach)
{
	m_fStomach = HyClamp(fStomach, 0.0f, 1.0f);
}

glm::ivec2 Bug::GetPos()
{
	glm::ivec2 ptPos(pos.X() / TILE_SIZE, pos.Y() / TILE_SIZE);
	if(pos.X() < 0.0f)
		ptPos.x -= 1;
	if(pos.Y() < 0.0f)
		ptPos.y -= 1;

	return ptPos;
}

void Bug::SetPos(glm::ivec2 ptPos)
{
	SetPos(ptPos.x, ptPos.y);
}

void Bug::SetPos(int32 iX, int32 iY)
{
	pos.Set(iX * TILE_SIZE, iY * TILE_SIZE);
	m_ptVirtualPos = GetPos();
	//m_DeferFuncDeque.push(BugDeferFunc([=](Bug *pThis) { pThis->pos.Set(iX * TILE_SIZE, iY * TILE_SIZE); }, 0.0f));
}

void Bug::Wait(float fDuration)
{
	m_DeferFuncDeque.push_back(BugDeferFunc([](Bug *pThis) { pThis->m_eBugAction = BUGACTION_Waiting; }, fDuration));
}

void Bug::InterruptWalkTo(float fDuration)
{
	if(m_eBugAction != BUGACTION_Walking)
		return;
	
	float fRemainingDuration = pos.GetTweenRemainingDuration();
	glm::vec2 ptTweenDest = pos.GetTweenDestination();
	pos.StopTween();

	m_DeferFuncDeque.push_front(BugDeferFunc([=](Bug *pThis) { pThis->m_eBugAction = BUGACTION_Walking; pThis->pos.Tween(ptTweenDest.x, ptTweenDest.y, fDuration, HyTween::QuadInOut); }, fRemainingDuration));
	m_DeferFuncDeque.push_front(BugDeferFunc([](Bug *pThis) { pThis->m_eBugAction = BUGACTION_Waiting; }, fDuration));
	m_fDeferTimer = 0.0f;
}

void Bug::WalkTo(int32 iX, int32 iY)
{
	float fDuration = glm::distance(m_ptVirtualPos, glm::vec2(iX, iY));
	m_DeferFuncDeque.push_back(BugDeferFunc([=](Bug *pThis) { pThis->m_eBugAction = BUGACTION_Walking; pThis->pos.Tween(iX * TILE_SIZE + (TILE_SIZE * 0.5f), iY * TILE_SIZE + (TILE_SIZE * 0.5f), fDuration, HyTween::QuadInOut); }, fDuration));

	m_ptVirtualPos = glm::vec2(iX, iY);
}

void Bug::EnableCollision()
{
	m_DeferFuncDeque.push_back(BugDeferFunc([](Bug *pThis) { pThis->m_bIsColliable = true; }, 0.0f));
}

void Bug::Eat()
{
	m_DeferFuncDeque.push_back(BugDeferFunc([](Bug *pThis) { pThis->m_eBugAction = BUGACTION_Eating; HarvestBoom::GetSndBank()->Play(pThis->GetBugType() == BUGTYPE_Beetle ? XACT_CUE_BASEGAME_SMALLBUG_CRY_SHORT : XACT_CUE_BASEGAME_BIGBUG_CRY); }, 0.0f));
}

bool Bug::IsColliable()
{
	return m_bIsColliable;
}

bool Bug::IsGoingHome()
{
	return m_bIsGoingHome;
}

void Bug::GoHome()
{
	StopEating();
	m_DeferFuncDeque.clear();
	m_fDeferTimer = 0.0f;
	pos.StopTween();
	float fDuration = glm::distance(glm::vec2(GetPos().x, GetPos().y), glm::vec2(m_WorldRef.GetTileWaypoint(0).x, m_WorldRef.GetTileWaypoint(0).y));
	pos.Tween(m_WorldRef.GetPixelWaypoint(0).x, m_WorldRef.GetPixelWaypoint(0).y, fDuration, HyTween::Linear);

	m_bIsGoingHome = true;
}

void Bug::BugUpdate()
{
	m_fDeferTimer = HyMax(m_fDeferTimer - Hy_UpdateStep(), 0.0f);
	if(m_eBugAction != BUGACTION_Eating && m_fDeferTimer == 0.0f && m_DeferFuncDeque.empty() == false)
	{
		m_fDeferTimer = m_DeferFuncDeque.front().second;
		m_DeferFuncDeque.front().first(this);

		m_DeferFuncDeque.pop_front();
	}

	if(m_eBugAction == BUGACTION_Eating)
	{
		m_Leaf.AnimSetPlayRate(5.0f);
		m_Leaf.AnimSetPause(false);

		if(m_Leaf.rot.IsTweening() == false)
			m_Leaf.rot.Tween(-20.0f, 1.25f, HyTween::QuadOut, [this](IHyNode *) { m_Leaf.rot.Tween(3.0f, 0.25f, HyTween::QuadIn); TakeBite(); });
	}
	else
	{
		m_Leaf.AnimSetPlayRate(1.0f);

		if(pos.IsTweening())
		{
			m_Leaf.AnimSetPause(false);
			if(m_Leaf.rot.IsTweening() == false)
				m_Leaf.rot.Tween(-3.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { m_Leaf.rot.Tween(3.0f, 0.25f, HyTween::QuadIn); });
		}
		else
		{
			if(m_Leaf.rot.Get() != 0.0f && m_Leaf.rot.IsTweening() == false)
				m_Leaf.rot.Tween(0.0f, 0.75f, HyTween::QuadInOut);

			m_Leaf.AnimSetPause(true);
		}
	}

	if(m_ptPrevPos != pos.Get() && rot.IsTweening() == false)
	{
		glm::vec2 vOrientation = m_ptPrevPos - pos.Get();
		vOrientation = glm::normalize(vOrientation);
		float fNewOrientation = glm::degrees(atan2(vOrientation.y, vOrientation.x)) + 90.0f;

		if(abs(fNewOrientation - rot.Get()) < 10.0f)
			rot.Set(fNewOrientation);
		else
			rot.Tween(fNewOrientation, 0.4f, HyTween::QuadInOut);
	}

	m_ptPrevPos = pos.Get();
}

bool Bug::IsWaiting()
{
	return m_eBugAction == BUGACTION_Waiting;
}

bool Bug::IsEating()
{
	return m_eBugAction == BUGACTION_Eating;
}

void Bug::StopEating()
{
	m_eBugAction = BUGACTION_Nothing;
}

void Bug::TakeBite()
{
	Tile *pTile = m_WorldRef.FindTile(pos.Get());
	if(pTile == nullptr || pTile->GetPlant() == nullptr)
		return;

	pTile->DamagePlant(*this);
}
