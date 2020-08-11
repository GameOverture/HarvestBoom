#include "pch.h"
#include "HarvestBoom.h"

//--------------------------------------------------------------------------------------
// Entry point to Harvest Boom
//--------------------------------------------------------------------------------------
int main(int argc, char **argv)
{
	HarmonyInit initStruct("HarvestBoom.hyproj");

	HarvestBoom game(initStruct);
	return game.RunGame();
}
