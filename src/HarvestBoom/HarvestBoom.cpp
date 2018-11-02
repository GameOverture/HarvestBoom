#include "pch.h"
#include "HarvestBoom.h"

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) : IHyApplication(initStruct),
													m_World(*this)
{
}

HarvestBoom::~HarvestBoom()
{
}

/*virtual*/ bool HarvestBoom::Initialize() /*override*/
{
	m_pCamera = Window().CreateCamera2d();

	Input().MapBtn(MoveUp, HYKEY_Up);
	Input().MapBtn(MoveRight, HYKEY_Right);
	Input().MapBtn(MoveDown, HYKEY_Down);
	Input().MapBtn(MoveLeft, HYKEY_Left);
	
	m_World.Load();

	return true;
}

/*virtual*/ bool HarvestBoom::Update() /*override*/
{
	return true;
}

/*virtual*/ void HarvestBoom::Shutdown() /*override*/
{
}
