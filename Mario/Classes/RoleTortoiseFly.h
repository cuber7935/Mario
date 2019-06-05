#ifndef __RoleTortoiseFly_H__
#define __RoleTortoiseFly_H__

#include "RoleTortoiseRound.h"

class RoleTortoiseFly : public RoleTortoiseRound
{
public:
	virtual bool init(ValueMap& objProperty);

	// 是否在飞行和正在降落的属性
	bool _flying = true;    // false
	bool _dropping = false; // false

	// 更新状态
	void updateStatus();

	// 移动函数
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	CollisionResult collsion(Role*, const Rect&);
};

#endif

