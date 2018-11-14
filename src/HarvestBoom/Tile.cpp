#include "pch.h"
#include "Tile.h"
#include "Plant.h"

Tile::Tile(HyEntity2d *pParent) :	HyEntity2d(pParent),
									m_eTileType(Unknown),
									m_Ground(this),
									m_pTexture(nullptr),
									m_pTilledOverlay(nullptr),
									m_SelectedRect(this),
									m_pNeighborNorth(nullptr),
									m_pNeighborEast(nullptr),
									m_pNeighborSouth(nullptr),
									m_pNeighborWest(nullptr),
									m_pNeighborNorthEast(nullptr),
									m_pNeighborSouthEast(nullptr),
									m_pNeighborSouthWest(nullptr),
									m_pNeighborNorthWest(nullptr),
									m_pPlant(nullptr),
									m_ProgressBar(this),
									m_bIsTilled(false)
{
	m_Ground.GetShape().SetAsBox(TILE_SIZE, TILE_SIZE);
	m_ProgressBar.SetEnabled(false);
	m_ProgressBar.pos.Set(TILE_SIZE * 0.5f + -25.0f, 0.0f);

	m_SelectedRect.GetShape().SetAsBox(TILE_SIZE, TILE_SIZE);
	m_SelectedRect.topColor.Set(1.0f, 0.0f, 0.0);
	m_SelectedRect.SetWireframe(true);
	m_SelectedRect.SetEnabled(false);
	m_SelectedRect.SetDisplayOrder(DISPLAYORDER_SelectedRect);
}

Tile::~Tile()
{
}

TileType Tile::GetTileType() const
{
	return m_eTileType;
}

void Tile::Cleanup()
{
	m_SelectedRect.SetEnabled(false);
	m_ProgressBar.SetEnabled(false);
}

void Tile::SetNeighbors(Tile *pNorth, Tile *pEast, Tile *pSouth, Tile *pWest, Tile *pNorthEast, Tile *pSouthEast, Tile *pSouthWest, Tile *pNorthWest)
{
	m_pNeighborNorth = pNorth;
	m_pNeighborEast = pEast;
	m_pNeighborSouth = pSouth;
	m_pNeighborWest = pWest;

	m_pNeighborNorthEast = pNorthEast;
	m_pNeighborSouthEast = pSouthEast;
	m_pNeighborSouthWest = pSouthWest;
	m_pNeighborNorthWest = pNorthWest;
}

void Tile::SetType(TileType eType)
{
	m_eTileType = eType;
	switch(m_eTileType)
	{
	case Grass:
		delete m_pTexture;
		m_pTexture = HY_NEW HySprite2d("Tiles", "Grass", this);
		m_Ground.SetEnabled(false);
		break;

	case House:
		m_Ground.topColor.Set(0.623529f, 0.623529f, 0.372549f);
		m_Ground.SetEnabled(true);
		break;

	case HouseDoor:
		m_Ground.topColor.Set(0.184314f, 0.309804f, 0.309804f);
		m_Ground.SetEnabled(true);
		break;

	case Dirt:
		delete m_pTexture;
		m_pTexture = HY_NEW HySprite2d("Tiles", "Dirt", this);
		m_pTilledOverlay = HY_NEW HySprite2d("Tiles", "Dirt", this);
		m_pTilledOverlay->AnimSetState(1);
		m_pTilledOverlay->alpha.Set(0.0f);
		m_Ground.SetEnabled(false);
		break;

	case Impassable:
		m_Ground.topColor.Set(0.6f, 0.8f, 0.196078f);
		break;
	}
}

