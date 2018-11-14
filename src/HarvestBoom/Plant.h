#pragma once

enum PlantType
{
	PLANTTYPE_Corn = 0,
	PLANTTYPE_Eggplant,
	PLANTTYPE_Pumpkin,
	PLANTTYPE_Gernaium,
	PLANTTYPE_Marigold,
	PLANTTYPE_Vine
};

class Plant : public HySprite2d
{
protected:
	const PlantType		m_ePLANT_TYPE;
	bool				m_bIsPlanted;

public:
	Plant(PlantType ePlantType, const char *szPrefix, const char *szName, HyEntity2d *pParent);
	virtual ~Plant();

	PlantType GetPlantType();

	void SetAsPlanted();
	bool IsPlanted();

	bool IsFullyGrown();
};

