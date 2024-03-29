#include "pch.h"
#include "Tile.h"
#include "Plant.h"
#include "Bug.h"
#include "HarvestBoom.h"

extern float Hy_UpdateStep();

Tile::Tile(HyEntity2d *pParent) :	HyEntity2d(pParent),
									m_eTileType(Unknown),
									m_Ground(this),
									m_Grass("Tiles", "Grass", this),
									m_Dirt("Tiles", "Dirt", this),
									m_TilledOverlay("Tiles", "Dirt", this),
									m_House("Game", "House", this),
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
	m_Ground.SetAsBox(TILE_SIZE, TILE_SIZE);
	m_ProgressBar.SetVisible(false);
	m_ProgressBar.pos.Set(TILE_SIZE * 0.5f + -25.0f, 0.0f);

	m_SelectedRect.SetAsBox(TILE_SIZE, TILE_SIZE);
	m_SelectedRect.topColor.Set(1.0f, 0.0f, 0.0);
	m_SelectedRect.SetWireframe(true);
	m_SelectedRect.SetVisible(false);
	//m_SelectedRect.SetDisplayOrder(DISPLAYORDER_SelectedRect);
}

Tile::~Tile()
{
	//delete m_pPlant; TODO: leaking this for now. Pumpkins will cause a crash
}

glm::ivec2 Tile::GetPos()
{
	glm::ivec2 ptPos(pos.X() / TILE_SIZE, pos.Y() / TILE_SIZE);
	if(pos.X() < 0.0f)
		ptPos.x -= 1;
	if(pos.Y() < 0.0f)
		ptPos.y -= 1;

	return ptPos;
}

TileType Tile::GetTileType() const
{
	return m_eTileType;
}

Plant *Tile::GetPlant()
{
	return m_pPlant;
}

void Tile::Reset()
{
	m_SelectedRect.SetVisible(false);
	m_ProgressBar.SetVisible(false);

	if(m_pPlant)
	{
		m_pPlant->SetTag(0);
		if(m_pPlant->rot.Get() != 0.0f && m_pPlant->rot.IsAnimating() == false)
			m_pPlant->rot.Tween(0.0f, 0.75f, HyTween::QuadInOut);
	}
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
	if(m_eTileType == eType)
		return;

	m_Grass.SetDisplayOrder(DISPLAYORDER_Ground);
	m_Dirt.SetDisplayOrder(DISPLAYORDER_Ground);
	
	m_eTileType = eType;
	switch(m_eTileType)
	{
	case Grass:
		m_Dirt.SetVisible(false);
		m_TilledOverlay.SetVisible(false);
		
		break;

	case House:
		m_Ground.topColor.Set(0.623529f, 0.623529f, 0.372549f);
		m_Ground.SetVisible(true);
		break;

	case HouseDoor:
		m_Ground.topColor.Set(0.184314f, 0.309804f, 0.309804f);
		m_Ground.SetVisible(true);
		break;

	case Dirt:
		m_Grass.SetVisible(false);
		m_Dirt.SetVisible(true);
		m_TilledOverlay.SetVisible(true);
		m_TilledOverlay.AnimSetState(1);
		m_TilledOverlay.alpha.Set(0.0f);
		m_Ground.SetVisible(false);
		break;

	case Impassable:
		m_Ground.topColor.Set(0.6f, 0.8f, 0.196078f);
		break;

	default:
		break;
	}

	m_Ground.SetVisible(false);

	m_House.SetVisible(false);
}

