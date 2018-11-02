#include "pch.h"
#include "World.h"
#include "HarvestBoom.h"

World::World(HarvestBoom &gameRef) :	HyEntity2d(nullptr),
										m_GameRef(gameRef),
										m_Player(this),
										m_Plant(this),
										m_Enemy(this)
{
}

World::~World()
{
}

/*virtual*/ void World::OnUpdate() /*override*/
{
	if(m_GameRef.Input().IsActionDown(MoveUp))
		m_Player.pos.Offset(0.0f, 1.0f);
	if(m_GameRef.Input().IsActionDown(MoveDown))
		m_Player.pos.Offset(0.0f, -1.0f);
	if(m_GameRef.Input().IsActionDown(MoveLeft))
		m_Player.pos.Offset(-1.0f, 0.0f);
	if(m_GameRef.Input().IsActionDown(MoveRight))
		m_Player.pos.Offset(1.0f, 0.0f);
}
