#include "RoleMushroomAddLife.h"

bool RoleMushroomAddLife::init(ValueMap& objProperty)
{
	Role::init(objProperty);
	
	this->setSpriteFrame(FRA_MUSHROOM_REWARD2);

	return true;
}