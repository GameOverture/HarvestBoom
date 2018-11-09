/***************************************************************************************
 * LtGAudioBanks.cpp
 *
 * Copyright (c) 2010 Lightning Gaming, Inc.
 * All Rights Reserved.
 *
 * Permission to use, copy, modify, and distribute this software 
 * is hereby NOT granted. Please refer to the file "copyright.html"
 * for further important copyright and licensing information.
 *
 * PURPOSE:
 * TBD
 ***************************************************************************************/
#include "LtGAudioBanks.h"
#include "Harmony/HyEngine.h"

LtGAudioWavBank::LtGAudioWavBank(const char *szWavBankName, void *pData, IXACT3WaveBank *pSndBankInterface)
{
	m_szWavBankName = NULL;
	size_t iStrSize = strlen(szWavBankName) + 1; // +1 for NULL terminator
	m_szWavBankName = HY_NEW char[iStrSize];
	strcpy_s(m_szWavBankName, iStrSize, szWavBankName);
//	DynamicStringCopy(m_szWavBankName, szWavBankName);

	m_pWaveBankInterface = pSndBankInterface;
	m_pWaveBankData = pData;

	m_iRefs = 1;
}
LtGAudioWavBank::~LtGAudioWavBank()
{
	delete [] m_szWavBankName;

	// Cleanup wav bank memory
	if(m_pWaveBankData)
	{
		UnmapViewOfFile(m_pWaveBankData);
		m_pWaveBankData = NULL;
	}
}

LtGAudioSndBank::LtGAudioSndBank(const char *szSndBankName, void *pData, IXACT3SoundBank *pSndBankInterface, int iCachedIndex)
{
	m_szSndBankName = NULL;
	size_t iStrSize = strlen(szSndBankName) + 1; // +1 for NULL terminator
	m_szSndBankName = HY_NEW char[iStrSize];
	strcpy_s(m_szSndBankName, iStrSize, szSndBankName);
//	DynamicStringCopy(m_szSndBankName, szSndBankName);

	m_pSoundBankInterface = pSndBankInterface;
	m_pSoundBankData = pData;

	m_vActiveCues.clear();

	m_iCachedIndex = iCachedIndex;
}
LtGAudioSndBank::~LtGAudioSndBank()
{
	m_vActiveCues.clear();

	delete [] m_szSndBankName;

	// Cleanup sound bank memory
	if(m_pSoundBankData)
	{
		delete[] m_pSoundBankData;
		m_pSoundBankData = NULL;
	}
}

void LtGAudioSndBank::Update()
{


}

void LtGAudioSndBank::Play(unsigned int uiCueIndex, XACTTIME iTimeOffset, IXACT3Cue **ppCue)
{
	if(ppCue == NULL)
		m_pSoundBankInterface->Play(uiCueIndex, NULL, iTimeOffset, /*&pCue*/NULL);
	else
		m_pSoundBankInterface->Play(uiCueIndex, NULL, iTimeOffset, ppCue);
}

bool LtGAudioSndBank::IsPlaying(XACTINDEX iCueIndex)
{
	XACTINDEX iIndex = iCueIndex;
	XACT_CUE_PROPERTIES  cueProp;

	// Access the properties so we can check the current active instances of this cue
	m_pSoundBankInterface->GetCueProperties(iIndex, &cueProp);
	
	return (cueProp.currentInstances > 0) ? true : false ;
}

bool LtGAudioSndBank::IsPlaying(const char * pCueName)
{
	// Gets the cue index associated with the name (pCueName)
	XACTINDEX iIndex = m_pSoundBankInterface->GetCueIndex(pCueName);
	
	XACT_CUE_PROPERTIES cueProp;

	// Access the properties so we can check the current active instances of this cue
	m_pSoundBankInterface->GetCueProperties(iIndex, &cueProp);

	return (cueProp.currentInstances > 0) ? true : false ;
}

void LtGAudioSndBank::Stop(unsigned int uiCueIndex, bool bStopImmediate)
{
	m_pSoundBankInterface->Stop(uiCueIndex, bStopImmediate ? XACT_FLAG_SOUNDBANK_STOP_IMMEDIATE : NULL);
}

void LtGAudioSndBank::SetCueVolume(XACTINDEX iCueIndex, float fVolume)
{
	LPXACT_CUE_INSTANCE_PROPERTIES pCueProperties = NULL;
	XACTINDEX iIndex = 0;
	
	for(unsigned int i = 0; i < m_vActiveCues.size(); i++)
	{
		m_vActiveCues[i].pCue->GetProperties(&pCueProperties);

		iIndex = m_pSoundBankInterface->GetCueIndex(pCueProperties->cueProperties.friendlyName);

		if(iIndex == iCueIndex)
		{
			XACTVARIABLEVALUE value;
			XACTINDEX VolumeIndex = m_vActiveCues[i].pCue->GetVariableIndex("Volume");
			m_vActiveCues[i].pCue->GetVariable(VolumeIndex, &value);

			m_vActiveCues[i].pCue->SetVariable(VolumeIndex, fVolume);
			break;
		}
	}
}

void LtGAudioSndBank::SetCuePitch(XACTINDEX iCueIndex, float fPitchVol)
{
	LPXACT_CUE_INSTANCE_PROPERTIES pCueProperties = NULL;
	XACTINDEX iIndex = 0;
	
	for(unsigned int i = 0; i < m_vActiveCues.size(); i++)
	{
		m_vActiveCues[i].pCue->GetProperties(&pCueProperties);

		iIndex = m_pSoundBankInterface->GetCueIndex(pCueProperties->cueProperties.friendlyName);
		
		if(iIndex == iCueIndex)
		{
			XACTINDEX PitchIndex = m_vActiveCues[i].pCue->GetVariableIndex("Pitch");
			XACTVARIABLEVALUE value;
			m_vActiveCues[i].pCue->GetVariable(PitchIndex, &value);
			m_vActiveCues[i].pCue->SetVariable(PitchIndex, fPitchVol);
			break;
		}
	}
}

