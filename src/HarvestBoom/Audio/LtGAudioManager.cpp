/***************************************************************************************
 * LtGEnt2dManager.cpp
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

#include "LtgAudioManager.h"
//#define _WIN32_WINNT 0x0501
#define _WIN32_DCOM

#include <objbase.h>


LtGAudioManager *LtGAudioManager::m_Instance = NULL;

void WINAPI XACTNotificationCallback(const XACT_NOTIFICATION* pNotification);

LtGAudioManager::LtGAudioManager() /*: m_szSOUNDBANKS(NULL), m_szWAVEDEPENDENCIES(NULL)*/
{
	HRESULT hr;

	m_iNumLinks = 0;
	
	InitializeCriticalSection(&m_CritSection);

	hr = CoInitializeEx(NULL, COINIT_MULTITHREADED);  // COINIT_APARTMENTTHREADED will work too
	if(FAILED(hr))
	{
		HyLog("CoInitializeEx() failed with error code: " << hr);
	//	LtGEngine::GetInstance()->Logf("CoInitializeEx() failed with error code: %i", LOG_ERROR, hr);
	}

	DWORD dwCreationFlags = 0;
	hr = XACT3CreateEngine(dwCreationFlags, &m_pXACTEngine);
	if(FAILED(hr) || m_pXACTEngine == NULL)
	{
		HyLog("XACT3CreateEngine() failed with error code: " << hr);
	//	LtGEngine::GetInstance()->Logf("XACT3CreateEngine() failed with error code: %i", LOG_ERROR, hr);
	}



}

LtGAudioManager::~LtGAudioManager(void)
{
	// Delete our copied information of WaveDepen & Soundbanks
	// since they are no longer needed
	//int j = 0;
	//for(int i = 0; i < m_iNumLinks; i++)
	//{
	//	if(*m_szWAVEDEPENDENCIES[i])
	//	{
	//		while(m_szWAVEDEPENDENCIES[i][j]) 
	//		{
	//			m_szWAVEDEPENDENCIES[i][j] = NULL;
	//			++j;
	//		}
	//	
	//		delete m_szWAVEDEPENDENCIES[i];
	//		m_szWAVEDEPENDENCIES[i] = NULL;
	//		j = 0;
	//	}
	//}

	//for(int i = 0; i < m_iNumLinks; i++)
	//{
	//	if(m_szSOUNDBANKS[i])
	//	{
	//		delete m_szSOUNDBANKS[i];
	//		m_szSOUNDBANKS[i] = NULL;
	//	}
	//}
	//delete [] m_szSOUNDBANKS;
	//m_szSOUNDBANKS = NULL;



	// Note that XACTShutDown is synchronous and will take some time to complete 
	// if there are still playing cues.  Also ShutDown() is generally only 
	// called when a game exits and is not the preferred method of changing audio 
	// resources. To know when it is safe to free wave/sound bank data without 
	// shutting down the XACT engine, use the XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED 
	// or XACTNOTIFICATIONTYPE_WAVEBANKDESTROYED notifications 
	if(m_pXACTEngine)
	{
		m_pXACTEngine->ShutDown();
		m_pXACTEngine->Release();
	}

	// Explicitly invoke all the wav and sound bank dtors. No need to call Unload (Destroy) because
	// we called the XACT engine's ShutDown()
	for(unsigned int i = 0; i < m_SoundBanks.size(); i++)
		delete m_SoundBanks[i];//->~LtGAudioSndBank();
	for(unsigned int i = 0; i < m_WaveBanks.size(); i++)
		delete m_WaveBanks[i];//->~LtGAudioWavBank();

	// Crit section is no longer needed
	DeleteCriticalSection(&m_CritSection);
	CoUninitialize();
}

LtGAudioManager *LtGAudioManager::GetInstance()
{
	if(!m_Instance)
		m_Instance = HY_NEW LtGAudioManager();

	return m_Instance;
}

/*static*/ void LtGAudioManager::Delete()
{
	delete m_Instance;
}

