#pragma once
#include "pch.h"

class Plant;
class World;

class Bug : public HyEntityLeaf2d<HySprite2d>
{
	const BugType				m_eBUG_TYPE;
	World &						m_WorldRef;

	typedef std::pair<std::function<void(Bug *pSelf)>, float> BugDeferFunc;
	std::deque<BugDeferFunc>	m_DeferFuncDeque;
	float						m_fDeferTimer;

	glm::vec2					m_ptVirtualPos;
	glm::vec2					m_ptPrevPos;
	bool						m_bIsColliable;

	enum BugAction
	{
		BUGACTION_Nothing = 0,
		BUGACTION_Waiting,
		BUGACTION_Walking,
		BUGACTION_Eating
	};
	BugAction					m_eBugAction;

	float						m_fStomach;
	bool						m_bIsGoingHome;
	
public:
	Bug(BugType eBugType, World &worldRef, HyEntity2d *pParent);
	virtual ~Bug();

	BugType GetBugType() const;

	float GetHealth();
	void OffsetHealth(float fOffset);
	void SetHealth(float fHealth);

	float GetStomach();
	void OffsetStomach(float fOffset);
	void SetStomach(float fStomach);

	glm::ivec2 GetPos();
	void SetPos(glm::ivec2 ptPos);
	void SetPos(int32 iX, int32 iY);
	void Wait(float fDuration);
	void InterruptWalkTo(float fDuration);
	void WalkTo(int32 iX, int32 iY);
	void EnableCollision();
	void Eat();

	bool IsColliable();
	bool IsGoingHome();

	void GoHome();

	void BugUpdate();

	bool IsWaiting();
	bool IsEating();
	void StopEating();

	void TakeBite();
};
