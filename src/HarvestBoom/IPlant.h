#pragma once
#include "IActor.h"

enum PlantType
{
	PLANTTYPE_Corn = 0,
	PLANTTYPE_Eggplant,
	PLANTTYPE_Pumpkin,
	PLANTTYPE_Gernaium,
	PLANTTYPE_Marigold,
	PLANTTYPE_Vine
};

class IPlant : public IActor
{
protected:
	const PlantType		m_ePLANT_TYPE;
	HyPrimitive2d		m_Body;

public:
	IPlant(PlantType ePlantType, HyEntity2d *pParent);
	virtual ~IPlant();

	PlantType GetPlantType();

	bool IsFullyGrown();
};

