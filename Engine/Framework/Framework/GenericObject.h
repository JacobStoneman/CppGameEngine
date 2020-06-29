
#include "EntityObject.h"

//For entities that don't do anything interesting, i.e not the player
class GenericObject :
	public EntityObject
{
public:
	GenericObject(float x, float y, float z, float hX, float hY, float hZ, float scaleX, float scaleY, float scaleZ, int _meshNum);
};
