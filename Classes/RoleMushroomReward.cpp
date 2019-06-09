#include "RoleMushroomReward.h"

bool RoleMushroomReward::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	this->setSpriteFrame(FRA_MUSHROOM_REWARD1);

	this->setVisible(false);

	_speed = 80;

	return true;
}

void RoleMushroomReward::growUp()
{
	this->_bGrow = true;
}

void RoleMushroomReward::moveDown(float dt)
{
	if (!_bGrow)
		return;

	// 设置Mario的提前量
	this->setPositionY(this->getPositionY() - _speedDown*dt);

	if (isBlockDown())
	{
		// 如果未来的那个位置，有阻挡，再退回来
		this->setPositionY(this->getPositionY() + _speedDown*dt);

		//this->moveDownAjust();
		util->moveDownAjust(this);

		// 044. Mario这帧有阻挡，上一次调用这个函数有两种情况
		// a.上一次调用时就已经落地
		// b.上一次调用该函数moveDown时，没有被阻挡

		_speedDown = _gravity;

		return;
	}



	// 设置Mario的位置
	//	this->setPositionY(this->getPositionY() - _speedDown*dt);
	// 增加下降速度
	_speedDown += _gravity;

}
void RoleMushroomReward::moveLeft(float dt)
{
	if (!_bGrow)
		return;
	if (_right) return;

	this->setPositionX(this->getPositionX() - dt*_speed);

	if (isBlockLeft())
	{
		this->setPositionX(this->getPositionX() + dt*_speed);
		_right = true;
	}
}

void RoleMushroomReward::moveRight(float dt)
{
	if (!_bGrow)
		return;
	if (!_right) return;

	this->setPositionX(this->getPositionX() + dt*_speed);

	if (isBlockRight())
	{
		this->setPositionX(this->getPositionX() - dt*_speed);
		_right = false;
	}
}

Role::CollisionResult RoleMushroomReward::collsion(Role* mario, const Rect& rcMario)
{
	if (!_bGrow)
		return CollisionResult::Nothing;

	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
		return CollisionResult::Nothing;

	this->removeFromParent();
	return Role::CollisionResult::EAT_MUSHROOM_REWARD;
}
