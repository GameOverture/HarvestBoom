#include "pch.h"
#include "Player.h"

Player::Player(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_Body(this)
{
	m_Body.GetShape().SetAsBox(25.0f, 25.0f);
	m_Body.topColor.Set(1.0f, 0.0f, 0.0f);
}

Player::~Player()
{
}
