
#ifndef __RoleMushroomReward_H__
#define __RoleMushroomReward_H__


#include "Role.h"

class RoleMushroomReward : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	/* 
		1. ��������״̬
		2. ������������
		3. �ƶ�
	*/
	bool _bGrow = false;
	void growUp();

	void moveLeft(float dt);
	void moveRight(float dt);
	void moveDown(float dt);

	CollisionResult collsion(Role* mario, const Rect& rcMario);
};


#endif
