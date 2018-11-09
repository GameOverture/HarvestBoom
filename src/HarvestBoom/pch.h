#pragma once
#include "Harmony/HyEngine.h"
#include "Audio/LtGAudioManager.h"
#include "Audio/LtGAudioCues.h"

#define TILE_SIZE 42.0f

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

#define DISPLAYORDER_UI			99999
#define DISPLAYORDER_DayNight	99998
#define DISPLAYORDER_DebugGrid	9999
#define DISPLAYORDER_Object		4

#define DISPLAYORDER_Structure	3
#define DISPLAYORDER_Impassable	2
#define DISPLAYORDER_Asphalt	1
#define DISPLAYORDER_Dirt		0
