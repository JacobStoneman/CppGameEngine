#pragma once

#include <string>
#include <vector>
#include "vec3.h"

//Parent class for all entities with generic info such as poition and rotation
class EntityObject
{
public:
	vec3 position;
	vec3 heading;
	vec3 rotation;
	vec3 scale;
	int meshNum;
	EntityObject();
	~EntityObject();
};

