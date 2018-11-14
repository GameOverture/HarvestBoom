#pragma once
#include "Harmony/HyEngine.h"
#include "Audio/LtGAudioManager.h"
#include "Audio/LtGAudioCues.h"

#include "Values.h"

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

enum PlantState
{
	PLANTSTATE_Sprout = 0,
	PLANTSTATE_Growing,
	PLANTSTATE_Harvest
};

enum ButtonState
{
	BTNSTATE_Pressable = 0,
	BTNSTATE_Down,
	BTNSTATE_Disabled,
	BTNSTATE_Selected
};

#define DISPLAYORDER_Title			999999999
#define DISPLAYORDER_Panel			99999999
#define DISPLAYORDER_UI				9999999
#define DISPLAYORDER_DayNight		9999998
#define DISPLAYORDER_DebugCollision	9999997
#define DISPLAYORDER_DebugGrid		999999
#define DISPLAYORDER_ProgressBar	99999

#define DISPLAYORDER_Player		1

#define DISPLAYORDER_PerRow		10

struct LoadPath
{
	const char *	szPrefix;
	const char *	szName;

	LoadPath() :	szPrefix(nullptr),
					szName(nullptr)
	{ }

	bool IsUsed() const {
		return szName != nullptr;
	}

	void Set(const char *szPre, const char *szNam) {
		szPrefix = szPre;
		szName = szNam;
	}
};

struct InfoPanelInit
{
	// HySprite2d
	LoadPath		panel_LoadPath;
	glm::ivec2		panel_Pos;

	// HyText2d
	LoadPath		text_LoadPath;
	glm::ivec2		text_LocalOffSet;
	glm::ivec2		text_ScaleBox;

	InfoPanelInit()
	{ }

	InfoPanelInit(const char *szPanelPrefix,
				  const char *szPanelName,
				  const char *szTextPrefix,
				  const char *szTextName,
				  int32 iPanelPosX,
				  int32 iPanelPosY,
				  int32 iTextOffsetX,
				  int32 iTextOffsetY,
				  int32 iTextDimensionsX,
				  int32 iTextDimensionsY)
	{
		panel_LoadPath.Set(szPanelPrefix, szPanelName);
		text_LoadPath.Set(szTextPrefix, szTextName);
		HySetVec(panel_Pos, iPanelPosX, iPanelPosY);
		HySetVec(text_LocalOffSet, iTextOffsetX, iTextOffsetY);
		HySetVec(text_ScaleBox, iTextDimensionsX, iTextDimensionsY);
	}
};
