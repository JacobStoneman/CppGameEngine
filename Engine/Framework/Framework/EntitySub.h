#pragma once
#include "Subsystem.h"
#include "GenericObject.h"
#include "Player.h"
#include "LightEntity.h"
#include "Engine.h"
#include<glm/gtx/rotate_vector.hpp>

class Engine;

class EntitySub :
	public Subsystem
{
private:
	static void(*EventReaction[0])(std::vector<arg>);
public:
	static void EntitySub::InitSystem();
	static void EntitySub::StartSystem();
	static void EntitySub::MainLoop();
	static void Update();
	EntitySub();
	~EntitySub();
};