void LtGAudioManager::Init(HarmonyInit &initStruct)
{
	m_strGameDir = initStruct.sDataDir;

	// Load the global settings file and pass it into XACTInitialize
	VOID* pGlobalSettingsData = NULL;
	DWORD dwGlobalSettingsFileSize = 0;
	bool bSuccess = false;

	HANDLE hFile;
	DWORD dwBytesRead;

	// Assemble the path to the sound bank file
	char szSndSettingsFilePath[128];
	ConvertAudioFileNameToPath(szSndSettingsFilePath, "LtGGlobalSettings", ".xgs", 128);

	//Use create file to load the file it into memory and read in the settings
	hFile = CreateFileA(szSndSettingsFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile)
	{
		dwGlobalSettingsFileSize = GetFileSize(hFile, NULL);
		if(dwGlobalSettingsFileSize != INVALID_FILE_SIZE)
		{
			pGlobalSettingsData = CoTaskMemAlloc(dwGlobalSettingsFileSize);

			if(pGlobalSettingsData)
			{
				if(0 != ReadFile(hFile, pGlobalSettingsData, dwGlobalSettingsFileSize, &dwBytesRead, NULL))
				{
					bSuccess = true;
				}
			}
		}
		CloseHandle(hFile);
	}
	else
	{
		HyLog("m_pXACTEngine->Initialize() failed to create Global Settings File!");
		// LtGEngine::GetInstance()->Log("m_pXACTEngine->Initialize() failed to create Global Settings File!", LOG_ERROR);
	}

	if(!bSuccess)
	{
		HyLog("m_pXACTEngine->Initialize() Global Settings was not sucessfully parsed!");
		//	LtGEngine::GetInstance()->Log("m_pXACTEngine->Initialize() Global Settings was not sucessfully parsed!", LOG_ERROR);

		if(pGlobalSettingsData)
			CoTaskMemFree(pGlobalSettingsData);

		pGlobalSettingsData = NULL;
		dwGlobalSettingsFileSize = 0;
	}

	// Initialize & create the XACT runtime 
	XACT_RUNTIME_PARAMETERS xrParams = { 0 };
	xrParams.pGlobalSettingsBuffer = pGlobalSettingsData;
	xrParams.globalSettingsBufferSize = dwGlobalSettingsFileSize;
	xrParams.globalSettingsFlags = XACT_FLAG_GLOBAL_SETTINGS_MANAGEDATA;

	xrParams.lookAheadTime = XACT_ENGINE_LOOKAHEAD_DEFAULT;
	xrParams.fnNotificationCallback = XACTNotificationCallback;
	HRESULT hr = m_pXACTEngine->Initialize(&xrParams);
	if(FAILED(hr))
	{
		HyLog("m_pXACTEngine->Initialize() failed with error code: " << hr);
		//		LtGEngine::GetInstance()->Logf("m_pXACTEngine->Initialize() failed with error code: %X", LOG_ERROR, hr);
	}

	//---------------------------------//
	// Register for XACT notifications //
	//---------------------------------//

	// The "wave bank prepared" notification will let the app know when it is save to use
	// play cues that reference streaming wave data.
	XACT_NOTIFICATION_DESCRIPTION desc = { 0 };
	//desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
	//desc.type = XACTNOTIFICATIONTYPE_WAVEBANKPREPARED;
	//m_pXACTEngine->RegisterNotification(&desc);

	// The "sound bank destroyed" notification will let the app know when it is save to use
	// play cues that reference streaming wave data.
	desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
	desc.type = XACTNOTIFICATIONTYPE_WAVEBANKDESTROYED;
	m_pXACTEngine->RegisterNotification(&desc);

	desc.flags = XACT_FLAG_NOTIFICATION_PERSIST;
	desc.type = XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED;
	m_pXACTEngine->RegisterNotification(&desc);

	m_dUpdateThrottle = 0.0;
}

