#include "pch.h"
#include "Player.h"

#define PLAYER_MAXVELOCITY 200.0f	// pixels per second
#define PLAYER_ACCEL 300.0f
#define PLAYER_DECEL 600.0f

#define PLAYER_WIDTH 25.0f
#define PLAYER_HEIGHT (TILE_SIZE * 2)

Player::Player(HyEntity2d *pParent) :	IActor(pParent),
										m_Body(this),
										m_Tool(this),
										m_Text("Game", "Main", this),
										m_Collision(this)
{
	m_vVelocity.x = m_vVelocity.y = 0.0f;

	m_Body.GetShape().SetAsBox(PLAYER_WIDTH, PLAYER_HEIGHT);
	m_Body.pos.X(-PLAYER_WIDTH * 0.5f);	// Center
	m_Body.topColor.Set(1.0f, 0.0f, 1.0f);

	m_Tool.GetShape().SetAsBox(5.0f, 30.0f);
	m_Tool.pos.Set(10.0f, 25.0f);
	m_Tool.rot.Set(30.0f);
	SetDisplayOrder(DISPLAYORDER_Object);

	m_Collision.GetShape().SetAsBox(PLAYER_WIDTH, 10.0f);
	m_Collision.pos.X(-PLAYER_WIDTH * 0.5f);	// Center

	m_Tool.SetEnabled(false);
	m_Text.SetEnabled(false);
}

Player::~Player()
{
}

float Player::GetMagnitude()
{
	return glm::length(m_vVelocity);
}

HyShape2d &Player::GetCollision()
{
	return m_Collision.GetShape();
}

void Player::Equip()
{
	m_Tool.SetEnabled(true);
}

bool Player::IsEquipped()
{
	return m_Tool.IsEnabled();
}

void Player::HandleInput()
{
	if(Hy_App().Input().IsActionDown(MoveUp))
		m_vVelocity.y = HyClamp(m_vVelocity.y + (Hy_UpdateStep() * (m_vVelocity.y < 0.0f ? PLAYER_DECEL : PLAYER_ACCEL)), m_vVelocity.y, PLAYER_MAXVELOCITY);
	else if(Hy_App().Input().IsActionDown(MoveDown))
		m_vVelocity.y = HyClamp(m_vVelocity.y - (Hy_UpdateStep() * (m_vVelocity.y > 0.0f ? PLAYER_DECEL : PLAYER_ACCEL)), -PLAYER_MAXVELOCITY, m_vVelocity.y);
	else
	{
		if(m_vVelocity.y > 0.0f)
			m_vVelocity.y = HyClamp(m_vVelocity.y - (Hy_UpdateStep() * PLAYER_DECEL), 0.0f, m_vVelocity.y);
		else if(m_vVelocity.y < 0.0f)
			m_vVelocity.y = HyClamp(m_vVelocity.y + (Hy_UpdateStep() * PLAYER_DECEL), m_vVelocity.y, 0.0f);
	}

	if(Hy_App().Input().IsActionDown(MoveLeft))
		m_vVelocity.x = HyClamp(m_vVelocity.x - (Hy_UpdateStep() * (m_vVelocity.x > 0.0f ? PLAYER_DECEL : PLAYER_ACCEL)), -PLAYER_MAXVELOCITY, m_vVelocity.x);
	else if(Hy_App().Input().IsActionDown(MoveRight))
		m_vVelocity.x = HyClamp(m_vVelocity.x + (Hy_UpdateStep() * (m_vVelocity.x < 0.0f ? PLAYER_DECEL : PLAYER_ACCEL)), m_vVelocity.x, PLAYER_MAXVELOCITY);
	else
	{
		if(m_vVelocity.x > 0.0f)
			m_vVelocity.x = HyClamp(m_vVelocity.x - (Hy_UpdateStep() * PLAYER_DECEL), 0.0f, m_vVelocity.x);
		else if(m_vVelocity.x < 0.0f)
			m_vVelocity.x = HyClamp(m_vVelocity.x + (Hy_UpdateStep() * PLAYER_DECEL), m_vVelocity.x, 0.0f);
	}

	pos.Offset(m_vVelocity * Hy_UpdateStep());

	m_Text.TextSet(std::to_string(GetMagnitude()));
}
