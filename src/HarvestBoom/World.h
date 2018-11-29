#pragma once
#include "pch.h"
#include "HousePanel.h"

#define WORLD_WIDTH 25
#define WORLD_HEIGHT 25

class Tile;
class Player;
class Stamina;
class HousePanel;

class World : public HyEntity2d
{
	Tile *				m_pTileGrid[WORLD_WIDTH][WORLD_HEIGHT];
	uint32				m_uiSetRowCurrentIndex;

	typedef std::pair<uint32, Tile *> PheromoneWaypoint;
	std::vector<PheromoneWaypoint>	m_PheromoneWaypointList;

	Tile *							m_pDoorTile;

	HyPrimitive2d	m_DebugCollidePt1;
	HyPrimitive2d	m_DebugCollidePt2;
	HyPrimitive2d	m_DebugCollideNormal;

public:
	World(HyEntity2d *pParent);
	virtual ~World();

	Tile *GetTile(uint32 uiX, uint32 uiY);
	Tile *FindTile(glm::vec2 ptWorldCoordinate);

	glm::vec2 GetDoorCenter();

	uint32 GetNumWaypoints();
	glm::ivec2 GetTileWaypoint(uint32 uiIndex);
	glm::vec2 GetPixelWaypoint(uint32 uiIndex);

	void SetupNewDay();

	void CleanupTiles();
	void UpdatePlayer(Player &playerRef, Stamina &staminaRef, HousePanel &housePanelRef);

private:
	void SetRow(std::string sRow);

	static bool PheromoneWaypointSortPredicate(const PheromoneWaypoint wayPt1, const PheromoneWaypoint wayPt2);
};
