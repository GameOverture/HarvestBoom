#include "pch.h"
#include "Player.h"
#include "Tile.h"
#include "Plant.h"
#include "HarvestBoom.h"

#define PLAYER_WIDTH 10.0f
#define PLAYER_HEIGHT 5.0f

extern HyInput &Hy_Input();
extern float Hy_UpdateStep();

Player::Player(HyEntity2d *pParent) :
	IActor(pParent),
	m_Body("Game", "Player", this),
	m_Tool(this),
	m_DebugText(HY_SYSTEM_FONT, this),
	m_Collision(this),
	m_Origin(this),
	m_ePrevEquipedItem(EQUIP_Nothing),
	m_pEquipment(nullptr),
	m_fEquipIdleHeight(0.0f)
{
	m_vVelocity.x = m_vVelocity.y = 0.0f;

	m_Body.pos.X(-TILE_SIZE * 0.5f);	// Center

	m_Tool.SetAsBox(5.0f, 30.0f);
	m_Tool.pos.Set(10.0f, 25.0f);
	m_Tool.rot.Set(30.0f);

	m_Collision.SetAsBox(PLAYER_WIDTH, PLAYER_HEIGHT);
	m_Collision.pos.Offset(-PLAYER_WIDTH * 0.5f, -PLAYER_HEIGHT * 0.5f);
	m_Collision.SetWireframe(true);
	m_Collision.topColor.Set(0.0f, 0.0f, 1.0f);
	m_Collision.SetVisible(false);

	m_Origin.SetAsCircle(2);
	m_Origin.SetVisible(false);

	m_Tool.SetVisible(false);
	m_DebugText.SetVisible(false);

	SetPos(PLAYER_STARTPOS);
	Sync();
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

const HyShape2d &Player::GetCollision()
{
	return m_Collision.GetLocalBoundingVolume();
}

const glm::mat4 &Player::GetCollisionTransform()
{
	return m_Collision.GetWorldTransform();
}

void Player::Equip()
{
	m_Tool.SetVisible(true);
}

bool Player::IsEquipped()
{
	return m_Tool.IsVisible();
}

void Player::HandleInput(Tile *pPlayerTile)
{
	if(Hy_Input().IsActionDown(MoveUp))
		m_vVelocity.y = HyClamp(m_vVelocity.y + (Hy_UpdateStep() * (m_vVelocity.y < 0.0f ? Values::Get()->m_fPLAYER_DECEL : Values::Get()->m_fPLAYER_ACCEL)), m_vVelocity.y, Values::Get()->m_fPLAYER_MAXVELOCITY);
	else if(Hy_Input().IsActionDown(MoveDown))
		m_vVelocity.y = HyClamp(m_vVelocity.y - (Hy_UpdateStep() * (m_vVelocity.y > 0.0f ? Values::Get()->m_fPLAYER_DECEL : Values::Get()->m_fPLAYER_ACCEL)), -Values::Get()->m_fPLAYER_MAXVELOCITY, m_vVelocity.y);
	else
	{
		if(m_vVelocity.y > 0.0f)
			m_vVelocity.y = HyClamp(m_vVelocity.y - (Hy_UpdateStep() * Values::Get()->m_fPLAYER_DECEL), 0.0f, m_vVelocity.y);
		else if(m_vVelocity.y < 0.0f)
			m_vVelocity.y = HyClamp(m_vVelocity.y + (Hy_UpdateStep() * Values::Get()->m_fPLAYER_DECEL), m_vVelocity.y, 0.0f);
	}

	if(Hy_Input().IsActionDown(MoveLeft))
		m_vVelocity.x = HyClamp(m_vVelocity.x - (Hy_UpdateStep() * (m_vVelocity.x > 0.0f ? Values::Get()->m_fPLAYER_DECEL : Values::Get()->m_fPLAYER_ACCEL)), -Values::Get()->m_fPLAYER_MAXVELOCITY, m_vVelocity.x);
	else if(Hy_Input().IsActionDown(MoveRight))
		m_vVelocity.x = HyClamp(m_vVelocity.x + (Hy_UpdateStep() * (m_vVelocity.x < 0.0f ? Values::Get()->m_fPLAYER_DECEL : Values::Get()->m_fPLAYER_ACCEL)), m_vVelocity.x, Values::Get()->m_fPLAYER_MAXVELOCITY);
	else
	{
		if(m_vVelocity.x > 0.0f)
			m_vVelocity.x = HyClamp(m_vVelocity.x - (Hy_UpdateStep() * Values::Get()->m_fPLAYER_DECEL), 0.0f, m_vVelocity.x);
		else if(m_vVelocity.x < 0.0f)
			m_vVelocity.x = HyClamp(m_vVelocity.x + (Hy_UpdateStep() * Values::Get()->m_fPLAYER_DECEL), m_vVelocity.x, 0.0f);
	}


	// Shuffle crops around as passing through (and modify player velocity)
	float fMaxClamp = 1.0f;
	if(pPlayerTile && pPlayerTile->GetTileType() == Dirt && pPlayerTile->GetPlant())
	{
		float fRunNormalized = GetMagnitude() / Values::Get()->m_fPLAYER_MAXVELOCITY;
		fMaxClamp = 0.25f;

		if(pPlayerTile->GetPlant()->rot.IsAnimating() == false && fRunNormalized != 0.0f)
		{
			if(m_vVelocity.x > 0)
				pPlayerTile->GetPlant()->rot.Tween(-15.0f, 0.25f, HyTween::QuadOut, [](IHyNode *pPlant) { static_cast<IHyNode2d *>(pPlant)->rot.Tween(15.0f, 0.25f, HyTween::QuadIn); });
			else if(m_vVelocity.x < 0)
				pPlayerTile->GetPlant()->rot.Tween(15.0f, 0.25f, HyTween::QuadOut, [](IHyNode *pPlant) { static_cast<IHyNode2d *>(pPlant)->rot.Tween(-15.0f, 0.25f, HyTween::QuadIn); });
			else // Zero X velocity, so sway crop based on player position to plant
			{
				if(pos.X() < pPlayerTile->pos.X() + (TILE_SIZE * 0.5f))
					pPlayerTile->GetPlant()->rot.Tween(-15.0f, 0.25f, HyTween::QuadOut, [](IHyNode *pPlant) { static_cast<IHyNode2d *>(pPlant)->rot.Tween(15.0f, 0.25f, HyTween::QuadIn); });
				else
					pPlayerTile->GetPlant()->rot.Tween(15.0f, 0.25f, HyTween::QuadOut, [](IHyNode *pPlant) { static_cast<IHyNode2d *>(pPlant)->rot.Tween(-15.0f, 0.25f, HyTween::QuadIn); });
			}
		}
	}

	if(Values::Get()->m_fStamina == 0.0f)
		fMaxClamp = 0.25f;

	m_vVelocity.x = HyClamp(m_vVelocity.x, -fMaxClamp * Values::Get()->m_fPLAYER_MAXVELOCITY, fMaxClamp * Values::Get()->m_fPLAYER_MAXVELOCITY);
	m_vVelocity.y = HyClamp(m_vVelocity.y, -fMaxClamp * Values::Get()->m_fPLAYER_MAXVELOCITY, fMaxClamp * Values::Get()->m_fPLAYER_MAXVELOCITY);

	pos.Offset(m_vVelocity * Hy_UpdateStep());
	float fMagnitude = GetMagnitude();
	if(abs(fMagnitude) > 0.0f)
	{
		m_Body.AnimSetState(1);
		m_Body.AnimSetPlayRate(fMagnitude / Values::Get()->m_fPLAYER_MAXVELOCITY);
	}
	else
		m_Body.AnimSetState(0);

	//m_DebugText.TextSet(std::to_string(fMagnitude));
	//m_DebugText.TextSet(std::to_string(Hy_Window().GetCamera2d(0)->pos.Y()));
}

bool Player::DoAction(Tile &tileRef)
{
	// Checks whether action is valid
	if(Values::Get()->m_fStamina > 0.0f && tileRef.IncrementProgress())
	{
		ZeroVelocity();

		switch(Values::Get()->m_eEquipedItem)
		{
		case EQUIP_Hoe:
			if(m_pEquipment && m_pEquipment->rot.IsAnimating() == false)
				m_pEquipment->rot.Tween(-80.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_USEHOE_1); m_pEquipment->rot.Tween(-50.0f, 0.25f, HyTween::QuadIn); });

			if(m_pEquipment && m_pEquipment->pos.Y() == m_fEquipIdleHeight)
				m_pEquipment->pos.Tween(m_pEquipment->pos.X(), 14.0f, 0.25f, HyTween::QuadOut);

			if(rot.IsAnimating() == false)
				rot.Tween(-3.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { rot.Tween(3.0f, 0.25f, HyTween::QuadIn); });
			break;

		case EQUIP_Harvest:
			if(m_pEquipment && m_pEquipment->rot.IsAnimating() == false)
				m_pEquipment->rot.Tween(80.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_USEHOE_3); m_pEquipment->rot.Tween(-50.0f, 0.25f, HyTween::QuadIn); });
			if(rot.IsAnimating() == false)
				rot.Tween(-10.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { rot.Tween(10.0f, 0.25f, HyTween::QuadIn); });
			break;

		case EQUIP_Corn:
		case EQUIP_Eggplant:
		case EQUIP_Pumpkin:
		case EQUIP_Gernaium:
		case EQUIP_Marigold:
		case EQUIP_Vine:
			scale.Set(1.0f, 0.75f);
			if(rot.IsAnimating() == false)
				rot.Tween(-20.0f, 0.25f, HyTween::QuadOut, [this](IHyNode *) { HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_USEHOE_1); rot.Tween(20.0f, 0.25f, HyTween::QuadIn); });
			break;
		}

		return true;
	}
	else
		StopAction();

	return false;
}

