#include "RoleMario.h"

// 032. Mario对象的创始花
bool RoleMario::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	// this->runAnimation(ANI_MARIO_WALK_RIGHT_SML);
	// 033. 根据状态来显示Mario的样子，状态什么时候初始化？？该对象被创建时，构造时，已经初始化
	updateStatus();

	/* 034. 启动定时器，检测mario下降，任何时候都要检测马里奥是否能下降
		Mario下降的因素有两个，跳起来然后下降，走路时，在悬崖边掉下去，先忽略，回头看，先看jz函数
	*/
	/*042. 下落*/


	_ladder = nullptr;

	return true;
}

void RoleMario::autoCtrl1()
{
	_speedUp = 0;
	_speedDown = 10;

	_autoCtrl1 = true;
	updateStatus();
}

void RoleMario::autoCtrl2()
{
	_speedUp = 0;
	_speedDown = 10;
	_autoCtrl2 = true;
	_autoCtrl1 = false;
	updateStatus();
	runAction(MoveBy::create(winSize.width / _speed, Vec2(winSize.width, 0)));
}
void RoleMario::setFlying(bool fly)
{
	if (_flying == fly) return;
	_flying = fly;
	updateStatus();
}


void RoleMario::setBig(bool big)
{
	if (_big == big) return;
	_big = big;
	updateStatus();

	/* Mario由大变小 */
	if (big == false)
	{
		setGodMode(5.0f);
	}
	else
	{
		// 。。。
	}
}

void RoleMario::setRight(bool right)
{
	if (_right == right) return;
	_right = right;
	updateStatus();
}



void RoleMario::moveLeft(float dt)
{
	if (_autoCtrl1 || _autoCtrl2) return;
	if (_running == false) return;
	if (_right) return;
	if (_dead) return;

//	if (在窗口左侧边沿) return;
	Vec2 posInMap = this->getPosition();
	Vec2 posInWorld = this->_map->convertToWorldSpace(posInMap);
	if (posInWorld.x <= 0)
		return;


	this->setPositionX(this->getPositionX() - dt*_speed);

	if (isBlockLeft())
	{
		this->setPositionX(this->getPositionX() + dt*_speed);
	}

}

void RoleMario::moveRight(float dt)
{
	if (_autoCtrl1 || _autoCtrl2) return;
	if (_running == false) return;
	if (_right == false) return;
	if (_dead) return;

	this->setPositionX(this->getPositionX() + dt*_speed);
	if (isBlockRight())
	{
		this->setPositionX(this->getPositionX() - dt*_speed);
#if 0
	//	int x = this->getPositionX();
	//	setPositionX(x / 16 * 16);

		Rect rc = this->getBoundingBox();
		int maxX = rc.getMaxX();
		maxX = maxX / 16 * 16;

		int minX = maxX - rc.size.width;
		setPositionX(minX);
#endif
		return;
	}

	
}

// 040. 向上移动实现代码
void RoleMario::moveUp(float dt)
{
	if (_speedUp <= 0)
		return;

	if (_dead)
	{
		float yDt = _speedUp * dt;
		setPositionY(getPositionY() + yDt);
		_speedUp -= _gravity; 
		return;
	}

	float yDt = _speedUp * dt;
	setPositionY(getPositionY() + yDt);

	if (isBlockUp())
	{
#if 0
		/* 顶动砖头 */
		Sprite* sprite = getHitBlock();
		if (sprite)
			sprite->runAction(JumpBy::create(0.2f, Vec2(0, 0), 30, 1));
	
#endif
		// 通知Model模块，sprite被顶了
		/* 顶动砖头 */
		Sprite* sprite = getHitBlock();
		if (sprite)
		{
			// 发送自定义消息
		//	sprite->retain();
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("hitblock", sprite);
		}

		/* 微调位置 */
		setPositionY(getPositionY() - yDt);

		int y = getPositionY() + this->getBoundingBox().size.height;
		y = y / 16 * 16+16;
		y -= this->getBoundingBox().size.height;
		setPositionY(y);

		_speedDown = _speedUp; // 反弹效果
		_speedUp = 0;
	}

	// 041. 每帧移动之后，将速度减小重力加速度
	_speedUp -= _gravity;
}

