#ifndef __RoleTortoiseRound_H__
#define __RoleTortoiseRound_H__

#include "RoleTortoise.h"

class RoleTortoiseRound : public RoleTortoise
{
public:
	virtual bool init(ValueMap& objProperty);

	/* 保存巡逻范围，地图对象层中有设定，初始化巡逻乌龟时获取 */
	int _roundDis;
	
	/* 巡逻乌龟左右移动控制，向下移动控制由父类负责 */
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);

	/* 具体化的巡逻范围 */
	int _xTurnRight;  /* 乌龟的位置小于该值，方向改成向右 */
	int _xTurnLeft;  /* 乌龟的位置大于该值，方向改成向左 */
};

#endif
