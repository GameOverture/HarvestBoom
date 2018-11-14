#include "pch.h"
#include "Player.h"
#include "Tile.h"

#define PLAYER_MAXVELOCITY 200.0f	// pixels per second
#define PLAYER_ACCEL 300.0f
#define PLAYER_DECEL 600.0f

#define PLAYER_WIDTH 10.0f
#define PLAYER_HEIGHT 5.0f

Player::Player(HyEntity2d *pParent) :	IActor(pParent),
										m_Body("Game", "Player", this),
										m_Tool(this),
										m_DebugText(HY_SYSTEM_FONT, this),
										m_Collision(this),
										m_Origin(this),
										m_pEquipment(nullptr)
{
	m_vVelocity.x = m_vVelocity.y = 0.0f;

	m_Body.pos.X(-TILE_SIZE * 0.5f);	// Center

	m_Tool.GetShape().SetAsBox(5.0f, 30.0f);
	m_Tool.pos.Set(10.0f, 25.0f);
	m_Tool.rot.Set(30.0f);

	m_Collision.GetShape().SetAsBox(PLAYER_WIDTH, PLAYER_HEIGHT);
	m_Collision.pos.Offset(-PLAYER_WIDTH * 0.5f, -PLAYER_HEIGHT * 0.5f);
	m_Collision.SetWireframe(true);
	m_Collision.topColor.Set(0.0f, 0.0f, 1.0f);
	m_Collision.SetEnabled(false);

	m_Origin.GetShape().SetAsCircle(2);
	m_Origin.SetEnabled(false);

	m_Tool.SetEnabled(false);
	m_DebugText.SetEnabled(false);
}

Player::~Player()
{
}

float Player::GetMagnitude()
{
	return glm::length(m_vVelocity);
}

void Player::ZeroVelocity()
{
	m_vVelocity.x = m_vVelocity.y = 0.0f;
}

void Player::ZeroVelocityX()
{
	m_vVelocity.x = 0.0f;
}

void Player::ZeroVelocityY()
{
	m_vVelocity.y = 0.0f;
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
	float fMagnitude = GetMagnitude();
	if(abs(fMagnitude) > 0.0f)
	{
		m_Body.AnimSetState(1);
		m_Body.AnimSetPlayRate(fMagnitude / PLAYER_MAXVELOCITY);
	}
	else
		m_Body.AnimSetState(0);

	m_DebugText.TextSet(std::to_string(fMagnitude));
}

void Player::DoAction(Tile &tileRef)
{
	// Checks whether action is valid
	if(tileRef.IncrementProgress())
	{
		ZeroVelocity();

		switch(Values::Get()->m_eEquipedItem)
		{
		case EQUIP_Hoe:
			if(m_pEquipment && m_pEquipment->rot.IsTweening() == false)
				m_pEquipment->rot.Tween(-80.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { m_pEquipment->rot.Tween(-50.0f, 0.25f, HyTween::QuadIn); });
			break;

		case EQUIP_Harvest:
			if(rot.IsTweening() == false)
				rot.Tween(-10.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { rot.Tween(10.0f, 0.25f, HyTween::QuadIn); });
			break;

		case EQUIP_Corn:
		case EQUIP_Eggplant:
		case EQUIP_Pumpkin:
		case EQUIP_Gernaium:
		case EQUIP_Marigold:
		case EQUIP_Vine:
			scale.Set(1.0f, 0.75f);
			if(rot.IsTweening() == false)
				rot.Tween(-20.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { rot.Tween(20.0f, 0.25f, HyTween::QuadIn); });
			break;
		}
	}
	else
		StopAction();
}

void Player::StopAction()
{
	if(m_pEquipment && Values::Get()->m_eEquipedItem == EQUIP_Hoe)
		m_pEquipment->rot.Tween(0.0f, 0.5f, HyTween::QuadOut);

	scale.Set(1.0f, 1.0f);
	rot.Tween(0.0f, 0.25f, HyTween::QuadOut);
}

void Player::Sync()
{
	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		delete m_pEquipment;
		m_pEquipment = HY_NEW HySprite2d("Equip", "Hoe", this);
		m_pEquipment->pos.Set(4.0f, 16.0f);
		m_pEquipment->Load();
		break;
	case EQUIP_Harvest:
		delete m_pEquipment;
		m_pEquipment = nullptr;
		break;
	case EQUIP_Corn:
	case EQUIP_Eggplant:
	case EQUIP_Pumpkin:
	case EQUIP_Gernaium:
	case EQUIP_Marigold:
	case EQUIP_Vine:
		delete m_pEquipment;
		m_pEquipment = nullptr;
		break;
	}
}