void Tile::SetTileState()
{
	switch(m_eTileType)
	{
	case Grass:
		if(m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Dirt)
			m_Grass.AnimSetState(GRASS_South);
		if(m_pNeighborEast && m_pNeighborEast->GetTileType() == Dirt)
			m_Grass.AnimSetState(GRASS_West);
		if(m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Dirt)
			m_Grass.AnimSetState(GRASS_North);
		if(m_pNeighborWest && m_pNeighborWest->GetTileType() == Dirt)
			m_Grass.AnimSetState(GRASS_East);

		if(m_pNeighborNorthEast && m_pNeighborNorthEast->GetTileType() == Dirt &&
		   (m_pNeighborNorth == nullptr || m_pNeighborNorth->GetTileType() == Grass) &&
		   (m_pNeighborEast == nullptr || m_pNeighborEast->GetTileType() == Grass))
		{
			m_Grass.AnimSetState(GRASS_SouthWest);
		}

		if(m_pNeighborSouthEast && m_pNeighborSouthEast->GetTileType() == Dirt &&
		   (m_pNeighborSouth == nullptr || m_pNeighborSouth->GetTileType() == Grass) &&
		   (m_pNeighborEast == nullptr || m_pNeighborEast->GetTileType() == Grass))
		{
			m_Grass.AnimSetState(GRASS_NorthWest);
		}

		if(m_pNeighborSouthWest && m_pNeighborSouthWest->GetTileType() == Dirt &&
		   (m_pNeighborSouth == nullptr || m_pNeighborSouth->GetTileType() == Grass) &&
		   (m_pNeighborWest == nullptr || m_pNeighborWest->GetTileType() == Grass))
		{
			m_Grass.AnimSetState(GRASS_NorthEast);
		}

		if(m_pNeighborNorthWest && m_pNeighborNorthWest->GetTileType() == Dirt &&
		   (m_pNeighborNorth == nullptr || m_pNeighborNorth->GetTileType() == Grass) &&
		   (m_pNeighborWest == nullptr || m_pNeighborWest->GetTileType() == Grass))
		{
			m_Grass.AnimSetState(GRASS_SouthEast);
		}

		if((m_pNeighborNorth == nullptr || m_pNeighborNorth->GetTileType() == Grass) &&
		   (m_pNeighborNorthEast == nullptr || m_pNeighborNorthEast->GetTileType() == Grass) &&
		   (m_pNeighborEast == nullptr || m_pNeighborEast->GetTileType() == Grass) &&
		   m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Dirt &&
		   m_pNeighborWest && m_pNeighborWest->GetTileType() == Dirt)
		{
			m_Grass.AnimSetState(GRASS_InnerCorner_NE);
		}
		
		if((m_pNeighborNorth == nullptr || m_pNeighborNorth->GetTileType() == Grass) &&
		   (m_pNeighborNorthWest == nullptr || m_pNeighborNorthWest->GetTileType() == Grass) &&
		   (m_pNeighborWest == nullptr || m_pNeighborWest->GetTileType() == Grass) &&
		   m_pNeighborSouth && m_pNeighborSouth->GetTileType() == Dirt &&
		   m_pNeighborEast && m_pNeighborEast->GetTileType() == Dirt)
		{
			m_Grass.AnimSetState(GRASS_InnerCorner_NW);
		}
		
		if((m_pNeighborSouth == nullptr || m_pNeighborSouth->GetTileType() == Grass) &&
		   (m_pNeighborSouthEast == nullptr || m_pNeighborSouthEast->GetTileType() == Grass) &&
		   (m_pNeighborEast == nullptr || m_pNeighborEast->GetTileType() == Grass) &&
		   m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Dirt &&
		   m_pNeighborWest && m_pNeighborWest->GetTileType() == Dirt)
		{
			m_Grass.AnimSetState(GRASS_InnerCorner_SE);
		}
		
		if((m_pNeighborSouth == nullptr || m_pNeighborSouth->GetTileType() == Grass) &&
		   (m_pNeighborSouthWest == nullptr || m_pNeighborSouthWest->GetTileType() == Grass) &&
		   (m_pNeighborWest == nullptr || m_pNeighborWest->GetTileType() == Grass) &&
		   m_pNeighborNorth && m_pNeighborNorth->GetTileType() == Dirt &&
		   m_pNeighborEast && m_pNeighborEast->GetTileType() == Dirt)
		{
			m_Grass.AnimSetState(GRASS_InnerCorner_SW);
		}

		break;

	case House:
		if(m_pNeighborNorth->GetTileType() == House &&
		   m_pNeighborEast->GetTileType() == House &&
		   m_pNeighborWest->GetTileType() != House && m_pNeighborWest->GetTileType() != HouseDoor &&
		   m_pNeighborSouth->GetTileType() != House)
		{
			m_House.SetVisible(true);
		}
		else
			m_House.SetVisible(false);
		break;

	default:
		break;
	}
}

