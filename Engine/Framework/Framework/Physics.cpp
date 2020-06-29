#include "Physics.h"

void(*Physics::EventReaction[Engine::EVENTCOUNT])(std::vector<arg>);

btBroadphaseInterface* broadPhase;
btDefaultCollisionConfiguration* collisionConfiguration;
btCollisionDispatcher* dispatcher;
btSequentialImpulseConstraintSolver* solver;
btDiscreteDynamicsWorld* world;

Physics::Physics()
{
}

Physics::~Physics()
{
}

//Moves the entities position value along the heading axis
void MoveEntity(std::vector<arg> args) {
	float xPos = args[0].e->position.x;
	float yPos = args[0].e->position.y;
	float zPos = args[0].e->position.z;
	glm::vec3 head(args[0].e->heading.x, args[0].e->heading.y, args[0].e->heading.z);
	glm::vec3 newPos(xPos, yPos, zPos);
	if (args[0].i == 0) { // Forwards/Backwards
		newPos.x = xPos + (head.x * args[0].f);
		newPos.y = yPos + (head.y * args[0].f);
		newPos.z = zPos + (head.z * args[0].f);
	}
	else if (args[0].i == 1) { // Strafe
		newPos += glm::normalize(glm::cross(head, glm::vec3(0, 1, 0))) * args[0].f;
	}

	args[0].e->position.x = newPos.x;
	args[0].e->position.y = newPos.y;
	args[0].e->position.z = newPos.z;

	Event newEvent(EventType::EVENT_SEND_PACKET);
	newEvent.addSubsystem(SubsystemEnum::NETWORKING);
	newEvent.addArg(args[0]);
	Engine::eventQ.push_back(newEvent);
}

void EntityJump(std::vector<arg> args) {
	if (args[0].e->position.y <= 0) {
		float xPos = args[0].e->position.x;
		float yPos = args[0].e->position.y;
		float zPos = args[0].e->position.z;
		glm::vec3 newPos(xPos, yPos, zPos);
		newPos.y = newPos.y + args[0].f;
		args[0].e->position.x = newPos.x;
		args[0].e->position.y = newPos.y;
		args[0].e->position.z = newPos.z;
	}
}

void BuildPhysicsWorld() {
	//broadPhase = new btDbvtBroadphase();
	//collisionConfiguration = new btDefaultCollisionConfiguration;
	//dispatcher = new btCollisionDispatcher(collisionConfiguration);
	//solver = new btSequentialImpulseConstraintSolver();
	//world = new btDiscreteDynamicsWorld(dispatcher, broadPhase, solver, collisionConfiguration);
	//world->setGravity(btVector3(0, -9.8, 0));
}

//Checks the y value of objects and applies simple gravity if in the air
void UpdateObjects() {
	for (int i = 0; i < Engine::entities.size(); i++) {
		if (Engine::entities[i]->position.y > 0) {
			Engine::entities[i]->position.y--;
			if (Engine::entities[i]->position.y < 0) {
				Engine::entities[i]->position.y = 0;
			}
		}
	}
}

void Physics::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Initialising Entity Subsystem::::" << std::endl;

	//Declare function pointers
	void (*fnpMoveEntity)(std::vector<arg> args) = MoveEntity;
	void (*fnpEntityJump)(std::vector<arg> args) = EntityJump;
	EventReaction[(int)EventType::EVENT_MOVE_ENTITY] = fnpMoveEntity;
	EventReaction[(int)EventType::EVENT_ENTITY_JUMP] = fnpEntityJump;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}

void Physics::StartSystem()
{
	Update();
}

void Physics::MainLoop()
{
	Update();
	UpdateObjects();
}

//Checks event queue for physics events
void Physics::Update() {
	for (int i = 0; i < Engine::eventQ.size(); i++)
	{
		for (int j = 0; j < Engine::eventQ[i].eventSystems.size(); j++)
		{
			if (Engine::eventQ[i].eventSystems[j] == SubsystemEnum::PHYSICS)
			{
				EventReaction[(int)Engine::eventQ[i].eType](Engine::eventQ[i].args);
				Engine::eventQ[i].eventSystems.erase(Engine::eventQ[i].eventSystems.begin() + j);
			}
		}
	}
}