void Tile::SetTileState()
{
	switch(m_eTileType)
	{
	case Grass:
		if(m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_South);
		if(m_pNeighborEast && m_pNeighborEast->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_West);
		if(m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_North);
		if(m_pNeighborWest && m_pNeighborWest->GetTileType() == Dirt)
			m_pTexture->AnimSetState(GRASS_East);

		if(m_pNeighborNorthEast && m_pNeighborNorthEast->GetTileType() == Dirt &&
		   m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Grass &&
		   m_pNeighborEast && m_pNeighborEast->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_SouthWest);
		}

		if(m_pNeighborSouthEast && m_pNeighborSouthEast->GetTileType() == Dirt &&
		   m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Grass &&
		   m_pNeighborEast && m_pNeighborEast->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_NorthWest);
		}

		if(m_pNeighborSouthWest && m_pNeighborSouthWest->GetTileType() == Dirt &&
		   m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Grass &&
		   m_pNeighborWest && m_pNeighborWest->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_NorthEast);
		}

		if(m_pNeighborNorthWest && m_pNeighborNorthWest->GetTileType() == Dirt &&
		   m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Grass &&
		   m_pNeighborWest && m_pNeighborWest->GetTileType() == Grass)
		{
			m_pTexture->AnimSetState(GRASS_SouthEast);
		}

		break;

	case House:
		if(m_pNeighborNorth->GetTileType() == House &&
		   m_pNeighborEast->GetTileType() == House &&
		   m_pNeighborWest->GetTileType() != House && m_pNeighborWest->GetTileType() != HouseDoor &&
		   m_pNeighborSouth->GetTileType() != House)
		{
			delete m_pTexture;
			m_pTexture = HY_NEW HySprite2d("Game", "House", this);
		}
		break;
	}
}

HyShape2d &Tile::GetCollision()
{
	return m_Ground.GetShape();
}

void Tile::SetAsSelected()
{
	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		if(m_bIsTilled == false)
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Harvest:
		if(m_pPlant && m_pPlant->IsFullyGrown())
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Corn:
		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Corn && m_pPlant->IsPlanted() == false)
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Eggplant:
		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Eggplant && m_pPlant->IsPlanted() == false)
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Pumpkin:
		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Pumpkin && m_pPlant->IsPlanted() == false)
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Gernaium:
		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Gernaium && m_pPlant->IsPlanted() == false)
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Marigold:
		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Marigold && m_pPlant->IsPlanted() == false)
			m_SelectedRect.SetEnabled(true);
		break;
	case EQUIP_Vine:
		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Vine && m_pPlant->IsPlanted() == false)
			m_SelectedRect.SetEnabled(true);
		break;
	}

	if(m_ProgressBar.GetPercent() != 0.0f && m_ProgressBar.GetPercent() != 1.0f)
		m_ProgressBar.SetEnabled(true);
}

