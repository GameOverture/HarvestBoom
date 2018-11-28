#pragma once
#include "pch.h"

class Plant;

class Bug : public HyEntityLeaf2d<HySprite2d>
{
	typedef std::pair<std::function<void(Bug *pSelf)>, float> BugDeferFunc;

	std::queue<BugDeferFunc>	m_DeferFuncQueue;
	float						m_fDeferTimer;

	bool						m_bEating;

public:
	Bug(BugType eBugType, HyEntity2d *pParent);
	virtual ~Bug();

	bool IsIdle();

	glm::ivec2 GetPos();
	void SetPos(glm::ivec2 ptPos);
	void SetPos(int32 iX, int32 iY);
	void Wait(float fDuration);
	void WalkTo(int32 iX, int32 iY);
	void Eat();

protected:
	virtual void OnUpdate() override;
};