void LtGAudioManager::StopAllSfxInCategory(const char *szCategoryName)
{
	XACTCATEGORY sCat = m_pXACTEngine->GetCategory(szCategoryName);
	m_pXACTEngine->Stop(sCat, XACT_FLAG_ENGINE_STOP_IMMEDIATE);
}
void LtGAudioManager::PauseAllSfxInCategory(const char *szCategoryName, bool bPause)
{
	XACTCATEGORY sCat = m_pXACTEngine->GetCategory(szCategoryName);
	m_pXACTEngine->Pause(sCat, bPause);
}

////////

void LtGAudioManager::SetVolumeInCategory(const char *szCategoryName, float fVolume)
{
	XACTCATEGORY sCat = m_pXACTEngine->GetCategory(szCategoryName);
	m_pXACTEngine->SetVolume(sCat, fVolume);
}

float LtGAudioManager::GetVolumeInCategory(const char *szCategoryName)
{ 
	return 1.0f;
	//XACTCATEGORY sCat = m_pXACTEngine->GetCategory(szCategoryName);
	//return m_pXACTEngine->GetVolume(sCat);
}
//--------------------------------------------------------------------------------------
// Read and register the sound bank file with XACT.  Do not use memory mapped file IO because the 
// memory needs to be read/write and the working set of sound banks are small.
//--------------------------------------------------------------------------------------
LtGAudioSndBank *LtGAudioManager::Load(const char *szSoundBank)
{
	HyLog("Loading Sound Bank: " << szSoundBank);

	// Convert sound bank name to lowercase for comparison
	char szSndBankFileName[64];
	strcpy_s(szSndBankFileName, 64, szSoundBank);
	for(int i = 0; szSndBankFileName[i] != '\0'; i++)
		szSndBankFileName[i] = tolower(szSndBankFileName[i]);

	// Don't load the same sound bank twice
	for(unsigned int i = 0; i < m_SoundBanks.size(); i++)
	{
		if(0 == strcmp(m_SoundBanks[i]->m_szSndBankName, szSndBankFileName))
			return m_SoundBanks[i];
	}

	// Assemble the path to the sound bank file
	char szSndBankFilePath[128];
	ConvertAudioFileNameToPath(szSndBankFilePath, szSndBankFileName, ".xsb", 128);
	
	// Load the sound bank...
	DWORD dwFileSize;
	HRESULT hr;
	HANDLE hFile;
	DWORD dwBytesRead;

	hr = E_FAIL; // assume failure

	hFile = CreateFileA((LPCSTR)szSndBankFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		HyLog("CreateFile() failed: Could not load the sound bank into a buffer.");
//		LtGEngine::GetInstance()->Log("CreateFile() failed: Could not load the sound bank into a buffer.", LOG_WARNING);
		return NULL;
	}

	dwFileSize = GetFileSize( hFile, NULL );
	if(dwFileSize == -1)
	{
		HyLog("LoadSoundBank's GetFileSize() failed");
	//	LtGEngine::GetInstance()->Log("LoadSoundBank's GetFileSize() failed", LOG_WARNING);
		return NULL;
	}

	// Allocate the data here and free the data when receiving the sound bank destroyed notification
	LtGAudioSndBank *	pSndBank = NULL;
	IXACT3SoundBank *	pSoundBankInterface = NULL;
	void *				pSoundBankData = HY_NEW BYTE[dwFileSize];

	if(0 != ReadFile(hFile, pSoundBankData, dwFileSize, &dwBytesRead, NULL))
	{		
		// Find wav bank dependencies for this sound bank, and load the ones that aren't already 
		// loaded while incrementing the ref counter for the ones that are.
		int iCachedIndex = LoadSndBankDependencies(szSndBankFileName);

		hr = m_pXACTEngine->CreateSoundBank(pSoundBankData, dwFileSize, 0, 0, &pSoundBankInterface);
		if(FAILED(hr))
		{
			switch(hr)
			{
			case XACTENGINE_E_OUTOFMEMORY               : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDARG                : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NOTIMPL                   : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_FAIL                      : {int asdf = 0; asdf++; }break;

			case XACTENGINE_E_ALREADYINITIALIZED        : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NOTINITIALIZED            : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_EXPIRED                   : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NONOTIFICATIONCALLBACK    : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NOTIFICATIONREGISTERED    : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDUSAGE              : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDDATA               : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INSTANCELIMITFAILTOPLAY   : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NOGLOBALSETTINGS          : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDVARIABLEINDEX      : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDCATEGORY           : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDCUEINDEX           : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDWAVEINDEX          : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDTRACKINDEX         : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDSOUNDOFFSETORINDEX : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_READFILE                  : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_UNKNOWNEVENT              : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INCALLBACK                : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NOWAVEBANK                : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_SELECTVARIATION           : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_MULTIPLEAUDITIONENGINES   : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_WAVEBANKNOTPREPARED       : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NORENDERER                : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_INVALIDENTRYCOUNT         : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_SEEKTIMEBEYONDCUEEND      : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_SEEKTIMEBEYONDWAVEEND     : {int asdf = 0; asdf++; }break;
			case XACTENGINE_E_NOFRIENDLYNAMES           : {int asdf = 0; asdf++; }break;

			case XACTENGINE_E_AUDITION_WRITEFILE:				{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_NOSOUNDBANK:				{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_INVALIDRPCINDEX:			{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_MISSINGDATA:				{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_UNKNOWNCOMMAND:			{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_INVALIDDSPINDEX:			{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_MISSINGWAVE:				{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_CREATEDIRECTORYFAILED:	{int asdf = 0; asdf++; }break;
			case XACTENGINE_E_AUDITION_INVALIDSESSION:			{int asdf = 0; asdf++; }break;
			}

			HyLog("LoadSoundBank's CreateSoundBank() failed with error code: " <<  hr);
		//	LtGEngine::GetInstance()->Logf("LoadSoundBank's CreateSoundBank() failed with error code: %x", LOG_WARNING, hr);
			return NULL;
		}

		pSndBank = HY_NEW LtGAudioSndBank(szSndBankFileName, pSoundBankData, pSoundBankInterface, iCachedIndex);
		m_SoundBanks.push_back(pSndBank);
	}
	else
	{
		delete [] pSoundBankData;

		HyLog("LoadSoundBank's ReadFile() failed");
	//	LtGEngine::GetInstance()->Log("LoadSoundBank's ReadFile() failed", LOG_WARNING);
		return NULL;
	}

	// LtGAudioSndBank::pSndBank maintains a handle on the file so close this unneeded handle
	CloseHandle(hFile);

	return pSndBank;
}

//--------------------------------------------------------------------------------------
// This function invokes the Destroy() method of the IXACT3SoundBank interface and decrements 
// any WavBanks references associated with it. 
// This should stops all cues residing in this sound bank that are currently playing, but 
// it does not free the associated memory right away. The memory will be freed once the XACT 
// callback fires the XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED event.
//--------------------------------------------------------------------------------------
void LtGAudioManager::UnLoad(LtGAudioSndBank **ppSndBank)
{
	UnRefWavBankDependencies((*ppSndBank));

	(*ppSndBank)->m_pSoundBankInterface->Destroy();
//	DEAD_MEMORY(*ppSndBank, LtGAudioSndBank);
}

bool LtGAudioManager::LinkSoundandWaveInformation(const char *** pWaveDepend, char ** pSoundBank)
{
	
	const char **ptr;
	ptr = &pWaveDepend[2][0];

	 //After this the subsequent elements can be accessed as
	// *(ptr + (i * j)) where i and j refer to array[i][j]
	const char * pAAA = (char *)ptr;

	int iCounter = 0;
	char * pBankName = pSoundBank[iCounter];

	// Iterate the sound banks until we hit NULL so we know how many
	// sound banks this project is using
	while(pBankName)
	{
		pBankName = pSoundBank[iCounter];
		++iCounter;
	}
	
	// The number of sound banks in this current project
	m_iNumLinks = iCounter - 1;

	// Determine max dependancy links
	int iDependLinks = 0;
	while(&pWaveDepend[iDependLinks][0])
	{
		char * pTest = (char *)&pWaveDepend[iDependLinks][0];
		iDependLinks++;
	}
	
	iDependLinks = (iDependLinks + 1) * m_iNumLinks;
	
	// Loop through and copy over the information from
	// pWaveDepend into our Audio Managers copy (m_szWAVEDEPENDENCIES) 
	//char ** pPassingIn = NULL;
	int iWaveIndex = 0;
	for(int i = 0; i < m_iNumLinks; ++i)
	{
		//pPassingIn = HY_NEW char*[2];
		std::vector<std::string> passingInList;

		for(int j = 0; j < iDependLinks; j++,iWaveIndex++)
		{
			char * pName = (char *)&pWaveDepend[iWaveIndex][0];
		
			if(!pName)
			{
				//pPassingIn[j] = NULL;
				passingInList.push_back(std::string(""));
				++iWaveIndex;
				break;
			}
			
//			int iLen = strlen((char *)&pWaveDepend[iWaveIndex][0]);
			const char * anothertest = (char *)&pWaveDepend[iWaveIndex][0];

			passingInList.push_back(std::string(anothertest));
			//pPassingIn[j] = HY_NEW char[strlen(anothertest) + 1];
			//strcpy_s(pPassingIn[j], strlen(anothertest) + 1, anothertest);
		
		}

		m_WaveDependenciesList.push_back(passingInList);
		//m_szWAVEDEPENDENCIES.push_back(pPassingIn);
	}

	/////////////////////////////////////////////

	// Instantiate our sound bank names to match pSoundBank
	//m_szSOUNDBANKS = HY_NEW char*[m_iNumLinks];

	// Loop through and copy over the information from
	// pSoundBank into our Audio Managers copy (m_szSOUNDBANKS) 
	for(int i = 0; i < m_iNumLinks; i++)
	{
		//int iBuffer = strlen(pSoundBank[i]);

		m_SoundBankList.push_back(std::string(pSoundBank[i]));
		//m_szSOUNDBANKS[i] = HY_NEW char[strlen(pSoundBank[i]) + 1];
		//strcpy_s(m_szSOUNDBANKS[i], strlen(pSoundBank[i]) + 1, pSoundBank[i]);
	}

	return true;
}

//-----------------------------------------------------------------------------------------
// Takes a const char * that represents an audio file and converts it to the absolute path
// on the file system. 'szExpectedExt' is what extension the audio should have (ex ".xsb"), which will be 
// appended to 'szFullAudioFilePath' if not included in 'szAudioFileName'.
//-----------------------------------------------------------------------------------------
void LtGAudioManager::ConvertAudioFileNameToPath(char *szFullAudioFilePath, const char* szAudioFileName, const char *szExpectedExt, int iFilePathLength)
{
//	strcpy_s(szFullAudioFilePath, iFilePathLength, THEMES_DIR);

	szFullAudioFilePath[0] = '\0';

	//size_t uiCharID = m_strGameDir.find('/');
	//char NewThemePath[64];
	//size_t uiNameLength = m_strGameDir._Copy_s(NewThemePath, 64, m_strGameDir.length() - uiCharID, uiCharID + 1);
	//NewThemePath[uiNameLength] = '\0';


	//strcat_s(szFullAudioFilePath, iFilePathLength, "themes\\");
	//strcat_s(szFullAudioFilePath, iFilePathLength, NewThemePath);
	strcat_s(szFullAudioFilePath, iFilePathLength, m_strGameDir.c_str());
	strcat_s(szFullAudioFilePath, iFilePathLength, AUDIO_DIR);
	strcat_s(szFullAudioFilePath, iFilePathLength, szAudioFileName);

	// Convert string to lowercase for comparison
	for(int i = 0; szFullAudioFilePath[i] != '\0'; i++)
		szFullAudioFilePath[i] = tolower(szFullAudioFilePath[i]);

	// Append the extension if user didn't use one
	if(0 != strcmp(szExpectedExt, &szFullAudioFilePath[strlen(szFullAudioFilePath) - 4]))
		strcat_s(szFullAudioFilePath, iFilePathLength, szExpectedExt);
}

//-----------------------------------------------------------------------------------------
// When the XACT project is built, it generates a report file which apart of a custom build
// process, creates the src file LtGAudioLinks.h. This header describes the dependencies
// between sound banks and their required wav banks. Invoking this function will load any
// wav banks not currently in memory, or increment their reference count if they already are.
//
// The integer returned is the index into LtGAudioLink szSOUNDBANKS's array for future lookup
//-----------------------------------------------------------------------------------------
int LtGAudioManager::LoadSndBankDependencies(const char *szSndBankName)
{
	// Find the index to be used in szWAVEDEPENDENCIES which matches the index of szSOUNDBANKS
	int iIndex = 0;
	while(true)
	{
		if(0 == strcmp(m_SoundBankList[iIndex].c_str(), szSndBankName)) //m_szSOUNDBANKS[iIndex], szSndBankName))
			break;

		iIndex++;

		if(m_SoundBankList[iIndex].c_str() == nullptr)// if(m_szSOUNDBANKS[iIndex] == NULL)
		{
			HyLog("Could not find the soundbank " << szSndBankName  << " Its dependencies have not been loaded!");
		//	LtGEngine::GetInstance()->Logf("Could not find the soundbank '%s'. Its dependencies have not been loaded!", LOG_WARNING, szSndBankName);
			return -1;
		}
	}

	// Load all the wav banks that this sound bank requires
	int iIndex2 = 0;
	while(m_WaveDependenciesList[iIndex][iIndex2].c_str() != nullptr)// m_szWAVEDEPENDENCIES[iIndex][iIndex2] != NULL)
	{
		//char * pA = m_szWAVEDEPENDENCIES[iIndex][iIndex2];

		if(FAILED(LoadWavBank(m_WaveDependenciesList[iIndex][iIndex2].c_str())))// m_szWAVEDEPENDENCIES[iIndex][iIndex2])))
		{
			HyLog("Failed loading wav bank: " << m_WaveDependenciesList[iIndex][iIndex2]/*m_szWAVEDEPENDENCIES[iIndex][iIndex2]*/ << " required by snd bank : " << szSndBankName);
		//	LtGEngine::GetInstance()->Logf("Failed loading wav bank: '%s' required by snd bank: '%s'", LOG_WARNING, m_szWAVEDEPENDENCIES[iIndex][iIndex2], szSndBankName);
		}

		iIndex2++;
		if(m_WaveDependenciesList[iIndex].size() > static_cast<uint32>(iIndex2))
			break;
	}

	return iIndex;
}

//-----------------------------------------------------------------------------------------
// This is essentially the opposite of LoadSndBankDependencies(). It figures out the 
// wav bank dependencies and decrements their reference count. If their reference count
// becomes zero because of this it will invoke the Destroy() function of the wav bank interface
//-----------------------------------------------------------------------------------------
void LtGAudioManager::UnRefWavBankDependencies(const LtGAudioSndBank *pSoundBank)
{
	// Find the index to be used in szWAVEDEPENDENCIES which matches the index of szSOUNDBANKS
	int iIndex = pSoundBank->m_iCachedIndex;

	// Unref all the wav banks that this sound bank is associated with
	int iIndex2 = 0;
	while(m_WaveDependenciesList[iIndex][iIndex2].c_str() != nullptr)// m_szWAVEDEPENDENCIES[iIndex][iIndex2] != NULL)
	{
		LtGAudioWavBank *pWavBnk = GetWaveBank(m_WaveDependenciesList[iIndex][iIndex2].c_str());//m_szWAVEDEPENDENCIES[iIndex][iIndex2]); // FIX
		if(pWavBnk)
		{
			pWavBnk->m_iRefs--;
			if(pWavBnk->m_iRefs <= 0)
				pWavBnk->m_pWaveBankInterface->Destroy();
		}
		else if( pSoundBank->m_pSoundBankData != NULL)
		{
			HyLog("Failed finding wav bank: " << m_WaveDependenciesList[iIndex][iIndex2] /*m_szWAVEDEPENDENCIES[iIndex][iIndex2]*/ << " when derefing from snd bank : " << pSoundBank->m_szSndBankName)
		//	LtGEngine::GetInstance()->Logf("Failed finding wav bank: '%s' when derefing from snd bank: '%s'", LOG_WARNING, m_szWAVEDEPENDENCIES[iIndex][iIndex2], pSoundBank->m_szSndBankName);
		} 
		else
		{
			HyLog("Failed finding wav bank: " << m_WaveDependenciesList[iIndex][iIndex2] /*m_szWAVEDEPENDENCIES[iIndex][iIndex2]*/ << " when derefing from snd bank : NULL");
			//LtGEngine::GetInstance()->Logf("Failed finding wav bank: %s when derefing from snd bank: NULL",LOG_WARNING, m_szWAVEDEPENDENCIES[iIndex][iIndex2]);
		}


		iIndex2++;
	}
}

//-----------------------------------------------------------------------------------------
// Iterates through the manager's wav vector and checks if any references is zero or less,
// invoking Destroy on the interface if so.
//-----------------------------------------------------------------------------------------
void LtGAudioManager::GarbageCollectWavBanks()
{
	vector<LtGAudioWavBank *>::iterator it;
	for(it = m_WaveBanks.begin(); it != m_WaveBanks.end(); ++it)
	{
		if((*it)->m_iRefs <= 0)
		{
			(*it)->m_pWaveBankInterface->Destroy();
			return;
		}
	}
}

//--------------------------------------------------------------------------------------
// Retrieves the LtGAudioWavBank pointer from the manager's vector based upon its name.
//--------------------------------------------------------------------------------------
LtGAudioWavBank *LtGAudioManager::GetWaveBank(const char *szWaveBankName)
{
	vector<LtGAudioWavBank *>::iterator it;
	for(it = m_WaveBanks.begin(); it != m_WaveBanks.end(); ++it)
	{
		if(0 == strcmp((*it)->m_szWavBankName, szWaveBankName))
			return (*it);
	}

	return NULL;
}

//--------------------------------------------------------------------------------------
// Create an "in memory" XACT wave bank file using memory mapped file IO
// Memory mapped files tend to be the fastest for most situations assuming you 
// have enough virtual address space for a full map of the file
//--------------------------------------------------------------------------------------
HRESULT LtGAudioManager::LoadWavBank(const char *szWaveBank, bool bStreaming)
{
	// First check if we have loaded this wav bank already
	for(unsigned int i = 0; i < m_WaveBanks.size(); i++)
	{
		if(0 == strcmp(m_WaveBanks[i]->m_szWavBankName, szWaveBank))
		{
			m_WaveBanks[i]->m_iRefs++;
			return S_OK;
		}
	}

	// Not found, load this wav bank
	DWORD dwFileSize;
	HRESULT hr;
	HANDLE hFile;
	HANDLE hMapFile;

	hr = E_FAIL;

	// Assemble the path to the sound bank file
	char szWavBankFilePath[128];
	ConvertAudioFileNameToPath(szWavBankFilePath, szWaveBank, ".xwb", 128);
	
	// Load the wave bank into a buffer
	hFile = CreateFileA(/*(LPCWSTR)*/szWavBankFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);
	if(hFile == INVALID_HANDLE_VALUE)
	{
		HyLog("CreateFile() failed: Could not load the wave bank into a buffer");
//		LtGEngine::GetInstance()->Log("CreateFile() failed: Could not load the wave bank into a buffer.", LOG_WARNING);
		return E_FAIL;
	}
	
	dwFileSize = GetFileSize(hFile, NULL);
	if(dwFileSize == -1)
	{
		HyLog("LoadWaveBank's GetFileSize() failed");
	//	LtGEngine::GetInstance()->Log("LoadWaveBank's GetFileSize() failed", LOG_WARNING);
		return E_FAIL;
	}

	// Create a file map of this buffer
	hMapFile = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, dwFileSize, NULL);
	if(!hMapFile)
	{
		HyLog("LoadWaveBank's CreateFileMapping() failed");
	//	LtGEngine::GetInstance()->Log("LoadWaveBank's CreateFileMapping() failed", LOG_WARNING);
		return E_FAIL;
	}
	
	// Get the starting address of the mapped view... aka our wavebank buffer
	IXACT3WaveBank *	pWavBankInterface = NULL;
	void *				pWavBankData = MapViewOfFile(hMapFile, FILE_MAP_READ, 0, 0, 0);

	if(pWavBankData)
	{
		hr = m_pXACTEngine->CreateInMemoryWaveBank(pWavBankData, dwFileSize, 0, 0, &pWavBankInterface);
		if(FAILED(hr))
		{
			HyLog("LoadWaveBank's CreateInMemoryWaveBank() failed with error code: " << hr);
		//	LtGEngine::GetInstance()->Logf("LoadWaveBank's CreateInMemoryWaveBank() failed with error code: %x", LOG_WARNING, hr);
			return E_FAIL;
		}

		LtGAudioWavBank *pWavBank = HY_NEW LtGAudioWavBank(szWaveBank, pWavBankData, pWavBankInterface);
		m_WaveBanks.push_back(pWavBank);
	}
	else
	{
		HyLog("LoadWaveBank's MapViewOfFile() failed");
	//	LtGEngine::GetInstance()->Log("LoadWaveBank's MapViewOfFile() failed", LOG_WARNING);
	}

	// waveBank.second maintains a handle on the file so close these unneeded handles
	CloseHandle(hMapFile);
	CloseHandle(hFile); 
	
	return S_OK;
}

//-----------------------------------------------------------------------------------------
// This is the callback for handling XACT notifications.  This callback can be executed on a 
// different thread than the app thread so shared data must be thread safe.  The game 
// also needs to minimize the amount of time spent in this callbacks to avoid glitching, 
// and a limited subset of XACT API can be called from inside the callback so 
// it is sometimes necessary to handle the notification outside of this callback.
//-----------------------------------------------------------------------------------------
void WINAPI LtGAudioManager::XACTNotificationCallback(const XACT_NOTIFICATION* pNotification)
{	

	if( pNotification->type == XACTNOTIFICATIONTYPE_WAVEBANKDESTROYED)
	{
		vector<LtGAudioWavBank *>::iterator it;
		for(it = m_Instance->m_WaveBanks.begin(); it != m_Instance->m_WaveBanks.end(); ++it)
		{
			if((*it)->m_pWaveBankInterface == pNotification->waveBank.pWaveBank)
			{
				delete (*it);
				m_Instance->m_WaveBanks.erase(it);
				break;
			}
		}
	}

	if( pNotification->type == XACTNOTIFICATIONTYPE_SOUNDBANKDESTROYED)
	{
		vector<LtGAudioSndBank *>::iterator it;
		for(it = m_Instance->m_SoundBanks.begin(); it != m_Instance->m_SoundBanks.end(); ++it)
		{
			if((*it)->m_pSoundBankInterface == pNotification->soundBank.pSoundBank)
			{
				delete (*it);
				m_Instance->m_SoundBanks.erase(it);
				break;
			}
		}
	}
}

//-----------------------------------------------------------------------------------------
// Calls XACT engine's DoWork() function at a throttled rate.
//-----------------------------------------------------------------------------------------
void LtGAudioManager::Update(/*double dTimeDelta*/)
{
//	PROFILE("Audio Manager");

	// Regulate the update rate so we don't overload the CPU
	m_dUpdateThrottle += Hy_UpdateStep();
	if(m_dUpdateThrottle > 0.016f/*SOUND_RATE_REGULATOR*/)
	{
		m_dUpdateThrottle = 0.0f;
		m_pXACTEngine->DoWork();
	}
	
	
}