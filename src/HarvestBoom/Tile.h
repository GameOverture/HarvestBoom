#pragma once

#include "pch.h"

class IPlant;

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
	HySprite2d *		m_pTexture;

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
			m_ProgressBarFill.SetTint(1.0f, 0.4f, 0.5f);
			m_ProgressBarFill.SetDisplayOrder(DISPLAYORDER_ProgressBar+1);
			m_ProgressBarFill.pos.Offset(1.0f, 1.0f);
			m_ProgressBarFill.scale.Set(0.0f, 1.0f);
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

	IPlant *			m_pPlant;

public:
	Tile(HyEntity2d *pParent);
	virtual ~Tile();

	TileType GetTileType() const;

	void SetNeighbors(Tile *pNorth, Tile *pEast, Tile *pSouth, Tile *pWest, Tile *pNorthEast, Tile *pSouthEast, Tile *pSouthWest, Tile *pNorthWest);
	void SetType(TileType eType);

	void SetTileState();
	HyShape2d &GetCollision();

	bool IncrementProgress();
	bool IsProgressComplete();
};

