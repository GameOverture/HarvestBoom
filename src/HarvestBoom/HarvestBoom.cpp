#include "pch.h"
#include "HarvestBoom.h"

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) : IHyApplication(initStruct),
													m_World(*this),
													m_Test(HY_SYSTEM_FONT, nullptr)
{
}

HarvestBoom::~HarvestBoom()
{
}

/*virtual*/ bool HarvestBoom::Initialize() /*override*/
{
	m_pCamera = Window().CreateCamera2d();

	Input().MapBtn(ShowFPS, HYKEY_F);
	Input().MapBtn(MoveUp, HYKEY_Up);
	Input().MapBtn(MoveRight, HYKEY_Right);
	Input().MapBtn(MoveDown, HYKEY_Down);
	Input().MapBtn(MoveLeft, HYKEY_Left);
	
	m_World.Load();

	m_Test.Load();
	m_Test.TextSet("Hello asdf asdf ");

	return true;
}

/*virtual*/ bool HarvestBoom::Update() /*override*/
{
	if(Input().IsActionReleased(ShowFPS))
	{
		if(Hy_Diagnostics().GetShowFlags() == 0)
			Hy_Diagnostics().Show(HYDIAG_ALL, 16.0f, Window().GetFramebufferSize().y - 16.0f);
		else
			Hy_Diagnostics().Show(HYDIAG_NONE, 16.0f, Window().GetFramebufferSize().y - 16.0f);
	}

	return true;
}

/*virtual*/ void HarvestBoom::Shutdown() /*override*/
{
}
