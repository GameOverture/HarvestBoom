#include "pch.h"
#include "HarvestBoom.h"

Values *Values::sm_pInstance = nullptr;

Values::Values() :
	m_fPLAYER_MAXVELOCITY(200.0f),	// pixels per second
	m_fPLAYER_ACCEL(300.0f),
	m_fPLAYER_DECEL(600.0f),
	
	m_fSTAMINA_RUN(0.01f),
	m_fSTAMINA_ACTION(0.02f),
	m_fSTAMINA_AC(0.025f),
	m_fSTAMINA_NO_VITAMIN_PENALTY(1.0f),	// Actions take X% more stamina
	m_fSTAMINA_EATCORNMODIFIER(0.2f),
	m_fSTAMINA_EATEGGPLANTMODIFIER(0.4f),
	m_fSTAMINA_EATPUMPKINMODIFIER(1.0f),

	m_uiGIFTED_GERNAIUMSEEDS(3),
	m_uiGIFTED_MARIGOLDSEEDS(3),
	m_uiGIFTED_VINESEEDS(1),

	m_uiHARVEST_CORNVALUE(10),
	m_uiHARVEST_EGGPLANTVALUE(20),
	m_uiHARVEST_PUMPKINVALUE(50),

	m_uiCOST_CORNSEEDS(2),
	m_uiCOST_EGGPLANTSEEDS(4),
	m_uiCOST_PUMPKINSEEDS(10),
	m_uiCOST_GERNAIUMSEEDS(1),
	m_uiCOST_MARIGOLDSEEDS(2),
	m_uiCOST_VINESEEDS(5),

	m_uiBILLS_RENT(30),
	m_uiBILLS_VITAMINS(25),
	m_uiBILLS_AC(10),

	m_uiSTARTING_MONEY(m_uiBILLS_RENT + m_uiBILLS_VITAMINS + (m_uiBILLS_AC / 2)),
	m_bCAN_GO_BANKRUPT(true),

	m_uiSTARTING_CORNSEEDS(5),
	m_uiSTARTING_EGGPLANTSEEDS(3),
	m_uiSTARTING_PUMPKINSEEDS(1),
	m_uiSTARTING_CORNHARVEST(0),
	m_uiSTARTING_EGGPLANTHARVEST(0),
	m_uiSTARTING_PUMPKINHARVEST(0),

	m_fDAY_LENGTH(90.0f),

	m_fDURATION_HOEDIRT(5.0f),
	m_fDURATION_PLANTCORN(2.0f),
	m_fDURATION_PLANTEGGPLANT(5.0f),
	m_fDURATION_PLANTPUMPKIN(10.0f),
	m_fDURATION_PLANTGERNAIUM(3.0f),
	m_fDURATION_PLANTMARIGOLD(6.0f),
	m_fDURATION_PLANTVINE(10.0f),
	m_fDURATION_HARVESTCORN(1.0f),
	m_fDURATION_HARVESTEGGPLANT(2.0f),
	m_fDURATION_HARVESTPUMPKIN(5.0f),

	m_fGROW_CORN(m_fDAY_LENGTH * 0.75f),
	m_fGROW_EGGPLANT(m_fDAY_LENGTH * 1.5f),
	m_fGROW_PUMPKIN(m_fDAY_LENGTH * 3.75f),
	m_fGROW_GERNAIUM(m_fDAY_LENGTH * 0.5f),
	m_fGROW_MARIGOLD(m_fDAY_LENGTH * 0.75f),
	m_fGROW_VINE(m_fDAY_LENGTH * 1.0f),

	m_uiENABLE_DEFENSE_DAY(3),

	m_uiNUMBITES_BEETLE(1),
	m_uiNUMBITES_ANT(2),
	m_uiNUMBITES_SPIDER(5),

	m_uiDAMAGE_BEETLE(5),
	m_uiDAMAGE_ANT(10),
	m_uiDAMAGE_SPIDER(25)
{
	Reset();
}

Values::~Values()
{
}

/*static*/ void Values::Init()
{
	HyAssert(sm_pInstance == nullptr, "");
	sm_pInstance = HY_NEW Values();
}

/*static*/ Values *Values::Get()
{
	HyAssert(sm_pInstance, "");
	return sm_pInstance;
}

void Values::Reset()
{
	m_iSavings = m_uiSTARTING_MONEY;
	m_fStamina = 1.0f;
	
	m_uiSeedsCorn = m_uiSTARTING_CORNSEEDS;
	m_uiSeedsEggplant = m_uiSTARTING_EGGPLANTSEEDS;
	m_uiSeedsPumpkin = m_uiSTARTING_PUMPKINSEEDS;
	m_uiSeedsGernaium = 0;
	m_uiSeedsMarigold = 0;
	m_uiSeedsVine = 0;
	
	m_uiHarvestCorn = m_uiSTARTING_CORNHARVEST;
	m_uiHarvestEggplant = m_uiSTARTING_EGGPLANTHARVEST;
	m_uiHarvestPumpkin = m_uiSTARTING_PUMPKINHARVEST;

	m_uiHarvestSoldAmt = 0;

	m_uiCurrentDay = 1;
	m_eEquipedItem = EQUIP_Hoe;
	m_bVitaminStrength = true;
	m_bAirConditioning = true;

	m_uiDamageCost = 0;
}

void Values::Sync()
{
	static_cast<HarvestBoom &>(Hy_App()).GetGame()->Sync();
}
