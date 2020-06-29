#include "EntitySub.h"

void(*EntitySub::EventReaction[Engine::EVENTCOUNT])(std::vector<arg>);

//Creation of the different types of entities
void CreatePlayerEntity(std::vector<arg> args) {
	EntityObject* newPlayer = new Player(args[0].f, args[1].f, args[2].f, args[3].f, args[4].f, args[5].f, args[6].f,args[7].f,args[8].f, args[9].i);
	Engine::entities.push_back(newPlayer);

	Event newEvent(EventType::EVENT_CREATE_PLAYER);
	newEvent.addSubsystem(SubsystemEnum::GRAPHICS);
	arg arg1;
	arg1.e = newPlayer;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void CreateObjectEntity(std::vector<arg> args) {
	EntityObject* newObject = new GenericObject(args[0].f, args[1].f, args[2].f, args[3].f, args[4].f, args[5].f, args[6].f, args[7].f, args[8].f, args[9].i);
	Engine::entities.push_back(newObject);

	Event newEvent(EventType::EVENT_CREATE_OBJECT);
	newEvent.addSubsystem(SubsystemEnum::GRAPHICS);
	arg arg1;
	arg1.e = newObject;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void CreateLightEntity(std::vector<arg> args) {
	EntityObject* newLight = new LightEntity(args[0].f, args[1].f, args[2].f);
	Event newEvent(EventType::EVENT_CREATE_LIGHT);
	newEvent.addSubsystem(SubsystemEnum::GRAPHICS);
	arg arg1;
	arg1.e = newLight;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

//Rotates an entity and its heading by a given value
void RotateEntity(std::vector<arg> args) {
	glm::vec3 head(args[0].e->heading.x, args[0].e->heading.y, args[0].e->heading.z);
	head = glm::rotate(head, glm::radians(args[0].f), glm::vec3(0.0, 1.0, 0.0));
	args[0].e->heading.x = head.x;
	args[0].e->heading.y = head.y;
	args[0].e->heading.z = head.z;
	args[0].e->rotation.y += args[0].f;
}

void EntitySub::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Initialising Entity Subsystem::::" << std::endl;

	//Create function pointers
	void (*fnpCreatePlayerEntity)(std::vector<arg> args) = CreatePlayerEntity;
	void (*fnpCreateObjectEntity)(std::vector<arg> args) = CreateObjectEntity;
	void (*fnpCreateLightEntity)(std::vector<arg> args) = CreateLightEntity;
	void (*fnpRotateEntity)(std::vector<arg> args) = RotateEntity;
	EventReaction[(int)EventType::EVENT_CREATE_PLAYER_ENTITY] = fnpCreatePlayerEntity;
	EventReaction[(int)EventType::EVENT_CREATE_OBJECT_ENTITY] = fnpCreateObjectEntity;
	EventReaction[(int)EventType::EVENT_CREATE_LIGHT_ENTITY] = fnpCreateLightEntity;
	EventReaction[(int)EventType::EVENT_ROTATE_ENTITY] = fnpRotateEntity;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl<<std::endl;
}

void EntitySub::StartSystem()
{
	Update();
}

void EntitySub::MainLoop()
{
	Update();
}

//Check for entity specific events in the event queue
void EntitySub::Update() {
	for (int i = 0; i < Engine::eventQ.size(); i++)
	{
		for (int j = 0; j < Engine::eventQ[i].eventSystems.size(); j++)
		{
			if (Engine::eventQ[i].eventSystems[j] == SubsystemEnum::ENTITYSUB)
			{
				EventReaction[(int)Engine::eventQ[i].eType](Engine::eventQ[i].args);
				Engine::eventQ[i].eventSystems.erase(Engine::eventQ[i].eventSystems.begin() + j);
			}
		}
	}
}