#include "pch.h"
#include "Player.h"

#define MAX_VEL 100.0f	// pixels per second
#define ACCEL 200.0f
#define STOP 500.0f

Player::Player(HyEntity2d *pParent) :	HyEntity2d(pParent),
										m_Body(this),
										m_Tool(this),
										m_Text(HY_SYSTEM_FONT, this)
{
	m_vVelocity.x = m_vVelocity.y = 0.0f;

	m_Body.GetShape().SetAsBox(20.0f, 50.0f);
	m_Body.pos.X(-10.0f);	// Center
	m_Body.topColor.Set(1.0f, 0.0f, 1.0f);

	m_Tool.GetShape().SetAsBox(5.0f, 30.0f);
	m_Tool.pos.Set(10.0f, 25.0f);
	m_Tool.rot.Set(30.0f);
	SetDisplayOrder(DISPLAYORDER_Object);

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

void Player::Equip()
{
	m_Tool.SetEnabled(true);
}

bool Player::IsEquipped()
{
	return m_Tool.IsEnabled();
}

/*virtual*/ void Player::OnUpdate() /*override*/
{
	if(Hy_App().Input().IsActionDown(MoveUp))
		m_vVelocity.y = HyClamp(m_vVelocity.y + (Hy_UpdateStep() * (m_vVelocity.y < 0.0f ? STOP : ACCEL)), m_vVelocity.y, MAX_VEL);
	else if(Hy_App().Input().IsActionDown(MoveDown))
		m_vVelocity.y = HyClamp(m_vVelocity.y - (Hy_UpdateStep() * (m_vVelocity.y > 0.0f ? STOP : ACCEL)), -MAX_VEL, m_vVelocity.y);
	else
	{
		if(m_vVelocity.y > 0.0f)
			m_vVelocity.y = HyClamp(m_vVelocity.y - (Hy_UpdateStep() * STOP), 0.0f, m_vVelocity.y);
		else if(m_vVelocity.y < 0.0f)
			m_vVelocity.y = HyClamp(m_vVelocity.y + (Hy_UpdateStep() * STOP), m_vVelocity.y, 0.0f);
	}

	if(Hy_App().Input().IsActionDown(MoveLeft))
		m_vVelocity.x = HyClamp(m_vVelocity.x - (Hy_UpdateStep() * (m_vVelocity.x > 0.0f ? STOP : ACCEL)), -MAX_VEL, m_vVelocity.x);
	else if(Hy_App().Input().IsActionDown(MoveRight))
		m_vVelocity.x = HyClamp(m_vVelocity.x + (Hy_UpdateStep() * (m_vVelocity.x < 0.0f ? STOP : ACCEL)), m_vVelocity.x, MAX_VEL);
	else
	{
		if(m_vVelocity.x > 0.0f)
			m_vVelocity.x = HyClamp(m_vVelocity.x - (Hy_UpdateStep() * STOP), 0.0f, m_vVelocity.x);
		else if(m_vVelocity.x < 0.0f)
			m_vVelocity.x = HyClamp(m_vVelocity.x + (Hy_UpdateStep() * STOP), m_vVelocity.x, 0.0f);
	}

	pos.Offset(m_vVelocity * Hy_UpdateStep());

	m_Text.TextSet(std::to_string(GetMagnitude()));
}
