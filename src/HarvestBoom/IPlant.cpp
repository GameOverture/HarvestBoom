#include "pch.h"
#include "IPlant.h"


IPlant::IPlant(PlantType ePlantType, HyEntity2d *pParent) :	IActor(pParent),
															m_ePLANT_TYPE(ePlantType),
															m_Body(this)
{
	m_Body.GetShape().SetAsBox(TILE_SIZE, TILE_SIZE);
	m_Body.topColor.Set(0.0f, 1.0f, 0.0f);
}

IPlant::~IPlant()
{
}

PlantType IPlant::GetPlantType()
{
	return m_ePLANT_TYPE;
}

bool IPlant::IsFullyGrown()
{
	return false;
}