/*
	015001: Mario的下降控制流程：
	1. 根据定时器的间隔时间和当前的下降速度，将Mario移动到目标位置
	2. 判断目标位置是否合法
	3. 如果不合法，说明mario脚下被阻挡，将Mario移回来
	4. 为了不出现Mario的下降偏移为0的情况，需要将_speedDown初始化为非0
*/
void RoleMario::moveDown(float dt)
{
	// 043. _speedUp如果大于0，说明Mario还在跳跃状态
	//      如果脚下有阻挡，说明着地了，也不能下降
	if (_speedUp > 0) return;
	if (_dead)
	{
		// 设置Mario的提前量
		this->setPositionY(this->getPositionY() - _speedDown*dt);
		_speedDown += _gravity;
	
		return;
	}

	/* 控制有梯子不能向下移动 */
	if (_ladder)
	{
		_speedDown = _gravity;
		setFlying(false);
		return;
	}

	// 设置Mario的提前量
	this->setPositionY(this->getPositionY() - _speedDown*dt);

	if (isBlockDown())
	{
		// 如果未来的那个位置，有阻挡，再退回来
		this->setPositionY(this->getPositionY() + _speedDown*dt);

		this->moveDownAjust();

		// 044. Mario这帧有阻挡，上一次调用这个函数有两种情况
		// a.上一次调用时就已经落地
		// b.上一次调用该函数moveDown时，没有被阻挡
		_speedDown = _gravity;
		setFlying(false);
		return;
	}
	
	
	
	// 045. 设置flying状态为true
	setFlying(true);

	// 设置Mario的位置
//	this->setPositionY(this->getPositionY() - _speedDown*dt);
	// 增加下降速度
	_speedDown += _gravity;
}

/*
	1.静止时候调用该函数
	2.Mario向左移动时调用该函数
	3.Mario向右移动时调用该函数
	4.Mario在天上飞行时调用该函数
*/
void RoleMario::moveRight()
{
	/* 设置Mario向右走的属性 */
	setRunning(true);
	setRight(true);
}

void RoleMario::moveLeft()
{
	setRunning(true);
	setRight(false);
}
void RoleMario::stop()
{
	setRunning(false);
}

void RoleMario::Dead()
{
#if 0
	return;
#endif
	if (_godMode)
		return;

	if (_big)
	{
		setBig(false);
		return;
	}

	setDead(true);
}

// 035. 实现Mario的跳跃
//  跳跃：为了实现重力效果，利用定时器来控制mario的跳跃运动
void RoleMario::jump()
{
	if (_autoCtrl1 || _autoCtrl2) 
		return;

	_ladder = nullptr;

	// 037. 如果Mario在飞行状态下，不能再跳
	if (_flying)
		return;

	// 036. 改变Mario的属性，并且改变Mario的表现形式
	setFlying(true);

	// 038. 跳跃,就是向上移动，为了实现重力效果，跳跃使用向上速度实现
	// 将向上运动速度设置成300
	_speedUp = 300;
	

#if 0
	// 实现mario的跳跃
	if (_flying)
		return;
		
	stopAllActions();

	setSpriteFrame(FRA_MARIO_JUMP_RIGHT_SML);

	_flying = true;
	_speedUp = 300;
	schedule(schedule_selector(RoleMario::moveUp));
#endif
}

void RoleMario::updateStatus()
{
	stopAnimation();
	
	if (_autoCtrl1)
	{
		if (_big)
			setSpriteFrameByAnimation(ANI_MARIO_WALK_RIGHT_BIG);
		else
			setSpriteFrameByAnimation(ANI_MARIO_WALK_RIGHT_SML);
		return;
	}

	// 1. 翻跟斗
	if (_dead)
	{
		runAnimation(ANI_MARIO_DIE_SML);
		this->_speedUp = 250;
		this->_speedDown = _gravity;
		return;
	}

	// 根据状态决定Mario的形状
	if (_big)
	{
		if (_flying)
		{
			if (_right)
			{
				// 小个子的Mario，脸朝右，在空中
				setSpriteFrame(FRA_MARIO_JUMP_RIGHT_BIG);
			}
			else
			{
				setSpriteFrame(FRA_MARIO_JUMP_LEFT_BIG);
			}
		}
		else
		{
			if (_running)
			{
				if (_right)
				{
					runAnimation(ANI_MARIO_WALK_RIGHT_BIG);
				}
				else
				{
					runAnimation(ANI_MARIO_WALK_LEFT_BIG);
				}
			}
			else
			{
				if (_right)
				{
					setSpriteFrameByAnimation(ANI_MARIO_WALK_RIGHT_BIG);
				}
				else
				{
					setSpriteFrameByAnimation(ANI_MARIO_WALK_LEFT_BIG);
				}
			}
		}
	}
	else
	{
		if (_flying)
		{
			if (_right)
			{
				// 小个子的Mario，脸朝右，在空中
				setSpriteFrame(FRA_MARIO_JUMP_RIGHT_SML);
			}
			else
			{
				setSpriteFrame(FRA_MARIO_JUMP_LEFT_SML);
			}
		}
		else
		{
			if (_running)
			{
				if (_right)
				{
					runAnimation(ANI_MARIO_WALK_RIGHT_SML);
				}
				else
				{
					runAnimation(ANI_MARIO_WALK_LEFT_SML);
				}
			}
			else
			{
				if (_right)
				{
					setSpriteFrameByAnimation(ANI_MARIO_WALK_RIGHT_SML);
				}
				else
				{
					setSpriteFrameByAnimation(ANI_MARIO_WALK_LEFT_SML);
				}
			}
		}
	}
}

