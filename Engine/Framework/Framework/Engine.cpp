#include "Engine.h"
std::vector<Event> Engine::eventQ;
std::vector<EntityObject*> Engine::entities;
int Engine::pEntityNum;
int Engine::width = 600;
int Engine::height = 400;

Engine::Engine()
{
}

Engine::~Engine()
{
}

//Initialise each subsystem
//Initialisation is used for system preamble and sending of events that control startup
void Engine::InitEngine() {
	Networking::InitSystem();
	Physics::InitSystem();
	EntitySub::InitSystem();
	GameData::InitSystem();
	Graphics::InitSystem();
	UserInterface::InitSystem();
	Audio::InitSystem();
	Engine::StartEngine();
}

//Start each subsystem
//Start is used to respond to events created by other systems that need to be processed before the main loop
void Engine::StartEngine()
{
	Networking::StartSystem();
	Physics::StartSystem();
	EntitySub::StartSystem();
	GameData::StartSystem();
	Graphics::StartSystem();
	UserInterface::StartSystem();
	Audio::StartSystem();
	
	//Find the player entity
	for (int i = 0; i < Engine::entities.size(); i++) {
		if (Engine::entities[i]->meshNum == 0) {
			Engine::pEntityNum = i;
		}
	}

	Engine::MainLoop();
}

//Loop indefinately and call each systems update function
void Engine::MainLoop()
{
	std::cout << "Engine successfully initialised - beginning main loop" << std::endl;
	while (true) {
		Networking::MainLoop();
		Physics::MainLoop();
		EntitySub::MainLoop();
		Graphics::MainLoop();
		Audio::MainLoop();
		UserInterface::MainLoop();
		Engine::Update();
	}
}

//Cycles through the event queue and if any events have finished being processed then they are removed from the queue
void Engine::Update()
{
	for (int i = 0; i < Engine::eventQ.size(); i++) {
		if (Engine::eventQ[i].eventSystems.size() == 0) {
			Engine::eventQ.erase(Engine::eventQ.begin() + i);
		}
	}
}

