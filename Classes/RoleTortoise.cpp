#include "RoleTortoise.h"

bool RoleTortoise::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	//this->runAnimation(ANI_TORTOISE_RUN_LEFT);
	_speed = 60;
	_right = false;
	this->updateStatus();

	return true;
}

void RoleTortoise::setScared(bool scared)
{
	if (_bScared != scared)
	{
		_bScared = scared;
		updateStatus();
	}
}

void RoleTortoise::setCrazy(bool crazy)
{
	if (_bCrazy != crazy)
	{
		_bCrazy = crazy;
		updateStatus();
	}
}

void RoleTortoise::moveLeft(float dt)
{
	if (!_running) return;
	if (_right) return;

	if (_bScared && _bCrazy ==false) return;

	this->setPositionX(this->getPositionX() - dt*_speed);

	if (isBlockLeft())
	{
		this->setPositionX(this->getPositionX() + dt*_speed);
		// _right = true;
		setRight(true);
	}
}
void RoleTortoise::moveRight(float dt)
{
	if (!_running) return;
	if (!_right) return;
	if (_bScared && _bCrazy == false) return;

	this->setPositionX(this->getPositionX() + dt*_speed);

	if (isBlockRight())
	{
		this->setPositionX(this->getPositionX() - dt*_speed);
	//	_right = false;
		setRight(false);
	}
}
void RoleTortoise::moveDown(float dt)
{
	if (!_running) return;

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

void RoleTortoise::updateStatus()
{
	
	if (this->_bScared)
	{
		if (this->_bCrazy)
		{
			// stopAnimation
			_speed = 240;
		}
		else
		{
			stopAnimation();
			this->runAnimation(ANI_TORTOISE_SCARED);
		}
	}
	else
	{
		stopAnimation();
		if (this->_right)
		{
			this->runAnimation(ANI_TORTOISE_RUN_RIGHT);
		}
		else
		{
			this->runAnimation(ANI_TORTOISE_RUN_LEFT);
		}
	}
}

Role::CollisionResult RoleTortoise::collsion(Role* mario, const Rect& rcMario)
{
	if (_bScared)
	{
		if (_bCrazy)
		{
#if 1
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


			//	this->setDead(false);
			//this->setScared(true);
			this->setCrazy(false);

			/* Mario反弹 */
			mario->_speedUp = 100;
			mario->_speedDown = _gravity;

			return CollisionResult::Nothing;
#endif
		}
		else
		{

			Rect rcRole = this->getBoundingBox();
			if (!rcRole.intersectsRect(rcMario))
				return CollisionResult::Nothing;

			if (rcRole.getMidX() < rcMario.getMidX())
			{
				// 向左走
				_right = false;

			}
			else
			{
				// 向右走
				_right = true;
			}
			setCrazy(true);
		}
	}
	else // 当乌龟在普通状态时，碰撞检测和蘑菇怪一样
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

		
	//	this->setDead(false);
		this->setScared(true);

		/* Mario反弹 */
		mario->_speedUp = 100;
		mario->_speedDown = _gravity;

		return CollisionResult::Nothing;
	}


	return CollisionResult::Nothing;
}