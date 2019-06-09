#ifndef _ROLE_TORTOISE_FLY_H_
#define _ROLE_TORTOISE_FLY_H_

#include "RoleTortoiseRound.h"

// 飞天龟
class RoleTortoiseFly : public RoleTortoiseRound
{
public:
	virtual bool init(ValueMap& objProperty);

	// 更新状态
	void updateStatus();

	// 移动函数
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	CollisionResult collsion(Role*, const Rect&);

protected:
	// 是否在飞行和正在降落的属性
	bool _flying	= true;		// 默认飞行
	bool _dropping	= false;	// 默认没下降
};

#endif

