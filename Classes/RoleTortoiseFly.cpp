#include "RoleTortoiseFly.h"


bool RoleTortoiseFly::init(ValueMap& objProperty)
{
	RoleTortoise::init(objProperty);

	_roundDis = objProperty["flyDis"].asInt();

	_xTurnLeft = this->getPositionX();
	_xTurnRight = _xTurnLeft - _roundDis;

	return true;
}

void RoleTortoiseFly::updateStatus()
{
	if (_flying) // 正在天上飞
	{
		stopAnimation();
		if (_right)
		{
			runAnimation(ANI_TORTOISE_FLY_RIGHT);
		}
		else
		{
			runAnimation(ANI_TORTOISE_FLY_LEFT);
		}
	}
	else // 不在飞
	{
		if (_dropping)  // 正在降落
		{
			stopAnimation();
			if (_right)
			{
				this->setDisplayFrameWithAnimationName(ANI_TORTOISE_RUN_RIGHT, 0);
				//setSpriteFrameByAnimation(ANI_TORTOISE_RUN_RIGHT);
			}
			else
			{
				this->setDisplayFrameWithAnimationName(ANI_TORTOISE_RUN_LEFT, 0);
				//setSpriteFrameByAnimation(ANI_TORTOISE_RUN_LEFT);
			}
		}
		else  // 已经落地
		{
			RoleTortoise::updateStatus();
		}
	}
}


void RoleTortoiseFly::moveLeft(float dt)
{
	// 根据飞天乌龟的状态不同
	if (_flying) // 在fly状态时
	{
		if (_right)
			return;

		this->setPositionX(this->getPositionX() - dt*_speed);
		if (this->getPositionX() < _xTurnRight)
		{
			// 设置了变量，并调用updateStatus改变了表现状态
			setRight(true);
		}
	}
	else if (_dropping)
	{
		// 不平行移动
	}
	else
	{
		RoleTortoise::moveLeft(dt);
	}
}
void RoleTortoiseFly::moveRight(float dt)
{
	if (_flying)
	{
		if (!_right)
			return;

		this->setPositionX(this->getPositionX() + dt*_speed);
		if (this->getPositionX() > _xTurnLeft)
		{
			setRight(false);
		}
	}
	else if (_dropping)
	{
		// 不水平移动
	}
	else
	{
		RoleTortoise::moveRight(dt);
	}
}
void RoleTortoiseFly::moveDown(float dt)
{
	if (_flying)
	{
		// 竖直方向不移动
	}
	else if (_dropping)
	{
		this->setPositionY(this->getPositionY() - _speedDown*dt);

		if (isBlockDown())
		{
			this->setPositionY(this->getPositionY() + _speedDown*dt);
			
			util->moveDownAjust(this);

			_speedDown = _gravity;

			_dropping = false;
			updateStatus();

			return;
		}

		_speedDown += _gravity;

	}
	else
	{
		RoleTortoise::moveDown(dt);
	}
}

Role::CollisionResult RoleTortoiseFly::collsion(Role* role, const Rect& rcMario)
{
	Rect rc = this->getBoundingBox();
	if (_flying)
	{
		if (!rc.intersectsRect(rcMario))
		{
			return CollisionResult::Nothing;
		}

		/* rcMario.getMinY() > rc.getMidY(): 表示Mario的脚底超过了飞天乌龟身材一半
		   role->_speedUp <= 0: 表示Mario正在下降 */
		if (rcMario.getMinY() > rc.getMidY() && role->_speedUp <= 0)
		{
			/* 飞天乌龟被踩了 */
			_flying = false;
			_dropping = true;
			updateStatus();
			return CollisionResult::Nothing;
		}
		else
		{
			/* mario被撞了 */
			return CollisionResult::MarioDie;
		}
	}
	else if (_dropping)
	{
		if (!rc.intersectsRect(rcMario))
		{
			return CollisionResult::Nothing;
		}

		/* rcMario.getMinY() > rc.getMidY(): 表示Mario的脚底超过了飞天乌龟身材一半
		role->_speedUp <= 0: 表示Mario正在下降 */
		if (rcMario.getMinY() > rc.getMidY() && role->_speedUp <= 0)
		{
			/* 加速下降 */
			this->_speedDown += 50;
			return CollisionResult::Nothing;
		}
		else
		{
			/* mario被撞了 */
			return CollisionResult::MarioDie;
		}
	}
	else
	{
		return RoleTortoise::collsion(role, rcMario);
	}

	return CollisionResult::Nothing;
}