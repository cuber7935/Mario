#include "RoleLadderLR.h"
#include "RoleMario.h"

bool RoleLadderLR::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	_LorR = objProperty["LorR"].asInt();
	_ladderDis = objProperty["ladderDis"].asInt();

	_right = !_LorR;
	if (_right)
	{
		_LL = this->getPositionX();
		_RR = _LL + _ladderDis;
	}
	else
	{
		_RR = this->getPositionX();
		_LL = _RR - _ladderDis;
	}

	_speed = 60;

	setTexture("ladder.png");

	return true;
}

void RoleLadderLR::moveLeft(float dt)
{
	if (_right)return;

	this->setPositionX(this->getPositionX() - _speed*dt);

	/* 梯子带着Mario运动 */
	if (_mario)
		_mario->setPositionX(_mario->getPositionX() - _speed*dt);

	if (this->getPositionX() < _LL)
	{
		_right = true;
	}
}
void RoleLadderLR::moveRight(float dt)
{
	if (!_right) return;

	this->setPositionX(this->getPositionX() + _speed*dt);

	/* 梯子带着Mario运动 */
	if (_mario)
		_mario->setPositionX(_mario->getPositionX() + _speed*dt);

	if (this->getPositionX() > _RR)
	{
		_right = false;
	}
}

Role::CollisionResult RoleLadderLR::collsion(Role* role, const Rect& rcMario)
{
	RoleMario* mario = (RoleMario*)role;

	Rect rc = this->getBoundingBox();

	/* 如果梯子和Mario没有碰撞 */
	if (!rc.intersectsRect(rcMario))
	{
		/* 之前Mario是不是在这个梯子上 */
		if (_mario)
		{
			// 解除关系
			mario->_ladder = nullptr;
			_mario = nullptr;
		}

		return Role::CollisionResult::Nothing;
	}

	/* 如果Mario本身就在该梯子上，就不需要碰撞检测 */
	//if (_mario) return Role::CollisionResult::Nothing;
	if (mario->_ladder) return Role::CollisionResult::Nothing;

	/* Mario和梯子碰上了，根据Mario的中心坐标点和梯子的中心坐标点的高度来判断Mario的碰撞方向 */
	if (rcMario.getMidY() > rc.getMidY())
	{
		// 马里奥脚踩在梯子上
		// 微调
		role->setPositionY(rc.getMaxY()-0.01);

		// 记录下Mario
		_mario = role;

		// Mario也要记录，在某个梯子上
		mario->_ladder = this;
	}
	else
	{
		// 马里奥头顶在梯子上
		role->_speedDown = _speedUp; // 反弹
		role->_speedUp = 0;
	}

	return Role::CollisionResult::Nothing;
}