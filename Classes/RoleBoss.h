#ifndef _ROLE_BOSS_H_
#define _ROLE_BOSS_H_

#include "Role.h"

//boss类
class RoleBoss : public Role
{
public:
	virtual bool init(ValueMap& objProperty)override;

	// 移动方向（左右上下）
	virtual void moveLeft(float dt)override;
	virtual void moveRight(float dt)override;
	virtual void moveUp(float dt)override;
	virtual void moveDown(float dt)override;

	// 跟新状态
	virtual void updateStatus()override;

	// 碰撞检测
	virtual CollisionResult collsion(Role*, const Rect&);

	// boss跳跃
	void jump();
	void jumpEngine();

	// boss发射子弹
	void fire();
	void fireEngine();

public:
	int _leftMost;
	int _rightMost;
};

#endif

