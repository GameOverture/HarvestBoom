#pragma once
#include "IActor.h"

class Tile;

class Player : public IActor
{
	HySprite2d			m_Body;
	HyPrimitive2d		m_Tool;
	HyText2d			m_DebugText;

	glm::vec2			m_vVelocity;

	HyPrimitive2d		m_Collision;
	HyPrimitive2d		m_Origin;

	HySprite2d *		m_pEquipment;

public:
	Player(HyEntity2d *pParent);
	virtual ~Player();

	float GetMagnitude();
	void ZeroVelocity();
	void ZeroVelocityX();
	void ZeroVelocityY();

	HyShape2d &GetCollision();

	void Equip();
	bool IsEquipped();

	void HandleInput();

	void DoAction(Tile &tileRef);
	void StopAction();

	void Sync();
};
