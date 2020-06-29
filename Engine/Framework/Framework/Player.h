#pragma once
#include "EntityObject.h"
class Player :
	public EntityObject
{
public:
	Player(float x, float y, float z, float hX, float hY, float hZ, float scaleX, float scaleY, float scaleZ, int _meshNum);
	~Player();
};

