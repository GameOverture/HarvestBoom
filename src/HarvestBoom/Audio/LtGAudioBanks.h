/***************************************************************************************
 * LtGAudioBanks.h
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
#pragma once

#include <xact3.h>
#include <vector>
using std::vector;


//#include "LtGAudioCues.h"

class LtGAudioManager;

class LtGAudioWavBank
{
	friend class LtGAudioManager;

	IXACT3WaveBank *	m_pWaveBankInterface;
	void *				m_pWaveBankData;

	char *				m_szWavBankName;
	int					m_iRefs;					// How many sound banks reference this wav bank

	LtGAudioWavBank(const char *szWavBankName, void *pData, IXACT3WaveBank *pSndBankInterface);
	~LtGAudioWavBank(void);
};

enum CueFlags	
{
	CUEVOLUME_FADESTOP	= 1 << 0,
	CUEVOLUME_FADE		= 1 << 1,

};
	
class LtGAudioSndBank
{
	struct CSoundObj
	{
		CSoundObj() 
		{
			fTargetVolume = 1.0f;
			m_iFlags = 0;
		}
		~CSoundObj() {}

		IXACT3Cue * pCue;
		float       fTargetVolume;
		bool		m_iFlags;
	};

	friend class LtGAudioManager;
	
	IXACT3SoundBank *	m_pSoundBankInterface;
	void *				m_pSoundBankData;

	char *				m_szSndBankName;
	int					m_iCachedIndex;		// Stores the index into the LtGAduioLinks.h's szSOUNDBANKS string array for quicker lookup

	vector<CSoundObj> m_vActiveCues;

	LtGAudioSndBank(const char *szSndBankName, void *pData, IXACT3SoundBank *pSndBankInterface, int iCachedIndex);
	~LtGAudioSndBank(void);

	
	void Update();

public:
	
	void Play(unsigned int uiCueIndex, XACTTIME iTimeOffset = 0, IXACT3Cue **ppCue = NULL);
	
	///////////////////////////////////////////////
	// Is Playing
	// Checks if a cueindex is currently playing
	// XACTINDEX iCueIndex - The cue index to check
	///////////////////////////////////////////////
	bool IsPlaying(XACTINDEX iCueIndex);

	///////////////////////////////////////////////
	// Is Playing
	// Checks if a cueindex is currently playing
	// const char * pCueName - The cue name ID to check
	///////////////////////////////////////////////
	bool IsPlaying(const char * pCueName);

	void SetCueVolume(XACTINDEX iCueIndex, float fVolume );

	void SetCuePitch (XACTINDEX iCueIndex, float fPitchVol );
	
	void Stop(unsigned int uiCueIndex, bool bStopImmediate = false);
};

