#ifndef _ROLE_LADDER_H_
#define _ROLE_LADDER_H_
#include "Role.h"


// 梯子
class RoleLadderLR : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	void moveLeft(float dt);
	void moveRight(float dt);

	virtual CollisionResult collsion(Role*, const Rect&);

private:
	Role* _mario = nullptr;
	int _LorR;				// 开始向哪个方向移动
	int _ladderDis;			// 移动范围

	int _LL;				// 最左边的位置 
	int _RR;				// 最右边的位置 
};

#endif

