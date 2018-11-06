#pragma once

#include "pch.h"
#include "World.h"

class HarvestBoom : public IHyApplication
{
	enum class GameState : uint32
	{
		Splash = 0,
		Title,
		Game
	};

	HyCamera2d *	m_pCamera;
	World			m_World;

public:
	HarvestBoom(HarmonyInit &initStruct);
	virtual ~HarvestBoom();

	virtual bool Initialize() override;
	virtual bool Update() override;
	virtual void Shutdown() override;
};
