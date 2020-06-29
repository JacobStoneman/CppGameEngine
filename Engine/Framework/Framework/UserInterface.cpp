#include "UserInterface.h"

void(*UserInterface::InteractionArray[(int)Interaction::max])();
int controllerType = 0;
SHORT val = NULL;

UserInterface::UserInterface() : Subsystem()
{
}

//Functions that create the necessary event for the interaction
void MovePlayerForward() {
	Event newEvent(EventType::EVENT_MOVE_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::PHYSICS);
	newEvent.addSubsystem(SubsystemEnum::AUDIO);
	arg arg1;
	arg1.e = Engine::entities[Engine::pEntityNum];
	arg1.f = 1;
	arg1.i = 0;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}
void MovePlayerBackward() {
	Event newEvent(EventType::EVENT_MOVE_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::PHYSICS);
	arg arg1;
	arg1.e = Engine::entities[Engine::pEntityNum];
	arg1.f = -1;
	arg1.i = 0;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void StrafePlayerLeft() {
	Event newEvent(EventType::EVENT_MOVE_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::PHYSICS);
	arg arg1;
	arg1.e = Engine::entities[Engine::pEntityNum];
	arg1.f = 1;
	arg1.i = 1;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void StrafePlayerRight() {
	Event newEvent(EventType::EVENT_MOVE_ENTITY);
	newEvent.addSubsystem(SubsystemEnum::PHYSICS);
	arg arg1;
	arg1.e = Engine::entities[Engine::pEntityNum];
	arg1.f = -1;
	arg1.i = 1;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void ConnectClientInteraction() {
	Event newEvent(EventType::EVENT_CONNECT_CLIENT);
	newEvent.addSubsystem(SubsystemEnum::NETWORKING);
	Engine::eventQ.push_back(newEvent);
}

void PlayMusic() {
	Event newEvent(EventType::EVENT_PLAY_MUSIC);
	newEvent.addSubsystem(SubsystemEnum::AUDIO);
	arg arg1;
	arg1.i = 0;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void VolumeUp() {
	Event newEvent(EventType::EVENT_MUSIC_VOLUME);
	newEvent.addSubsystem(SubsystemEnum::AUDIO);
	arg arg1;
	arg1.i = 1;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void VolumeDown() {
	Event newEvent(EventType::EVENT_MUSIC_VOLUME);
	newEvent.addSubsystem(SubsystemEnum::AUDIO);
	arg arg1;
	arg1.i = 0;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void PlayerJump() {
	Event newEvent(EventType::EVENT_ENTITY_JUMP);
	newEvent.addSubsystem(SubsystemEnum::PHYSICS);
	arg arg1;
	arg1.e = Engine::entities[Engine::pEntityNum];
	arg1.f = 200;
	newEvent.addArg(arg1);
	Engine::eventQ.push_back(newEvent);
}

void UserInterface::InitSystem()
{
	auto start = std::chrono::system_clock::now();
	std::cout << "::::Initialising User Interface Subsystem::::" << std::endl;

	//Declare function pointers for interactions
	void (*fnpMovePlayerForward)() = MovePlayerForward;
	void (*fnpMovePlayerBackward)() = MovePlayerBackward;
	void (*fnpPlayerJump)() = PlayerJump;
	void (*fnpStrafePlayerLeft)() = StrafePlayerLeft;
	void (*fnpStrafePlayerRight)() = StrafePlayerRight;
	void (*fnpConnectClientInteraction)() = ConnectClientInteraction;
	void (*fnpPlayMusic)() = PlayMusic;
	void (*fnpVolumeUp)() = VolumeUp;
	void (*fnpVolumeDown)() = VolumeDown;
	InteractionArray[(int)Interaction::MOVE_PLAYER_FORWARD] = fnpMovePlayerForward;
	InteractionArray[(int)Interaction::MOVE_PLAYER_BACKWARD] = fnpMovePlayerBackward;
	InteractionArray[(int)Interaction::PLAYER_JUMP] = fnpPlayerJump;
	InteractionArray[(int)Interaction::STRAFE_PLAYER_LEFT] = fnpStrafePlayerLeft;
	InteractionArray[(int)Interaction::STRAFE_PLAYER_RIGHT] = fnpStrafePlayerRight;
	InteractionArray[(int)Interaction::CONNECT_CLIENT] = fnpConnectClientInteraction;
	InteractionArray[(int)Interaction::PLAY_MUSIC] = fnpPlayMusic;
	InteractionArray[(int)Interaction::VOLUME_DOWN] = fnpVolumeDown;
	InteractionArray[(int)Interaction::VOLUME_UP] = fnpVolumeUp;

	auto end = std::chrono::system_clock::now();
	std::chrono::duration<double> elapsed_seconds = end - start;
	std::cout << "System initialized - Time taken: " << elapsed_seconds.count() << std::endl << std::endl;
}

void UserInterface::StartSystem()
{

}

void UserInterface::MainLoop()
{
	//Calls the check input function of the control scheme in use
	if (controllerType == 0) {
		val = KeyboardInput::CheckInput(val);
	}
	else {
		//Other input types here
	}
}
//UI has no need to check event queue as nothing should be sending events to the UI