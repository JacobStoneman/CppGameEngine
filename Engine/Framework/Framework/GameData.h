#pragma once
#include "Subsystem.h"
#include "Event.h"
#include "Engine.h"

//The following code is compiled in C as this is what lua is written in
extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <LuaBridge/LuaBridge.h>

class GameData : public Subsystem
{
public:
	static void GameData::InitSystem();
	static void GameData::StartSystem();
};

