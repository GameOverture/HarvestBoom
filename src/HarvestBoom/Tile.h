#pragma once

#include "pch.h"

class Plant;

class Tile : public HyEntity2d
{
	enum GrassAnimState
	{
		GRASS_Full = 0,
		GRASS_North,
		GRASS_East,
		GRASS_South,
		GRASS_West,
		GRASS_NorthWest,
		GRASS_NorthEast,
		GRASS_SouthEast,
		GRASS_SouthWest
	};

	TileType			m_eTileType;

	HyPrimitive2d		m_Ground;
	HySprite2d 			m_Grass;
	HySprite2d 			m_Dirt;
	HySprite2d 			m_TilledOverlay;
	HySprite2d			m_House;

	HyPrimitive2d		m_SelectedRect;

	Tile *				m_pNeighborNorth;
	Tile *				m_pNeighborEast;
	Tile *				m_pNeighborSouth;
	Tile *				m_pNeighborWest;
	Tile *				m_pNeighborNorthEast;
	Tile *				m_pNeighborSouthEast;
	Tile *				m_pNeighborSouthWest;
	Tile *				m_pNeighborNorthWest;
	
	class ProgressBar : public HyEntity2d
	{
		HyPrimitive2d		m_ProgressBarOutline;
		HyPrimitive2d		m_ProgressBarFill;

	public:
		ProgressBar(HyEntity2d *pParent) :	HyEntity2d(pParent),
											m_ProgressBarOutline(this),
											m_ProgressBarFill(this)
		{
			m_ProgressBarOutline.GetShape().SetAsBox(52.0f, 4.0f);
			m_ProgressBarOutline.SetTint(0.0f, 0.0f, 0.0f);
			m_ProgressBarOutline.SetDisplayOrder(DISPLAYORDER_ProgressBar);

			m_ProgressBarFill.GetShape().SetAsBox(50.0f, 2.0f);
			m_ProgressBarFill.SetDisplayOrder(DISPLAYORDER_ProgressBar+1);
			m_ProgressBarFill.pos.Offset(1.0f, 1.0f);
			m_ProgressBarFill.scale.Set(0.0f, 1.0f);
			
			SetColor_Tilling();
		}
		
		void SetColor_Tilling() {
			m_ProgressBarFill.SetTint(1.0f, 0.4f, 0.5f);
		}
		void SetColor_Planting() {
			m_ProgressBarFill.SetTint(170.0f / 255.0f, 216.0f / 255.0f, 143.0f / 255.0f);
		}
		void SetColor_Growing() {
			m_ProgressBarFill.SetTint(250.0f / 255.0f, 248.0f / 255.0f, 153.0f / 255.0f);
		}
		void SetColor_Harvesting() {
			m_ProgressBarFill.SetTint(230.0f / 255.0f, 140.0f / 255.0f, 86.0f / 255.0f);
		}

		float GetPercent() {
			return m_ProgressBarFill.scale.X();
		}

		void OffsetPercent(float fPercentOffset) {
			m_ProgressBarFill.scale.X(HyClamp(m_ProgressBarFill.scale.X() + fPercentOffset, 0.0f, 1.0f));
			SetEnabled(m_ProgressBarFill.scale.X() < 1.0f);
		}

		void SetPercent(float fPercent) {
			m_ProgressBarFill.scale.X(HyClamp(fPercent, 0.0f, 1.0f));
			SetEnabled(m_ProgressBarFill.scale.X() < 1.0f);
		}
	};
	ProgressBar			m_ProgressBar;
	bool				m_bIsTilled;

	Plant *			m_pPlant;

public:
	Tile(HyEntity2d *pParent);
	virtual ~Tile();

	TileType GetTileType() const;

	void Cleanup();

	void SetNeighbors(Tile *pNorth, Tile *pEast, Tile *pSouth, Tile *pWest, Tile *pNorthEast, Tile *pSouthEast, Tile *pSouthWest, Tile *pNorthWest);
	void SetType(TileType eType);

	void SetTileState();
	HyShape2d &GetCollision();

	void SetAsSelected();

	// Checks whether action is valid
	bool IncrementProgress();

	bool IncrementGrowing();

private:
	bool IsPlantable(PlantType ePlantType, std::vector<Tile *> *pValidTiles = nullptr);
};

