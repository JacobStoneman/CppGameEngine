#include "KeyboardInput.h"

//Checks for specific key presses then calls a function pointer in the UI
//Multiple of these control schemes can be created provided the UI is told which ones to use
SHORT KeyboardInput::CheckInput(SHORT prevVal)
{
	SHORT val;
	if (val = GetKeyState('W') & 0x8000)
	{
		UserInterface::InteractionArray[(int)Interaction::MOVE_PLAYER_FORWARD]();
	}
	if (val = GetKeyState('S') & 0x8000)
	{
		UserInterface::InteractionArray[(int)Interaction::MOVE_PLAYER_BACKWARD]();
	}
	if (val = GetKeyState('A') & 0x8000)
	{
		UserInterface::InteractionArray[(int)Interaction::STRAFE_PLAYER_LEFT]();
	}
	if (val = GetKeyState('D') & 0x8000)
	{
		UserInterface::InteractionArray[(int)Interaction::STRAFE_PLAYER_RIGHT]();
	}
	if (val = GetKeyState('G') & 0x8000)
	{
		if (val != prevVal) {
			UserInterface::InteractionArray[(int)Interaction::PLAYER_JUMP]();
		}
	}
	if (val = GetKeyState('P') & 0x8000)
	{
		if (val != prevVal) {
			UserInterface::InteractionArray[(int)Interaction::PLAY_MUSIC]();
		}
	}
	if (val = GetKeyState('C') & 0x8000)
	{
		if (val != prevVal) {
			UserInterface::InteractionArray[(int)Interaction::CONNECT_CLIENT]();
		}
	}
	if (val = GetKeyState('O') & 0x8000)
	{
		UserInterface::InteractionArray[(int)Interaction::VOLUME_UP]();
	}
	if (val = GetKeyState('L') & 0x8000)
	{
		UserInterface::InteractionArray[(int)Interaction::VOLUME_DOWN]();
	}
	return val;
}