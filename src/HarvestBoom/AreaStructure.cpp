#include "pch.h"
#include "AreaStructure.h"
#include "Player.h"

AreaStructure::AreaStructure(HyEntity2d *pParent) :	IArea(Structure, pParent),
													m_CollidePt1(nullptr),
													m_CollidePt2(nullptr)
{
	m_CollidePt1.GetShape().SetAsCircle(5.0f);
	m_CollidePt1.SetDisplayOrder(5000);
	m_CollidePt1.Load();

	m_CollidePt2.GetShape().SetAsCircle(5.0f);
	m_CollidePt2.SetDisplayOrder(5000);
	m_CollidePt2.Load();
}

AreaStructure::~AreaStructure()
{
}

bool AreaStructure::CollisionTest(Player &playerRef)
{
	b2WorldManifold manifold;
	bool bCollided = m_Ground.GetShape().IsColliding(playerRef.GetCollision(), manifold);

	if(bCollided == false)// m_Ground.GetShape().TestPoint(playerRef.pos.Get()) == false)
		return false;

	m_CollidePt1.pos.Set(manifold.points[0].x, manifold.points[0].y);
	m_CollidePt2.pos.Set(manifold.points[1].x, manifold.points[1].y);

	/*if(abs(playerRef.pos.X() - pos.X()) < abs(playerRef.pos.Y() - pos.Y()))
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
	}*/

	return true;
}