const HyShape2d &Tile::GetCollision()
{
	return m_Ground.GetLocalBoundingVolume();
}

void Tile::SetAsSelected()
{
	switch(Values::Get()->m_eEquipedItem)
	{
	case EQUIP_Hoe:
		if(m_bIsTilled == false)
			m_SelectedRect.SetVisible(true);
		break;
	case EQUIP_Harvest:
		if(m_pPlant && m_pPlant->IsFullyGrown())
			m_SelectedRect.SetVisible(true);
		break;
	case EQUIP_Corn:
		if(IsPlantable(PLANTTYPE_Corn))
			m_SelectedRect.SetVisible(true);
		break;
	case EQUIP_Eggplant:
		if(IsPlantable(PLANTTYPE_Eggplant))
			m_SelectedRect.SetVisible(true);
		break;
	case EQUIP_Pumpkin: {
		std::vector<Tile *> validTileList;
		if(IsPlantable(PLANTTYPE_Pumpkin, &validTileList))
		{
			for(uint32 i = 0; i < static_cast<uint32>(validTileList.size()); ++i)
				validTileList[i]->m_SelectedRect.SetVisible(true);
		}
		} break;
	case EQUIP_Gernaium:
		if(IsPlantable(PLANTTYPE_Gernaium))
			m_SelectedRect.SetVisible(true);
		break;
	case EQUIP_Marigold:
		if(IsPlantable(PLANTTYPE_Marigold))
			m_SelectedRect.SetVisible(true);
		break;
	case EQUIP_Vine:
		if(IsPlantable(PLANTTYPE_Vine))
			m_SelectedRect.SetVisible(true);
		break;

	default:
		break;
	}

	if(m_ProgressBar.GetPercent() != 0.0f && m_ProgressBar.GetPercent() != 1.0f)
		m_ProgressBar.SetVisible(true);
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
			m_TilledOverlay.alpha.Set(m_ProgressBar.GetPercent());

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
				break;
			case PLANTTYPE_Eggplant:
				fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_HARVESTEGGPLANT;
				fElapsedTime += Hy_UpdateStep();
				m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_HARVESTEGGPLANT);
				break;
			case PLANTTYPE_Pumpkin:
				// Must be bottom left corner of Pumpkin
				if((m_pNeighborNorth->m_pPlant && m_pNeighborNorth->m_pPlant == m_pPlant &&
				   m_pNeighborNorthEast->m_pPlant && m_pNeighborNorthEast->m_pPlant == m_pPlant &&
				   m_pNeighborEast->m_pPlant && m_pNeighborEast->m_pPlant == m_pPlant) == false)
				{
					return false;
				}

				fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_HARVESTPUMPKIN;
				fElapsedTime += Hy_UpdateStep();
				m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_HARVESTPUMPKIN);
				break;

			default:
				break;
			}

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				switch(m_pPlant->GetPlantType())
				{
				case PLANTTYPE_Corn:		Values::Get()->m_uiHarvestCorn++; break;
				case PLANTTYPE_Eggplant:	Values::Get()->m_uiHarvestEggplant++; break;
				case PLANTTYPE_Pumpkin:		Values::Get()->m_uiHarvestPumpkin++; break;

				default:
					break;
				}

				m_ProgressBar.SetPercent(0.0f);
				m_ProgressBar.SetColor_Growing();

				m_pPlant->AnimSetState(PLANTSTATE_Sprout);
			}
			return true;
		}
		break;

	case EQUIP_Corn:
		if(IsPlantable(PLANTTYPE_Corn))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsCorn == 0)
					break;

				Values::Get()->m_uiSeedsCorn--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Corn, "Plant", "Corn", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->rot_pivot.Set(static_cast<const HySprite2dData *>(m_pPlant->AcquireData())->GetFrame(0, 0).vOFFSET);
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
		if(IsPlantable(PLANTTYPE_Eggplant))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsEggplant == 0)
					break;

				Values::Get()->m_uiSeedsEggplant--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Eggplant, "Plant", "Eggplant", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->rot_pivot.Set(static_cast<const HySprite2dData *>(m_pPlant->AcquireData())->GetFrame(0, 0).vOFFSET);
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

	case EQUIP_Pumpkin: {
		std::vector<Tile *> validTileList;
		if(IsPlantable(PLANTTYPE_Pumpkin, &validTileList))
		{
			if(validTileList[0]->m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsPumpkin == 0)
					break;

				Values::Get()->m_uiSeedsPumpkin--;

				for(uint32 i = 0; i < static_cast<uint32>(validTileList.size()); ++i)
				{
					if(i == 0)
					{
						validTileList[i]->m_pPlant = HY_NEW Plant(PLANTTYPE_Pumpkin, "Plant", "Pumpkin", this);
						validTileList[i]->m_pPlant->alpha.Set(0.0f);
						validTileList[i]->m_pPlant->rot_pivot.Set(static_cast<const HySprite2dData *>(m_pPlant->AcquireData())->GetFrame(0, 0).vOFFSET);
						validTileList[i]->m_pPlant->Load();

						validTileList[i]->m_TilledOverlay.scale.Set(2.0f, 2.0f);
						validTileList[i]->m_TilledOverlay.SetDisplayOrder(validTileList[i]->m_pNeighborNorth->m_TilledOverlay.GetDisplayOrder());
						//validTileList[i]->m_Dirt.SetDisplayOrder(validTileList[i]->m_pNeighborNorth->m_Dirt.GetDisplayOrder());
						validTileList[i]->m_SelectedRect.scale.Set(2.0f, 2.0f);
					}
					else
					{
						validTileList[i]->m_pPlant = validTileList[0]->m_pPlant;
						validTileList[i]->m_TilledOverlay.SetVisible(false);
						//validTileList[i]->m_Dirt.SetDisplayOrder(validTileList[0]->m_Dirt.GetDisplayOrder());
						validTileList[i]->m_SelectedRect.alpha.Set(0.0f);
					}
				}

				m_ProgressBar.SetColor_Planting();
				m_ProgressBar.SetPercent(0.0f);
			}

			float fElapsedTime = m_ProgressBar.GetPercent() * Values::Get()->m_fDURATION_PLANTPUMPKIN;
			fElapsedTime += Hy_UpdateStep();
			m_ProgressBar.SetPercent(fElapsedTime / Values::Get()->m_fDURATION_PLANTPUMPKIN);
			validTileList[0]->m_pPlant->alpha.Set(m_ProgressBar.GetPercent());

			if(m_ProgressBar.GetPercent() == 1.0f)
			{
				validTileList[0]->m_pPlant->SetAsPlanted();
				m_ProgressBar.SetColor_Growing();
				m_ProgressBar.SetPercent(0.0f);
			}
			return true;
		}
		} break;

	case EQUIP_Gernaium:
		if(IsPlantable(PLANTTYPE_Gernaium))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsGernaium == 0)
					break;

				Values::Get()->m_uiSeedsGernaium--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Gernaium, "Plant", "Gernaium", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->rot_pivot.Set(static_cast<const HySprite2dData *>(m_pPlant->AcquireData())->GetFrame(0, 0).vOFFSET);
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
		if(IsPlantable(PLANTTYPE_Marigold))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsMarigold == 0)
					break;

				Values::Get()->m_uiSeedsMarigold--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Marigold, "Plant", "Marigold", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->rot_pivot.Set(static_cast<const HySprite2dData *>(m_pPlant->AcquireData())->GetFrame(0, 0).vOFFSET);
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
		if(IsPlantable(PLANTTYPE_Vine))
		{
			if(m_pPlant == nullptr)
			{
				if(Values::Get()->m_uiSeedsVine == 0)
					break;

				Values::Get()->m_uiSeedsVine--;

				m_pPlant = HY_NEW Plant(PLANTTYPE_Vine, "Plant", "Vine", this);
				m_pPlant->alpha.Set(0.0f);
				m_pPlant->rot_pivot.Set(static_cast<const HySprite2dData *>(m_pPlant->AcquireData())->GetFrame(0, 0).vOFFSET);
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

	default:
		break;
	}

	return false;
}

