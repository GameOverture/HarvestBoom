#pragma once
#include "pch.h"

class Player : public HyEntity2d
{
	HyPrimitive2d		m_Body;
	HyPrimitive2d		m_Tool;
	HyText2d			m_Text;

	glm::vec2			m_vVelocity;

public:
	Player(HyEntity2d *pParent);
	virtual ~Player();

	float GetMagnitude();

	void Equip();
	bool IsEquipped();

	virtual void OnUpdate() override;
};
