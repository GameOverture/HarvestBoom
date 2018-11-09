#pragma once
#include "IActor.h"

class Player : public IActor
{
	HyPrimitive2d		m_Body;
	HyPrimitive2d		m_Tool;
	HyText2d			m_Text;

	glm::vec2			m_vVelocity;

	HyPrimitive2d		m_Collision;

public:
	Player(HyEntity2d *pParent);
	virtual ~Player();

	float GetMagnitude();
	HyShape2d &GetCollision();

	void Equip();
	bool IsEquipped();

	void HandleInput();
};
