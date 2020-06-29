#pragma once
#include "Subsystem.h"
#include "vec3.h"
#include <enet/enet.h>

class Engine;

//Data types for use in packet creation and sending of data
struct PhysicsData {
	int packetType = 1;
	vec3 positions[2];
};

struct ClientData {
	vec3 position;
};

struct ClientPacket {
	int clientIndex;
	vec3 position;
};

class Networking :
	public Subsystem
{
public:
	static void Networking::InitSystem();
	static void Networking::StartSystem();
	static void Networking::MainLoop();
	static void Update();
};

