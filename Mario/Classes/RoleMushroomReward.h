
#ifndef __RoleMushroomReward_H__
#define __RoleMushroomReward_H__


#include "Role.h"

class RoleMushroomReward : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	/* 
		1. 看不见的状态
		2. 出生。。动作
		3. 移动
	*/
	bool _bGrow = false;
	void growUp();

	void moveLeft(float dt);
	void moveRight(float dt);
	void moveDown(float dt);

	CollisionResult collsion(Role* mario, const Rect& rcMario);
};


#endif
