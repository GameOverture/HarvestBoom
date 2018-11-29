#ifndef __XACT_PROJECT_HARVESTBOOM__
#define __XACT_PROJECT_HARVESTBOOM__

typedef enum
{
    XACT_VARIABLE_NUMCUEINSTANCES = 0,
    XACT_VARIABLE_ATTACKTIME = 1,
    XACT_VARIABLE_RELEASETIME = 2,
    XACT_VARIABLE_ORIENTATIONANGLE = 3,
    XACT_VARIABLE_DOPPLERPITCHSCALAR = 4,
    XACT_VARIABLE_SPEEDOFSOUND = 5,
    XACT_VARIABLE_DISTANCE = 6,
} XACT_VARIABLE;

#define XACT_VARIABLE_COUNT 7

typedef enum
{
    XACT_WAVEBANK_BASEGAME_ROOSTER_CROWING = 0,
    XACT_WAVEBANK_BASEGAME_USEHOE_3 = 1,
    XACT_WAVEBANK_BASEGAME_BUYSTUFF = 2,
    XACT_WAVEBANK_BASEGAME_MENU_CURSOR = 3,
    XACT_WAVEBANK_BASEGAME_USEHOE_1 = 4,
    XACT_WAVEBANK_BASEGAME_USEHOE_2 = 5,
    XACT_WAVEBANK_BASEGAME_DAY_ATTACK_90SEC = 6,
    XACT_WAVEBANK_BASEGAME_FARM_ATTACK = 7,
    XACT_WAVEBANK_BASEGAME_FARM_DAYTIME_16BIT = 8,
    XACT_WAVEBANK_BASEGAME_FARM_NIGHT_16BIT = 9,
    XACT_WAVEBANK_BASEGAME_FARM_WIN = 10,
    XACT_WAVEBANK_BASEGAME_DAY_90SEC = 11,
    XACT_WAVEBANK_BASEGAME_FOOTSTEP_2 = 12,
    XACT_WAVEBANK_BASEGAME_FOOTSTEP_3 = 13,
    XACT_WAVEBANK_BASEGAME_FOOTSTEP_1 = 14,
    XACT_WAVEBANK_BASEGAME_NIGHT_TRANSITION = 15,
    XACT_WAVEBANK_BASEGAME_DOOR_CLOSE = 16,
    XACT_WAVEBANK_BASEGAME_DOOR_OPEN = 17,
    XACT_WAVEBANK_BASEGAME_SMALLBUG_CRY_SHORT = 18,
    XACT_WAVEBANK_BASEGAME_BIGBUG_CRY = 19,
    XACT_WAVEBANK_BASEGAME_EAT = 20,
    XACT_WAVEBANK_BASEGAME_SCRIBBLE_SHORT = 21,
    XACT_WAVEBANK_BASEGAME_SRCIBBLE_LONG = 22,
} XACT_WAVEBANK_BASEGAME;

#define XACT_WAVEBANK_BASEGAME_ENTRY_COUNT 23

typedef enum
{
    XACT_CUE_BASEGAME_ROOSTER_CROWING = 0,
    XACT_CUE_BASEGAME_USEHOE_3 = 1,
    XACT_CUE_BASEGAME_BUYSTUFF = 2,
    XACT_CUE_BASEGAME_MENU_CURSOR = 3,
    XACT_CUE_BASEGAME_DAY_90SEC = 4,
    XACT_CUE_BASEGAME_DAY_ATTACK_90SEC = 5,
    XACT_CUE_BASEGAME_FARM_ATTACK = 6,
    XACT_CUE_BASEGAME_FARM_DAYTIME_16BIT = 7,
    XACT_CUE_BASEGAME_FARM_NIGHT_16BIT = 8,
    XACT_CUE_BASEGAME_FARM_WIN = 9,
    XACT_CUE_BASEGAME_NIGHT_TRANSITION = 10,
    XACT_CUE_BASEGAME_DOOR_CLOSE = 11,
    XACT_CUE_BASEGAME_DOOR_OPEN = 12,
    XACT_CUE_BASEGAME_SMALLBUG_CRY_SHORT = 13,
    XACT_CUE_BASEGAME_BIGBUG_CRY = 14,
    XACT_CUE_BASEGAME_EAT = 15,
    XACT_CUE_BASEGAME_SRCIBBLE_LONG = 16,
    XACT_CUE_BASEGAME_SCRIBBLE_SHORT = 17,
    XACT_CUE_BASEGAME_USEHOE_1 = 18,
    XACT_CUE_BASEGAME_FOOTSTEP_1 = 19,
} XACT_CUE_BASEGAME;

#define XACT_CUE_BASEGAME_ENTRY_COUNT 20

#endif // __XACT_PROJECT_HARVESTBOOM__