// Checks whether action is valid
bool Tile::IncrementProgress()
{
	HyAssert(m_eTileType == Dirt, "");

	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		if(m_bIsTilled == false)
		{
			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_HOEDIRT;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_HOEDIRT);
			m_pTilledOverlay->alpha.Set(m_ProgressBar.GetPercent());

			m_bIsTilled = m_ProgressBar.GetPercent() == 1.0f;
			return true;
		}
		break;

	case EQUIP_Harvest:
		if(m_pPlant && m_pPlant->IsFullyGrown())
		{
			float fElapsedTime = 0.0f;
			switch(m_pPlant->GetPlantType())
			{
			case PLANTTYPE_Corn:
				fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_HARVESTCORN;
				fElapsedTime += Hy_UpdateStep();
				m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_HARVESTCORN);
				return true;
			case PLANTTYPE_Eggplant:
				fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_HARVESTEGGPLANT;
				fElapsedTime += Hy_UpdateStep();
				m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_HARVESTEGGPLANT);
				return true;
			case PLANTTYPE_Pumpkin:
				fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_HARVESTPUMPKIN;
				fElapsedTime += Hy_UpdateStep();
				m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_HARVESTPUMPKIN);
				return true;
			}

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				switch(m_pPlant->GetPlantType())
				{
				case PLANTTYPE_Corn:		Values::Get()->m_uiHarvestCorn++; break;
				case PLANTTYPE_Eggplant:	Values::Get()->m_uiHarvestEggplant++; break;
				case PLANTTYPE_Pumpkin:		Values::Get()->m_uiHarvestPumpkin++; break;
				}

				m_ProgressBar.SetPercent(0.0f);
				m_ProgressBar.SetColor_Growing();

				m_pPlant->AnimSetState(PLANTSTATE_Sprout);
			}
		}
		break;

	case EQUIP_Corn:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == PLANTTYPE_Corn && m_pPlant->IsPlanted() == false)))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsCorn == 0)
					break;

				Values::Get()->m_uiSeedsCorn--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Corn, "Plant", "Corn", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->SetDisplayOrder(m_pTilledOverlay->GetDisplayOrder() + 1);
				m_pPlant->Load();

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTCORN;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTCORN);
			m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		} 
		break;

	case EQUIP_Eggplant:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == PLANTTYPE_Eggplant && m_pPlant->IsPlanted() == false)))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsEggplant == 0)
					break;

				Values::Get()->m_uiSeedsEggplant--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Eggplant, "Plant", "Eggplant", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->SetDisplayOrder(m_pTilledOverlay->GetDisplayOrder() + 1);
				m_pPlant->Load();

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTEGGPLANT;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTEGGPLANT);
			m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		}
		break;

	case EQUIP_Pumpkin:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == PLANTTYPE_Pumpkin && m_pPlant->IsPlanted() == false)))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsPumpkin == 0)
					break;

				Values::Get()->m_uiSeedsPumpkin--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Pumpkin, "Plant", "Pumpkin", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->SetDisplayOrder(m_pTilledOverlay->GetDisplayOrder() + 1);
				m_pPlant->Load();

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTPUMPKIN;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTPUMPKIN);
			m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		}
		break;

	case EQUIP_Gernaium:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == PLANTTYPE_Gernaium && m_pPlant->IsPlanted() == false)))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsGernaium == 0)
					break;

				Values::Get()->m_uiSeedsGernaium--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Gernaium, "Plant", "Gernaium", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->SetDisplayOrder(m_pTilledOverlay->GetDisplayOrder() + 1);
				m_pPlant->Load();

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTGERNAIUM;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTGERNAIUM);
			m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		}
		break;

	case EQUIP_Marigold:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == PLANTTYPE_Marigold && m_pPlant->IsPlanted() == false)))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsMarigold == 0)
					break;

				Values::Get()->m_uiSeedsMarigold--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Marigold, "Plant", "Marigold", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->SetDisplayOrder(m_pTilledOverlay->GetDisplayOrder() + 1);
				m_pPlant->Load();

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTMARIGOLD;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTMARIGOLD);
			m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		}
		break;

	case EQUIP_Vine:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == PLANTTYPE_Vine && m_pPlant->IsPlanted() == false)))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsVine == 0)
					break;

				Values::Get()->m_uiSeedsVine--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Vine, "Plant", "Vine", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->SetDisplayOrder(m_pTilledOverlay->GetDisplayOrder() + 1);
				m_pPlant->Load();

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTVINE;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTVINE);
			m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		}
		break;
	}

	return false;
}

bool Tile::IncrementGrowing()
{
	if(m_pPlant == nullptr || m_pPlant->IsPlanted() == false || m_pPlant->IsFullyGrown())
		return false;

	float fGrowTime = 0.0f;
	switch(m_pPlant->GetPlantType())
	{
	case PLANTTYPE_Corn:		fGrowTime = Values::Get()->m_fGROW_CORN;		break;
	case PLANTTYPE_Eggplant:	fGrowTime = Values::Get()->m_fGROW_EGGPLANT;	break;
	case PLANTTYPE_Pumpkin:		fGrowTime = Values::Get()->m_fGROW_PUMPKIN;		break;
	case PLANTTYPE_Gernaium:	fGrowTime = Values::Get()->m_fGROW_GERNAIUM;	break;
	case PLANTTYPE_Marigold:	fGrowTime = Values::Get()->m_fGROW_MARIGOLD;	break;
	case PLANTTYPE_Vine:		fGrowTime = Values::Get()->m_fGROW_VINE;		break;
	}
	float fElapsedTime = m_ProgressBar.GetPercent() * fGrowTime;
	fElapsedTime += Hy_UpdateStep();

	m_ProgressBar.SetPercent(fElapsedTime / fGrowTime);
	m_ProgressBar.SetEnabled(false);

	if(m_ProgressBar.GetPercent() >= 0.5f)
		m_pPlant->AnimSetState(PLANTSTATE_Growing);

	if(m_ProgressBar.GetPercent() == 1.0f)
	{
		m_ProgressBar.SetPercent(0.0f);
		m_ProgressBar.SetColor_Harvesting();
		m_pPlant->AnimSetState(PLANTSTATE_Harvest);	// Indicates fully grown
	}

	return true;
}
