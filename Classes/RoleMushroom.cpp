#include "RoleMushroom.h"

bool RoleMushroom::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	updateStatus();

	_right = false;
	_speed = 80;

	return true;
}

Role::CollisionResult RoleMushroom::collsion(Role* mario, const Rect& rcMario)
{
	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
		return CollisionResult::Nothing;

	/*
		1. Mario的minY > 怪物的midY
		2. Mario正在下降
	*/

	if (rcMario.getMinY() < rcRole.getMidY())
		return CollisionResult::MarioDie;

	if (mario->_speedDown <= _gravity)
		return CollisionResult::MarioDie;
	
	/* 蘑菇死 */
	this->setDead(false);

	/* Mario反弹 */
	mario->_speedUp = 100;
	mario->_speedDown = _gravity;


	return CollisionResult::RoleDie;
}

void RoleMushroom::moveDown(float dt)
{
	if (!_running)
		return;

	if (_dead) 
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
void RoleMushroom::moveLeft(float dt)
{
	if (!_running)
		return;
	if (_dead) return;
	if (_right) return;

	this->setPositionX(this->getPositionX() - dt*_speed);

	if (isBlockLeft())
	{
		this->setPositionX(this->getPositionX() + dt*_speed);
		_right = true;
	}
}

void RoleMushroom::moveRight(float dt)
{
	if (!_running)
		return;
	if (_dead) return;
	if (!_right) return;

	this->setPositionX(this->getPositionX() + dt*_speed);

	if (isBlockRight())
	{
		this->setPositionX(this->getPositionX() - dt*_speed);
		_right = false;
	}
}



void RoleMushroom::updateStatus()
{
	stopAllActions();

	if (_dead)
	{
		if (_deadByHit)
		{
			this->setSpriteFrame(FRA_MUSHROOM_DIE2);
		}
		else
		{
			// 被Mario踩死
			this->setSpriteFrame(FRA_MUSHROOM_DIE1);

			// 踩死之后的退场动画
			Blink* blink = Blink::create(1.0f, 5);
			RemoveSelf* remove = RemoveSelf::create();
			this->runAction(Sequence::createWithTwoActions(blink, remove));
		}
	}
	else
	{
		this->runAnimation(ANI_MUSHROOM_RUN);
	}
}