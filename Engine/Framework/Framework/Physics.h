#pragma once
#include "Subsystem.h"
#include "Engine.h"
#include "Event.h"

#include <src/btBulletDynamicsCommon.h>
#include<src/btBulletCollisionCommon.h>

class Physics :
	public Subsystem
{
private:
	static void(*EventReaction[0])(std::vector<arg>);
public:
	Physics();
	~Physics();
	static void Physics::InitSystem();
	static void Physics::StartSystem();
	static void Physics::MainLoop();
	static void Update();
};

