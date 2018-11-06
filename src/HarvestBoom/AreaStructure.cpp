#include "pch.h"
#include "AreaStructure.h"
#include "Player.h"

AreaStructure::AreaStructure(HyEntity2d *pParent) :	IArea(Structure, pParent)
{
}

AreaStructure::~AreaStructure()
{
}

bool AreaStructure::CollisionTest(Player &playerRef)
{
	if(m_Ground.GetShape().TestPoint(playerRef.pos.Get()) == false)
		return false;

	if(abs(playerRef.pos.X() - pos.X()) < abs(playerRef.pos.Y() - pos.Y()))
	{
		if(playerRef.pos.X() <= pos.X() + (m_vSize.x * 0.5f))
			playerRef.pos.X(pos.X());
		else
			playerRef.pos.X(pos.X() + m_vSize.x);
	}
	else
	{
		if(playerRef.pos.Y() <= pos.Y() + (m_vSize.y * 0.5f))
			playerRef.pos.Y(pos.Y());
		else
			playerRef.pos.Y(pos.Y() + m_vSize.y);
	}

	return true;
}