bool Tile::IncrementGrowing()
{
	if(m_pPlant == nullptr || m_pPlant->IsPlanted() == false || m_pPlant->IsFullyGrown() || m_pPlant->GetTag() != 0)
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
	m_ProgressBar.SetVisible(false);

	if(m_ProgressBar.GetPercent() >= 0.5f)
		m_pPlant->AnimSetState(PLANTSTATE_Growing);

	if(m_ProgressBar.GetPercent() == 1.0f)
	{
		m_ProgressBar.SetPercent(0.0f);
		m_ProgressBar.SetColor_Harvesting();
		m_pPlant->AnimSetState(PLANTSTATE_Harvest);	// Indicates fully grown
	}

	m_pPlant->SetTag(1);	// Indicates it has updated this frame

	return true;
}

void Tile::DamagePlant(Bug &bugRef)
{
	if(m_pPlant == nullptr)
		return;

	switch(m_pPlant->GetPlantType())
	{
	case PLANTTYPE_Corn:
	case PLANTTYPE_Eggplant:
	case PLANTTYPE_Pumpkin: {
		switch(bugRef.GetBugType())
		{
		case BUGTYPE_Beetle:	bugRef.OffsetStomach(1.0f / Values::Get()->m_uiNUMBITES_BEETLE);	break;
		case BUGTYPE_Ant:		bugRef.OffsetStomach(1.0f / Values::Get()->m_uiNUMBITES_ANT);		break;
		case BUGTYPE_Spider:	bugRef.OffsetStomach(1.0f / Values::Get()->m_uiNUMBITES_SPIDER);	break;
		}

		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_EAT);
		
		bool bDeletePlant = false;
		if(m_pPlant->IsFullyGrown())
		{
			m_ProgressBar.SetColor_Growing();
			m_ProgressBar.SetPercent(0.5f);
			m_pPlant->AnimSetState(PLANTSTATE_Growing);
		}
		else if(m_pPlant->IsPlanted())
		{
			if(m_ProgressBar.GetPercent() >= 0.5f)
			{
				m_ProgressBar.SetPercent(0.1f);
				m_pPlant->AnimSetState(PLANTSTATE_Sprout);
			}
			else
				bDeletePlant = true;
		}
		else
			bDeletePlant = true;

		if(bDeletePlant)
		{
			if(m_pPlant->GetPlantType() == PLANTTYPE_Pumpkin)
			{
				m_TilledOverlay.SetVisible(true);
				m_TilledOverlay.scale.Set(1.0f, 1.0f);
				m_SelectedRect.scale.Set(1.0f, 1.0f);

				if(m_pNeighborNorth->GetPlant() == m_pPlant)
				{
					m_pNeighborNorth->m_pPlant = nullptr;
					m_pNeighborNorth->m_TilledOverlay.SetVisible(true);
					m_pNeighborNorth->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborNorth->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborEast->GetPlant() == m_pPlant)
				{
					m_pNeighborEast->m_pPlant = nullptr;
					m_pNeighborEast->m_TilledOverlay.SetVisible(true);
					m_pNeighborEast->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborEast->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborSouth->GetPlant() == m_pPlant)
				{
					m_pNeighborSouth->m_pPlant = nullptr;
					m_pNeighborSouth->m_TilledOverlay.SetVisible(true);
					m_pNeighborSouth->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborSouth->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborWest->GetPlant() == m_pPlant)
				{
					m_pNeighborWest->m_pPlant = nullptr;
					m_pNeighborWest->m_TilledOverlay.SetVisible(true);
					m_pNeighborWest->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborWest->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborNorthWest->GetPlant() == m_pPlant)
				{
					m_pNeighborNorthWest->m_pPlant = nullptr;
					m_pNeighborNorthWest->m_TilledOverlay.SetVisible(true);
					m_pNeighborNorthWest->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborNorthWest->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborNorthEast->GetPlant() == m_pPlant)
				{
					m_pNeighborNorthEast->m_pPlant = nullptr;
					m_pNeighborNorthEast->m_TilledOverlay.SetVisible(true);
					m_pNeighborNorthEast->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborNorthEast->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborSouthWest->GetPlant() == m_pPlant)
				{
					m_pNeighborSouthWest->m_pPlant = nullptr;
					m_pNeighborSouthWest->m_TilledOverlay.SetVisible(true);
					m_pNeighborSouthWest->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborSouthWest->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
				if(m_pNeighborSouthEast->GetPlant() == m_pPlant)
				{
					m_pNeighborSouthEast->m_pPlant = nullptr;
					m_pNeighborSouthEast->m_TilledOverlay.SetVisible(true);
					m_pNeighborSouthEast->m_TilledOverlay.scale.Set(1.0f, 1.0f);
					m_pNeighborSouthEast->m_SelectedRect.scale.Set(1.0f, 1.0f);
				}
			}

			m_ProgressBar.SetPercent(0.0f);
			delete m_pPlant;
			m_pPlant = nullptr;
		}

		break; }

	case PLANTTYPE_Gernaium:
	case PLANTTYPE_Marigold:
	case PLANTTYPE_Vine:
		switch(bugRef.GetBugType())
		{
		case BUGTYPE_Beetle:	bugRef.OffsetHealth(-0.5f);	break;
		case BUGTYPE_Ant:		bugRef.OffsetHealth(-0.5f);	break;
		case BUGTYPE_Spider:	bugRef.OffsetHealth(-0.25f);break;
		}

		HarvestBoom::GetSndBank()->Play(XACT_CUE_BASEGAME_USEHOE_3);

		bugRef.StopEating();
		break;
	}
}

