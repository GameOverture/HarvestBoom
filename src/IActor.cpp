#include "pch.h"
#include "IActor.h"

IActor::IActor(HyEntity2d *pParent) : HyEntity2d(pParent)
{
}

IActor::~IActor()
{
}

glm::ivec2 IActor::GetPos()
{
	glm::ivec2 ptPos(pos.X() / TILE_SIZE, pos.Y() / TILE_SIZE);
	if(pos.X() < 0.0f)
		ptPos.x -= 1;
	if(pos.Y() < 0.0f)
		ptPos.y -= 1;

	return ptPos;
}

void IActor::SetPos(glm::ivec2 ptPos)
{
	SetPos(ptPos.x, ptPos.y);
}

void IActor::SetPos(int32 iX, int32 iY)
{
	pos.Set(iX * TILE_SIZE, iY * TILE_SIZE);
}
