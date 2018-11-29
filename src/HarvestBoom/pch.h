#pragma once
#include "Harmony/HyEngine.h"
#include "Audio/LtGAudioManager.h"
#include "Audio/LtGAudioCues.h"
#include "Values.h"

//#define DEV_QUICKMODE

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
	Dirt,
	Impassable
};

enum TitleScreenValue
{
	TITLE_Nothing = 0,
	TITLE_Play,
	TITLE_Quit
};

enum TitleScreenType
{
	TITLETYPE_Start = 0,
	TITLETYPE_GameOver
};

enum PlantState
{
	PLANTSTATE_Sprout = 0,
	PLANTSTATE_Growing,
	PLANTSTATE_Harvest
};

enum PlantType
{
	PLANTTYPE_Corn = 0,
	PLANTTYPE_Eggplant,
	PLANTTYPE_Pumpkin,
	PLANTTYPE_Gernaium,
	PLANTTYPE_Marigold,
	PLANTTYPE_Vine
};

enum BugType
{
	BUGTYPE_Beetle = 0,
	BUGTYPE_Ant,
	BUGTYPE_Spider
};

#define DISPLAYORDER_Splash				999999999
#define DISPLAYORDER_Title				99999999
#define DISPLAYORDER_Panel				9999999
#define DISPLAYORDER_UI					999999
#define DISPLAYORDER_DayNight			999998
#define DISPLAYORDER_DebugCollision		999997
#define DISPLAYORDER_DebugGrid			99999
#define DISPLAYORDER_ProgressBar		9999
#define DISPLAYORDER_SelectedRect		999

#define DISPLAYORDER_Player				1

#define DISPLAYORDER_TILE_Plant			10
#define DISPLAYORDER_TILE_ProgressBar	7
#define DISPLAYORDER_TILE_SelectRect	6
#define DISPLAYORDER_TILE_House			5
#define DISPLAYORDER_TILE_Tilled		4
#define DISPLAYORDER_TILE_Dirt			3
#define DISPLAYORDER_PerRow				20

#define DISPLAYORDER_Ground				10

#define PLAYER_STARTPOS 15, 10
