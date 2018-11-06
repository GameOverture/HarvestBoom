#pragma once
#include "Harmony/HyEngine.h"

enum Controls
{
	ShowFPS = 0,
	MoveUp,
	MoveRight,
	MoveDown,
	MoveLeft,
	UseEquip
};

#define DISPLAYORDER_Object		4

#define DISPLAYORDER_Structure	3
#define DISPLAYORDER_Impassable	2
#define DISPLAYORDER_Asphalt	1
#define DISPLAYORDER_Dirt		0
