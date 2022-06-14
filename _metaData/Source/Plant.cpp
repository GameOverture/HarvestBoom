#include "pch.h"
#include "Plant.h"


Plant::Plant(PlantType ePlantType, const char *szPrefix, const char *szName, HyEntity2d *pParent) :	HySprite2d(szPrefix, szName, pParent),
																									m_ePLANT_TYPE(ePlantType),
																									m_bIsPlanted(false)
{
}

Plant::~Plant()
{
}

PlantType Plant::GetPlantType()
{
	return m_ePLANT_TYPE;
}

void Plant::SetAsPlanted()
{
	m_bIsPlanted = true;
}

bool Plant::IsPlanted()
{
	return m_bIsPlanted;
}

bool Plant::IsFullyGrown()
{
	return GetState() == PLANTSTATE_Harvest;
}
