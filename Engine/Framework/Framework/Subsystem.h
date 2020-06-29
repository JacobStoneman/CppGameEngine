#pragma once
#include <iostream>
#include <vector>
#include <chrono>

class Subsystem
{
public:
	//Parent class for all subsystems
	//Should print if a subsytem is missing a core function
	virtual void InitSystem() { std::cout << "a subsystem has no init function" << std::endl; }; //This should be for initialising values exclusively for the subsystem
	virtual void MainLoop() { std::cout << "a subsystem has no main loop" << std::endl; } //This should be for actions before the game loop that may require other subsystems to already be initialised
};

