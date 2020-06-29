#include "Networking.h"
#include "Engine.h"

ENetAddress address;
ENetHost* client;
ENetPeer* peer;
ENetEvent enetEvent;
ClientData* clientData = new ClientData();
ENetPacket* dataPacket;

int* packetType = new int;

Engine* gameEngine;
void(*NetworkEventReaction[Engine::EVENTCOUNT])(std::vector<arg>);

//Checks for an existing connection and if none exist, connects the client
void ConnectClient(std::vector<arg> args) {
	if (client != NULL) {
		std::cout << "Client already exits" << std::endl;
	}
	else {
		client = enet_host_create(NULL, 1, 2, 0, 0);
		if (client == NULL)
		{
			std::cout << "ERROR::Client failed to initialise!" << std::endl;
		}
		else {
			if (peer != NULL) {
				std::cout << "Client has already connected to the server" << std::endl;
			}
			else {
				peer = enet_host_connect(client, &address, 2, 0);

				if (peer == NULL) {
					std::cout << "ERROR::No available peers for initializing an ENet connection.\n";
				}
				else {
					std::cout << "Client has successfully connected" << std::endl;
				}
			}
		}
	}
}

//Sends a packet with position data
void SendPacket(std::vector<arg> args) {
	vec3 positionData;
	positionData.x = args[0].e->position.x;
	positionData.y = args[0].e->position.y;
	positionData.z = args[0].e->position.z;

	clientData->position = positionData;

	if (client != NULL) {
		dataPacket = enet_packet_create(clientData, sizeof(ClientData), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(peer, 0, dataPacket);
	}
}

void Networking::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Initialising Network Subsystem::::" << std::endl;
	gameEngine = new Engine();

	//ENet preamble
	*packetType = -1;

	if (enet_initialize() != 0) {
		std::cout << "ERROR::Enet failed to initialize" << std::endl;
	}

	enet_address_set_host(&address, "localhost");
	address.port = 1234;

	//Initialise function pointers
	void (*fnpConnectClient)(std::vector<arg> args) = ConnectClient;
	void (*fnpSendPacket)(std::vector<arg> args) = SendPacket;
	NetworkEventReaction[(int)EventType::EVENT_CONNECT_CLIENT] = fnpConnectClient;
	NetworkEventReaction[(int)EventType::EVENT_SEND_PACKET] = fnpSendPacket;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}

void Networking::StartSystem()
{
	Update();
}
void Networking::MainLoop()
{
	Update();
	//If connected, check for incoming packets
	if (client != NULL) {
		while (enet_host_service(client, &enetEvent, 0) > 0)
		{
			switch (enetEvent.type) {
			case ENET_EVENT_TYPE_RECEIVE:
				std::cout << "Packet received!" << std::endl;
				memcpy(packetType, enetEvent.packet->data, sizeof(int));
				break;
			}
		}
	}
}

//Checks event queue for networking events
void Networking::Update()
{
	for (int i = 0; i < Engine::eventQ.size(); i++)
	{
		for (int j = 0; j < Engine::eventQ[i].eventSystems.size(); j++)
		{
			if (Engine::eventQ[i].eventSystems[j] == SubsystemEnum::NETWORKING)
			{
				NetworkEventReaction[(int)Engine::eventQ[i].eType](Engine::eventQ[i].args);
				Engine::eventQ[i].eventSystems.erase(Engine::eventQ[i].eventSystems.begin() + j);
			}
		}
	}
}