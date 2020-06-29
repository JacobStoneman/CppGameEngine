#include "Player.h"

Player::Player(float x, float y, float z, float hX, float hY, float hZ,float scaleX, float scaleY, float scaleZ, int _meshNum)
{
	this->position.x = x;
	this->position.y = y;
	this->position.z = z;
	this->heading.x = hX;
	this->heading.y = hY;
	this->heading.z = hZ;
	this->rotation.x = 0.0f;
	this->rotation.y = 0.0f;
	this->rotation.z = 0.0f;
	this->scale.x = scaleX,
	this->scale.y = scaleY,
	this->scale.z = scaleZ,
	this->meshNum = _meshNum;
}
