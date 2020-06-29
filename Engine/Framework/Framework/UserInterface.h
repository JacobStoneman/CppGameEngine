#pragma once
#include "Subsystem.h"
#include "Engine.h"
#include "Event.h"
#include "Interaction.h"
#include "KeyboardInput.h"

#include <Windows.h>

class UserInterface :
	public Subsystem
{
public:
	//Array of function pointers for each type of interaction
	static void(*InteractionArray[(int)Interaction::max])();
	UserInterface();
	~UserInterface();
	static void UserInterface::InitSystem();
	static void UserInterface::StartSystem();
	static void UserInterface::MainLoop();
};