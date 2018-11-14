#include "pch.h"

Values *Values::sm_pInstance = nullptr;

Values::Values() :	m_uiSTARTING_MONEY(50),
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
					m_eEquipedItem(EQUIP_Hoe)
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
