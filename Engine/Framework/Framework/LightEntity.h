#pragma once
#include "EntityObject.h"

//Lights will only require position values
class LightEntity :
	public EntityObject
{
public:
	LightEntity(float x, float y, float z);
};

