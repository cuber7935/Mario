#ifndef _ROLE_MUSHROOM_REWARD_H_
#define _ROLE_MUSHROOM_REWARD_H_


#include "Role.h"

//蘑菇奖赏
class RoleMushroomReward : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	void moveLeft(float dt);
	void moveRight(float dt);
	void moveDown(float dt);

	CollisionResult collsion(Role* mario, const Rect& rcMario);

	void growUp();

	/*
	1. 看不见的状态
	2. 出生。。动作
	3. 移动
	*/
	bool _bGrow = false;
	
};


#endif
