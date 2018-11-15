#include "pch.h"

Values *Values::sm_pInstance = nullptr;

Values::Values() :	m_fPLAYER_MAXVELOCITY(200.0f),	// pixels per second
					m_fPLAYER_ACCEL(300.0f),
					m_fPLAYER_DECEL(600.0f),
	
					m_fSTAMINA_RUN(0.02f),
					m_fSTAMINA_ACTION(0.04f),
					m_fSTAMINA_AC(0.01f),

					m_uiSTARTING_MONEY(50),
					m_uiSTARTING_CORNSEEDS(5),
					m_uiSTARTING_EGGPLANTSEEDS(5),
					m_uiSTARTING_PUMPKINSEEDS(2),

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
					m_uiBILLS_FOOD(25),
					m_uiBILLS_AC(10),

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

					m_iSavings(m_uiSTARTING_MONEY),
					m_uiSeedsCorn(m_uiSTARTING_CORNSEEDS),
					m_uiSeedsEggplant(m_uiSTARTING_EGGPLANTSEEDS),
					m_uiSeedsPumpkin(m_uiSTARTING_PUMPKINSEEDS),
					m_uiSeedsGernaium(0),
					m_uiSeedsMarigold(0),
					m_uiSeedsVine(0),
					m_uiHarvestCorn(0),
					m_uiHarvestEggplant(0),
					m_uiHarvestPumpkin(0),
					m_uiCurrentDay(1),
					m_eEquipedItem(EQUIP_Hoe),
					m_bAirConditioning(true)
{
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