bool Tile::IsPlantable(PlantType ePlantType, std::vector<Tile *> *pValidTiles /*= nullptr*/)
{
	switch(ePlantType)
	{
	case PLANTTYPE_Corn:
	case PLANTTYPE_Eggplant:
	case PLANTTYPE_Gernaium:
	case PLANTTYPE_Marigold:
		if(m_bIsTilled && (m_pPlant == nullptr || (m_pPlant->GetPlantType() == ePlantType && m_pPlant->IsPlanted() == false)))
		{
			if(pValidTiles)
				pValidTiles->push_back(this);
			return true;
		}
		break;

	case PLANTTYPE_Pumpkin:
		if(m_bIsTilled == false || m_pNeighborEast->m_bIsTilled == false || m_pNeighborNorth->m_bIsTilled == false || m_pNeighborNorthEast->m_bIsTilled == false)
			return false;

		if(m_pPlant == nullptr && m_pNeighborEast->m_pPlant == nullptr && m_pNeighborNorth->m_pPlant == nullptr && m_pNeighborNorthEast->m_pPlant == nullptr)
		{
			if(pValidTiles)
			{
				pValidTiles->push_back(this);
				pValidTiles->push_back(m_pNeighborNorth);
				pValidTiles->push_back(m_pNeighborNorthEast);
				pValidTiles->push_back(m_pNeighborEast);
			}
			return true;
		}

		if(m_pPlant != m_pNeighborEast->m_pPlant || m_pPlant != m_pNeighborNorth->m_pPlant || m_pPlant != m_pNeighborNorthEast->m_pPlant)
			return false;

		if(m_pPlant && m_pPlant->GetPlantType() == PLANTTYPE_Pumpkin && m_pPlant->IsPlanted() == false)
		{
			if(pValidTiles)
			{
				pValidTiles->push_back(this);
				pValidTiles->push_back(m_pNeighborNorth);
				pValidTiles->push_back(m_pNeighborNorthEast);
				pValidTiles->push_back(m_pNeighborEast);
			}
			return true;
		}
		break;

	case PLANTTYPE_Vine:
		break;
	}

	return false;
}
