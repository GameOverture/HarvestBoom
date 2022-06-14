#pragma once
#include "pch.h"

class IActor : public HyEntity2d
{
public:
	IActor(HyEntity2d *pParent);
	virtual ~IActor();

	glm::ivec2 GetPos();
	void SetPos(glm::ivec2 ptPos);
	void SetPos(int32 iX, int32 iY);
};
