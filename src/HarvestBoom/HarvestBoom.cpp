#include "HarvestBoom.h"


HarvestBoom::HarvestBoom(HarmonyInit &initStruct) : IHyApplication(initStruct)
{
}

HarvestBoom::~HarvestBoom()
{
}

/*virtual*/ bool HarvestBoom::Initialize() /*override*/
{
	m_pCamera = Window().CreateCamera2d();

	return true;
}

/*virtual*/ bool HarvestBoom::Update() /*override*/
{
	return true;
}

/*virtual*/ void HarvestBoom::Shutdown() /*override*/
{
}
