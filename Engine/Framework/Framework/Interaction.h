#pragma once

//All types of interactions the UI subsystem should be able to respond to
//Allows for different control schemes 
const enum class Interaction {
	MOVE_PLAYER_FORWARD,
	MOVE_PLAYER_BACKWARD,
	PLAYER_JUMP,
	STRAFE_PLAYER_LEFT,
	STRAFE_PLAYER_RIGHT,
	CONNECT_CLIENT,
	DISCONNECT_CLIENT,
	PLAY_MUSIC,
	VOLUME_UP,
	VOLUME_DOWN,
	max
};