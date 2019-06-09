#ifndef _ROLE_MUSHROOM_REWARD_H_
#define _ROLE_MUSHROOM_REWARD_H_


#include "Role.h"

//Ģ������
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
	1. ��������״̬
	2. ������������
	3. �ƶ�
	*/
	bool _bGrow = false;
	
};


#endif
