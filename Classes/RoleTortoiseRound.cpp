#include "RoleTortoiseRound.h"

bool RoleTortoiseRound::init(ValueMap& objProperty)
{
	// 先调用父类的初始化函数
	RoleTortoise::init(objProperty);

	// 获取巡逻范围，并细化左右边界
	_roundDis = objProperty["roundDis"].asInt();
	_xTurnLeft = this->getPositionX();
	_xTurnRight = _xTurnLeft - _roundDis;

	return true;
}

void RoleTortoiseRound::moveLeft(float dt)
{
	// 调用父类的move函数，实现水平移动
	RoleTortoise::moveLeft(dt);

	//移动完成之后，判断是否到了边界，如果是，掉头
	if (this->_bCrazy == false)
	{
		if (this->getPositionX() < _xTurnRight)
		{
			setRight(true);
		}
	}
}
void RoleTortoiseRound::moveRight(float dt)
{
	RoleTortoise::moveRight(dt);
	if (this->_bCrazy == false)
	{
		if (this->getPositionX() > _xTurnLeft)
		{
			setRight(false);
		}
	}
}