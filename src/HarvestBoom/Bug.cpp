#include "pch.h"
#include "Bug.h"
#include "Plant.h"
#include "World.h"

Bug::Bug(BugType eBugType, HyEntity2d *pParent) :
	HyEntityLeaf2d<HySprite2d>("Game", "Bug", pParent),
	m_eBUG_TYPE(eBugType),
	m_fDeferTimer(0.0f),
	m_bEating(false)
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

bool Bug::IsIdle()
{
	return m_DeferFuncQueue.empty() && m_bEating == false;
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
	//m_DeferFuncQueue.push(BugDeferFunc([=](Bug *pThis) { pThis->pos.Set(iX * TILE_SIZE, iY * TILE_SIZE); }, 0.0f));
}

void Bug::Wait(float fDuration)
{
	m_DeferFuncQueue.push(BugDeferFunc([](Bug *pThis) {}, fDuration));
}

void Bug::WalkTo(int32 iX, int32 iY)
{
	glm::vec2 ptPos(static_cast<float>(GetPos().x), static_cast<float>(GetPos().y));
	float fDuration = glm::distance(ptPos, glm::vec2(iX, iY));

	m_DeferFuncQueue.push(BugDeferFunc([=](Bug *pThis) { pThis->pos.Tween(iX * TILE_SIZE + (TILE_SIZE * 0.5f), iY * TILE_SIZE + (TILE_SIZE * 0.5f), fDuration, HyTween::QuadInOut); }, fDuration));
}

void Bug::Eat()
{
	m_DeferFuncQueue.push(BugDeferFunc([](Bug *pThis) { pThis->m_bEating = true; }, 0.0f));
}

void Bug::BugUpdate(World &worldRef)
{
	m_fDeferTimer = HyMax(m_fDeferTimer - Hy_UpdateStep(), 0.0f);
	if(m_bEating == false && m_fDeferTimer == 0.0f && m_DeferFuncQueue.empty() == false)
	{
		m_fDeferTimer = m_DeferFuncQueue.front().second;
		m_DeferFuncQueue.front().first(this);

		m_DeferFuncQueue.pop();
	}

	if(m_bEating)
	{
		m_Leaf.AnimSetPlayRate(3.0f);
		m_Leaf.AnimSetPause(false);
		if(m_Leaf.rot.IsTweening() == false)
			m_Leaf.rot.Tween(-3.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { m_Leaf.rot.Tween(3.0f, 0.25f, HyTween::QuadIn); });

		if(rot.IsTweening() == false)
			rot.Tween(-20.0f, 1.25f, HyTween::QuadOut, [this](IHyNode *) { rot.Tween(3.0f, 0.25f, HyTween::QuadIn); });
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
}

void Bug::StopEating()
{
	m_bEating = false;
}
