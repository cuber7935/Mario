#ifndef _ROLE_MUSHROOM_H_
#define _ROLE_MUSHROOM_H_

#include "Role.h"

// 蘑菇
class RoleMushroom : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	virtual void updateStatus()override;

	// 移动方向（左右上下）
	virtual void moveLeft(float dt)override;
	virtual void moveRight(float dt)override;
	virtual void moveDown(float dt)override;

	CollisionResult collsion(Role* mario, const Rect& rcMario);
};


#endif
