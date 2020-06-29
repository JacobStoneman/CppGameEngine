#pragma once
#include "Networking.h"
#include "Graphics.h"
#include "UserInterface.h"
#include "Audio.h"
#include "GameData.h"
#include "Event.h"
#include "EventTypeEnum.h"
#include "EntitySub.h"
#include "Physics.h"

#undef main

class Engine
{
public:

	static int pEntityNum;
	static int width;
	static int height;
	//Total amount of events for use by the subsystems to declare their event reaction arrays
	static const int EVENTCOUNT = (int)EventType::max;
	//The event queue which is looped through by each subsystem
	static std::vector<Event> eventQ;
	//vector of all game objects that exist in the scene
	static std::vector<EntityObject*> entities;
	Engine();
	~Engine();
	static void InitEngine(); 
	static void StartEngine(); 
	static void MainLoop();
	static void Update();
};

