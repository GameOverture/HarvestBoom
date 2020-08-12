cmake_minimum_required(VERSION 3.10)
project(HarvestBoom VERSION 1.0)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

option(HYBUILD_DebugEmscripten "Use a Debug build configuration when targeting web browsers" OFF)

add_subdirectory("C:/Soft/LG/SlotFramework/Engines/Harmony/Engine" "Engine")

set(HY_SRCFILES
	"src/BillsPanel.cpp"
	"src/BillsPanel.h"
	"src/Bug.cpp"
	"src/Bug.h"
	"src/BugAttack.cpp"
	"src/BugAttack.h"
	"src/BuyButton.cpp"
	"src/BuyButton.h"
	"src/CheckBox.cpp"
	"src/CheckBox.h"
	"src/ContinueButton.cpp"
	"src/ContinueButton.h"
	"src/DayNight.cpp"
	"src/DayNight.h"
	"src/DebugGrid.cpp"
	"src/DebugGrid.h"
	"src/EquipButton.cpp"
	"src/EquipButton.h"
	"src/FoodButton.cpp"
	"src/FoodButton.h"
	"src/FoodStuffs.cpp"
	"src/FoodStuffs.h"
	"src/Game.cpp"
	"src/Game.h"
	"src/HarvestBoom.cpp"
	"src/HarvestBoom.h"
	"src/HousePanel.cpp"
	"src/HousePanel.h"
	"src/IActor.cpp"
	"src/IActor.h"
	"src/IntroPanel.cpp"
	"src/IntroPanel.h"
	"src/main.cpp"
	"src/pch.h"
	"src/Plant.cpp"
	"src/Plant.h"
	"src/Player.cpp"
	"src/Player.h"
	"src/Stamina.cpp"
	"src/Stamina.h"
	"src/Tile.cpp"
	"src/Tile.h"
	"src/TitleScreen.cpp"
	"src/TitleScreen.h"
	"src/Values.cpp"
	"src/Values.h"
	"src/World.cpp"
	"src/World.h"
	"HarvestBoom.hyproj")

add_executable(HarvestBoom ${HY_SRCFILES})
set_target_properties(HarvestBoom PROPERTIES
	CXX_STANDARD 14
	CXX_STANDARD_REQUIRED YES
	CXX_EXTENSIONS NO)

target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/include")
target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/external/box2d/include")
target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/external/soil2/include")

if("${CMAKE_SYSTEM_NAME}" STREQUAL "Emscripten")
	message(STATUS "Building for ${CMAKE_SYSTEM_NAME} target system")
	
	set(EM_LINK_FLAGS "")
	list(APPEND EM_LINK_FLAGS "-s ALLOW_MEMORY_GROWTH=1")
	list(APPEND EM_LINK_FLAGS "-s MIN_WEBGL_VERSION=2")
	list(APPEND EM_LINK_FLAGS "-s MAX_WEBGL_VERSION=2")
	list(APPEND EM_LINK_FLAGS "-s USE_SDL=2")
	list(APPEND EM_LINK_FLAGS "--no-heap-copy")
	list(APPEND EM_LINK_FLAGS "--preload-file C:/Soft/Games/HarvestBoom/./data@./data")
	list(APPEND EM_LINK_FLAGS "--preload-file C:/Soft/Games/HarvestBoom/HarvestBoom.hyproj@HarvestBoom.hyproj")
	
	if(HYBUILD_SDL_NET)
		list(APPEND EM_LINK_FLAGS "-s USE_SDL_NET=2")
	endif()
	
	if(HYBUILD_DebugEmscripten)
		message(STATUS "Building for DEBUG")
		set(CMAKE_BUILD_TYPE Debug)
		target_compile_definitions(HyEngine PRIVATE DEBUG)
		target_compile_definitions(HarvestBoom PRIVATE DEBUG)
		set_target_properties(HarvestBoom PROPERTIES COMPILE_FLAGS_FLAGS "-fsanitize=undefined -g")
		
		list(APPEND EM_LINK_FLAGS "-g")
		list(APPEND EM_LINK_FLAGS "-s ASSERTIONS=1")
		list(APPEND EM_LINK_FLAGS "-s SAFE_HEAP=1")
		list(APPEND EM_LINK_FLAGS "-s STACK_OVERFLOW_CHECK=2")
		list(APPEND EM_LINK_FLAGS "-s LLD_REPORT_UNDEFINED")
	endif()
	
	string(REPLACE ";" " " EM_LINK_FLAGS "${EM_LINK_FLAGS}")
	message(STATUS "EM_LINK_FLAGS:" ${EM_LINK_FLAGS})
	
	set_target_properties(HarvestBoom PROPERTIES LINK_FLAGS ${EM_LINK_FLAGS})
	set(CMAKE_EXECUTABLE_SUFFIX ".html")
else()
	target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/external/glad/include")
	target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/external/glfw/include")
	target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/external/SDL2_mixer")
	if(HYBUILD_SDL_NET)
		target_include_directories(HarvestBoom PUBLIC "C:/Soft/LG/SlotFramework/Engines/Harmony/Engine/external/SDL2_net")
	endif()
	
	target_precompile_headers(HarvestBoom PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src/pch.h")
endif()

target_link_libraries(HarvestBoom PUBLIC HyEngine)

if(TARGET uninstall)
	set_target_properties(uninstall PROPERTIES FOLDER "Engine Libs")
endif()

if (MSVC)
	set_property(TARGET HarvestBoom PROPERTY VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}")
	set_property(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}" PROPERTY VS_STARTUP_PROJECT HarvestBoom)
endif()
