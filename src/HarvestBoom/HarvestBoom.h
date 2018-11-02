#pragma once

#include "Harmony/HyEngine.h"

class HarvestBoom : public IHyApplication
{
	HyCamera2d *	m_pCamera;

public:
	HarvestBoom(HarmonyInit &initStruct);
	virtual ~HarvestBoom();

	virtual bool Initialize() override;
	virtual bool Update() override;
	virtual void Shutdown() override;
};
