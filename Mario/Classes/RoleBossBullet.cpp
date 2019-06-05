#include "RoleBossBullet.h"

bool RoleBossBullet::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	_right = objProperty["right"].asBool();
	this->setRunning(true);

	return true;
}

void RoleBossBullet::updateStatus()
{
	stopAnimation();
	if (_right)
	{
		this->runAnimation(ANI_BOSS_BULLET_RIGHT);
	}
	else
	{
		this->runAnimation(ANI_BOSS_BULLET_LEFT);
	}
}

void RoleBossBullet::moveLeft(float dt)
{
	if (this->_right)return;

	this->setPositionX(this->getPositionX() - dt* _speed);
}
void RoleBossBullet::moveRight(float dt)
{
	if (this->_right)
		this->setPositionX(this->getPositionX() + dt* _speed);
}

Role::CollisionResult RoleBossBullet::collsion(Role* mario, const Rect& rcMario)
{
	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
	{
		return CollisionResult::Nothing;
	}

	return Role::CollisionResult::MarioDie;
}