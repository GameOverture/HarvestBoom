#pragma once
#include "pch.h"
#include "Player.h"

class HarvestBoom;

class World : public HyEntity2d
{
	HarvestBoom &	m_GameRef;
	Player			m_Player;

public:
	World(HarvestBoom &gameRef);
	virtual ~World();

	virtual void OnUpdate() override;
};

