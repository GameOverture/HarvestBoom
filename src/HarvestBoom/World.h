#pragma once
#include "pch.h"
#include "Player.h"
#include "IPlant.h"
#include "IEnemy.h"

class HarvestBoom;

class World : public HyEntity2d
{
	HarvestBoom &	m_GameRef;
	Player			m_Player;

	IPlant			m_Plant;

	IEnemy			m_Enemy;

public:
	World(HarvestBoom &gameRef);
	virtual ~World();

	virtual void OnUpdate() override;
};

