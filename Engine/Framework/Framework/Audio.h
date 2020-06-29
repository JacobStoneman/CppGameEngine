#pragma once
#include "Subsystem.h"
#include "Event.h"
#include "Engine.h"

#include <sdl/SDL.h>
#include <sdl/SDL_mixer.h>

class Audio :
	public Subsystem
{
private:
	static void(*EventReaction[0])(std::vector<arg>);
public:
	Audio();
	~Audio();
	static void Audio::InitSystem();
	static void Audio::StartSystem();
	static void Audio::MainLoop();
	static void Update();
};

