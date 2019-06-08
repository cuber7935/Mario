#include "RoleBoss.h"


bool RoleBoss::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	_speed = 60;

#if 0
	/* 假设boss一开始朝右走 */
	this->_leftMost = this->getPositionX();
	this->_rightMost = _leftMost + 120;
	_right = true;
#else
	/* 假设boss一开始朝左走 */
	this->_rightMost = this->getPositionX();
	this->_leftMost = _rightMost - 120;
	_right = false;

	_rightMost += 16;
	_leftMost += 16;
#endif

	updateStatus();

	// scheduleOnce(schedule_selector(RoleBoss::jump), CCRANDOM_0_1()/2);
	// scheduleOnce在这种场合下，有Bug
	jumpEngine();
	fireEngine();

	return true;
}

void RoleBoss::fire()
{
	// 发送一个消息给Model去发射子弹
	_eventDispatcher->dispatchCustomEvent("bossfire", this);

	fireEngine();
}
void RoleBoss::fireEngine()
{
	DelayTime* delay = DelayTime::create(CCRANDOM_0_1()+1);
	CallFunc* call = CallFunc::create(CC_CALLBACK_0(RoleBoss::fire, this));
	this->runAction(Sequence::createWithTwoActions(delay, call));
}

void RoleBoss::jumpEngine()
{
	DelayTime* delay = DelayTime::create(CCRANDOM_0_1() / 2);
	CallFunc* call = CallFunc::create(CC_CALLBACK_0(RoleBoss::jump, this));
	this->runAction(Sequence::createWithTwoActions(delay, call));
}

void RoleBoss::jump()
{
	if (_speedUp > 0 || _speedDown > _gravity)
	{
	}
	else
	{
		/* 0～0.5秒执行一次跳跃尝试，  每次跳跃尝试有30%概率会跳跃 */
		int a = CCRANDOM_0_1() * 100;
		if (a < 30)
		{
			log("speedUp=%f, speedDown=%f", _speedUp, _speedDown);
			this->_speedUp = CCRANDOM_0_1() * 40 + 100;
		}
	}

//	scheduleOnce(schedule_selector(RoleBoss::jump), CCRANDOM_0_1() / 2);

	jumpEngine();
}

void RoleBoss::moveLeft(float dt)
{
	if (_right)return;
	this->setPositionX(this->getPositionX() - dt*_speed);

	if (this->getPositionX() < _leftMost)
		setRight(true);
}
void RoleBoss::moveRight(float dt)
{
	if (!_right)return;
	this->setPositionX(this->getPositionX() + dt*_speed);

	if (this->getPositionX() > _rightMost)
		setRight(false);
}

void RoleBoss::moveUp(float dt)
{
	if (_speedUp <= 0) return;

	this->setPositionY(this->getPositionY() + dt*_speedUp);
	_speedUp -= _gravity;
}

void RoleBoss::moveDown(float dt)
{
	if (_speedUp > 0) return;
	
	this->setPositionY(this->getPositionY() - dt*_speedDown);
	if (isBlockDown())
	{
		this->setPositionY(this->getPositionY() + dt*_speedDown);
		this->moveDownAjust();
		_speedDown = _gravity;
		return;
	}
	_speedDown += _gravity;
}

void RoleBoss::updateStatus()
{
	stopAnimation();
	if (_right)
	{
		runAnimation(ANI_BOSS_RIGHT);
	}
	else
	{
		runAnimation(ANI_BOSS_LEFT);
	}
}

Role::CollisionResult RoleBoss::collsion(Role* mario, const Rect& rcMario)
{
	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
	{
		return CollisionResult::Nothing;
	}

	return Role::CollisionResult::MarioDie;
}