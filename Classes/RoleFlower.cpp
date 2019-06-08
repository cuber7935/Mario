#include "RoleFlower.h"
#include "RoleMario.h"

bool RoleFlower::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	this->runAnimation(ANI_FLOWER);

	/* 矫正位置：让花在水管中央，向左偏移半个瓦片宽度 */
	this->setPositionX(this->getPositionX() - 8);

	/* 执行动作：下降， 上升， 动画 */
	float duration = 1.0f;
	float delayTimeHide = 1.0f;
	float delayTimeShow = 2.0f;

	MoveBy* moveDown = MoveBy::create(duration, Vec2(0, -32));
	DelayTime* delay1 = DelayTime::create(delayTimeHide);
	MoveBy* moveUp = moveDown->reverse();
	DelayTime* delay2 = DelayTime::create(delayTimeShow);

	Sequence* seq = Sequence::create(moveDown, delay1, moveUp, delay2, NULL);
	RepeatForever* rep = RepeatForever::create(seq);
	runAction(rep);

	return true;
}

Role::CollisionResult RoleFlower::collsion(Role* mario, const Rect& rcMario)
{
	RoleMario* _mario = (RoleMario*)mario;

	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
	{
		rcRole.size.height = winSize.height;
		if (rcRole.intersectsRect(rcMario) && _mario->_flying == false)
		{
			// 有可能阻止花的运动
			// flying是false,又在花的头顶上，说明Mario此时停在了井盖上
			
			// Flower暂停动作
			_actionManager->pauseTarget(this);
			_bPaused = true;
			
		}
		else
		{
			if (_bPaused)
			{
				_bPaused = false;
				_actionManager->resumeTarget(this);
			}
		}

		return CollisionResult::Nothing;
	}

	

	return Role::CollisionResult::MarioDie;
}
