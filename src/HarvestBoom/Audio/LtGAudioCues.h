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
} XACT_WAVEBANK_BASEGAME;

#define XACT_WAVEBANK_BASEGAME_ENTRY_COUNT 16

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
    XACT_CUE_BASEGAME_USEHOE_1 = 11,
    XACT_CUE_BASEGAME_FOOTSTEP_1 = 12,
} XACT_CUE_BASEGAME;

#define XACT_CUE_BASEGAME_ENTRY_COUNT 13

#endif // __XACT_PROJECT_HARVESTBOOM__
