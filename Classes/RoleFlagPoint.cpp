#include "RoleFlagPoint.h"
#include "RoleMario.h"
bool RoleFlagPoint::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	this->setSpriteFrame(FRA_FLAG);
	this->setPositionX(this->getPositionX() - this->getBoundingBox().size.width/2);

	this->setLocalZOrder((int)ZOrder::Flag);

	return true;
}

Role::CollisionResult RoleFlagPoint::collsion(Role* role, const Rect& rcMario)
{
	RoleMario* mario = (RoleMario*)role;
	Rect rcRole = this->getBoundingBox();
	if (_bDrop == false)
	{

		if (rcMario.getMaxX() >= rcRole.getMaxX() - 8)
		{
			this->_bDrop = true;

			// Mario要进入自动控制状态
			mario->autoCtrl1();

			// 拆桥
			_eventDispatcher->dispatchCustomEvent("breakbridge", NULL);
		}
	}
	else
	{
		Rect rcRole = this->getBoundingBox();
		if (rcRole.intersectsRect(rcMario))
		{
			mario->autoCtrl2();
			return Role::CollisionResult::RoleDie;
		}
	}

	return Role::CollisionResult::Nothing;
}

void RoleFlagPoint::moveDown(float dt)
{
	if (!_bDrop)
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