#pragma once
#include "pch.h"

enum EquipedItemType
{
	EQUIP_Hoe = 0,
	EQUIP_Harvest,
	EQUIP_Corn,
	EQUIP_Eggplant,
	EQUIP_Pumpkin,
	EQUIP_Gernaium,
	EQUIP_Marigold,
	EQUIP_Vine
};

class Values
{
	static Values *	sm_pInstance;

	Values();
	~Values();

public:
	static void Init();
	static Values *Get();

	const uint32	m_uiSTARTING_MONEY;
	const uint32	m_uiSTARTING_CORNSEEDS;
	const uint32	m_uiSTARTING_EGGPLANTSEEDS;
	const uint32	m_uiSTARTING_PUMPKINSEEDS;

	const uint32	m_uiGIFTED_GERNAIUMSEEDS;
	const uint32	m_uiGIFTED_MARIGOLDSEEDS;
	const uint32	m_uiGIFTED_VINESEEDS;

	const uint32	m_uiHARVEST_CORNVALUE;
	const uint32	m_uiHARVEST_EGGPLANTVALUE;
	const uint32	m_uiHARVEST_PUMPKINVALUE;

	const uint32	m_uiCOST_CORNSEEDS;
	const uint32	m_uiCOST_EGGPLANTSEEDS;
	const uint32	m_uiCOST_PUMPKINSEEDS;
	const uint32	m_uiCOST_GERNAIUMSEEDS;
	const uint32	m_uiCOST_MARIGOLDSEEDS;
	const uint32	m_uiCOST_VINESEEDS;

	const uint32	m_uiBILLS_RENT;
	const uint32	m_uiBILLS_FOOD;
	const uint32	m_uiBILLS_AC;

	const uint32	m_uiENABLE_DEFENSE_DAY;

	int32			m_iSavings;

	uint32			m_uiSeedsCorn;
	uint32			m_uiSeedsEggplant;
	uint32			m_uiSeedsPumpkin;
	uint32			m_uiSeedsGernaium;
	uint32			m_uiSeedsMarigold;
	uint32			m_uiSeedsVine;

	uint32			m_uiHarvestCorn;
	uint32			m_uiHarvestEggplant;
	uint32			m_uiHarvestPumpkin;

	uint32			m_uiCurrentDay;

	EquipedItemType	m_eEquipedItem;
};
