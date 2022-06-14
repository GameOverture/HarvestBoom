#pragma once
#include "pch.h"

enum EquipedItemType
{
	EQUIP_Nothing = 0,
	EQUIP_Hoe,
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
	void Reset();

	const float		m_fPLAYER_MAXVELOCITY;
	const float		m_fPLAYER_ACCEL;
	const float		m_fPLAYER_DECEL;

	const float		m_fSTAMINA_RUN;
	const float		m_fSTAMINA_ACTION;
	const float		m_fSTAMINA_AC;
	const float		m_fSTAMINA_NO_VITAMIN_PENALTY;
	const float		m_fSTAMINA_EATCORNMODIFIER;
	const float		m_fSTAMINA_EATEGGPLANTMODIFIER;
	const float		m_fSTAMINA_EATPUMPKINMODIFIER;

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
	const uint32	m_uiBILLS_VITAMINS;
	const uint32	m_uiBILLS_AC;

	const uint32	m_uiSTARTING_MONEY;
	const bool		m_bCAN_GO_BANKRUPT;

	const uint32	m_uiSTARTING_CORNSEEDS;
	const uint32	m_uiSTARTING_EGGPLANTSEEDS;
	const uint32	m_uiSTARTING_PUMPKINSEEDS;
	const uint32	m_uiSTARTING_CORNHARVEST;
	const uint32	m_uiSTARTING_EGGPLANTHARVEST;
	const uint32	m_uiSTARTING_PUMPKINHARVEST;

	const float		m_fDAY_LENGTH;
	const uint32	m_uiNUM_DAYS_TO_WIN;

	const float		m_fDURATION_HOEDIRT;
	const float		m_fDURATION_PLANTCORN;
	const float		m_fDURATION_PLANTEGGPLANT;
	const float		m_fDURATION_PLANTPUMPKIN;
	const float		m_fDURATION_PLANTGERNAIUM;
	const float		m_fDURATION_PLANTMARIGOLD;
	const float		m_fDURATION_PLANTVINE;
	const float		m_fDURATION_HARVESTCORN;
	const float		m_fDURATION_HARVESTEGGPLANT;
	const float		m_fDURATION_HARVESTPUMPKIN;

	const float		m_fGROW_CORN;
	const float		m_fGROW_EGGPLANT;
	const float		m_fGROW_PUMPKIN;
	const float		m_fGROW_GERNAIUM;
	const float		m_fGROW_MARIGOLD;
	const float		m_fGROW_VINE;

	const uint32	m_uiENABLE_DEFENSE_DAY;

	const uint32	m_uiNUMBITES_BEETLE;
	const uint32	m_uiNUMBITES_ANT;
	const uint32	m_uiNUMBITES_SPIDER;

	const uint32	m_uiDAMAGE_BEETLE;
	const uint32	m_uiDAMAGE_ANT;
	const uint32	m_uiDAMAGE_SPIDER;

	int32			m_iSavings;
	float			m_fStamina;

	uint32			m_uiSeedsCorn;
	uint32			m_uiSeedsEggplant;
	uint32			m_uiSeedsPumpkin;
	uint32			m_uiSeedsGernaium;
	uint32			m_uiSeedsMarigold;
	uint32			m_uiSeedsVine;

	uint32			m_uiHarvestCorn;
	uint32			m_uiHarvestEggplant;
	uint32			m_uiHarvestPumpkin;

	uint32			m_uiHarvestSoldAmt;

	uint32			m_uiCurrentDay;

	EquipedItemType	m_eEquipedItem;

	bool			m_bVitaminStrength;
	bool			m_bAirConditioning;

	uint32			m_uiDamageCost;

	void Sync();
};
