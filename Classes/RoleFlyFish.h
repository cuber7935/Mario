#ifndef _ROLE_FLY_FISH_H_
#define _ROLE_FLY_FISH_H_

#include "Role.h"

// 飞鱼
class RoleFlyFish : public Role
{
public:
	virtual bool init(ValueMap& objProperty);
	void updateStatus();
	virtual CollisionResult collsion(Role*, const Rect&);

private:
	//回调函数 （切换 左右方向）
	void callback();

	int _duration;    // 持续时间
	int _offsetH;     // 水平偏移
	int _offsetV;     // 竖直偏移

	Vec2 _ori;        // 当前点
	Vec2 _dst;        // 目标点
};

#endif