void Player::StopAction()
{
	if(m_pEquipment)
	{
		if(m_pEquipment->rot.Get() != 0.0f && m_pEquipment->rot.IsAnimating() == false)
			m_pEquipment->rot.Tween(0.0f, 0.25f, HyTween::QuadOut);

		if(m_pEquipment->pos.Y() != m_fEquipIdleHeight && m_pEquipment->pos.IsAnimating() == false)
			m_pEquipment->pos.Tween(m_pEquipment->pos.X(), m_fEquipIdleHeight, 0.25f, HyTween::QuadOut);
	}

	scale.Set(1.0f, 1.0f);
	rot.Tween(0.0f, 0.25f, HyTween::QuadOut);
}

void Player::Sync()
{
	if(m_ePrevEquipedItem == Values::Get()->m_eEquipedItem)
		return;

	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		delete m_pEquipment;
		m_pEquipment = HY_NEW HySprite2d("Equip", "Hoe", this);
		m_fEquipIdleHeight = 20.0f;
		m_pEquipment->pos.Set(4.0f, m_fEquipIdleHeight);
		m_pEquipment->Load();
		break;
	case EQUIP_Harvest:
		delete m_pEquipment;
		m_pEquipment = HY_NEW HySprite2d("Equip", "Sythe", this);
		m_fEquipIdleHeight = 16.0f;
		m_pEquipment->pos.Set(-5.0f, m_fEquipIdleHeight);
		m_pEquipment->Load();
		break;
	case EQUIP_Corn:
	case EQUIP_Eggplant:
	case EQUIP_Pumpkin:
	case EQUIP_Gernaium:
	case EQUIP_Marigold:
	case EQUIP_Vine:
		delete m_pEquipment;
		m_pEquipment = HY_NEW HySprite2d("Equip", "Seeds", this);
		m_fEquipIdleHeight = 20.0f;
		m_pEquipment->pos.Set(9.0f, m_fEquipIdleHeight);
		m_pEquipment->Load();
		break;
	}

	m_ePrevEquipedItem = Values::Get()->m_eEquipedItem;
}
