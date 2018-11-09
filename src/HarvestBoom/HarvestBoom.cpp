#include "pch.h"
#include "HarvestBoom.h"
#include "Audio/LtGAudioLinks.h"

LtGAudioSndBank *HarvestBoom::sm_pSoundBank = nullptr;

HarvestBoom::HarvestBoom(HarmonyInit &initStruct) : IHyApplication(initStruct),
													m_World(*this)
{
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	// Initialize LgEntity's audio bank pointer
	LtGAudioManager *pAudioManager = LtGAudioManager::GetInstance();
	pAudioManager->Init(initStruct);
	pAudioManager->LinkSoundandWaveInformation((const char ***)szWAVEDEPENDENCIES, (char **)szSOUNDBANKS);
	sm_pSoundBank = LtGAudioManager::GetInstance()->Load("basegame");
}

HarvestBoom::~HarvestBoom()
{
}

/*static*/ LtGAudioSndBank *HarvestBoom::GetSndBank()
{
	return sm_pSoundBank;
}

/*virtual*/ bool HarvestBoom::Initialize() /*override*/
{
	m_pCamera = Window().CreateCamera2d();

	Input().MapBtn(ToggleFPS, HYKEY_F);
	Input().MapBtn(ToggleGrid, HYKEY_G);
	Input().MapBtn(MoveUp, HYKEY_Up);
	Input().MapAlternativeBtn(MoveUp, HYKEY_W);
	Input().MapBtn(MoveRight, HYKEY_Right);
	Input().MapAlternativeBtn(MoveRight, HYKEY_D);
	Input().MapBtn(MoveDown, HYKEY_Down);
	Input().MapAlternativeBtn(MoveDown, HYKEY_S);
	Input().MapBtn(MoveLeft, HYKEY_Left);
	Input().MapAlternativeBtn(MoveLeft, HYKEY_A);
	Input().MapBtn(UseEquip, HYKEY_Space);

	m_World.ConstructLevel();
	m_World.Load();

	return true;
}

/*virtual*/ bool HarvestBoom::Update() /*override*/
{
	if(Input().IsActionReleased(ToggleFPS))
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
