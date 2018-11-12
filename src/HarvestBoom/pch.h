#pragma once
#include "Harmony/HyEngine.h"
#include "Audio/LtGAudioManager.h"
#include "Audio/LtGAudioCues.h"

#define TILE_SIZE 21.0f

enum Controls
{
	ToggleFPS = 0,
	ToggleGrid,
	MoveUp,
	MoveRight,
	MoveDown,
	MoveLeft,
	UseEquip
};

enum TileType
{
	Unknown = 0,
	Grass,
	House,
	HouseDoor,
	HouseWindow,
	Dirt,
	Impassable
};

enum TitleScreenValue
{
	TITLE_Nothing = 0,
	TITLE_Play,
	TITLE_Quit
};

enum PlantState
{
	PLANTSTATE_Sprout = 0,
	PLANTSTATE_Growing,
	PLANTSTATE_Harvest
};

#define DISPLAYORDER_Title			999999999
#define DISPLAYORDER_Panel			99999999
#define DISPLAYORDER_UI				9999999
#define DISPLAYORDER_DayNight		9999998
#define DISPLAYORDER_DebugCollision	9999997
#define DISPLAYORDER_DebugGrid		999999

#define DISPLAYORDER_Player		1

#define DISPLAYORDER_PerRow		10
