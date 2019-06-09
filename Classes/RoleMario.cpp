#include "RoleMario.h"

// Mario����Ĵ�ʼ��
bool RoleMario::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	// ����״̬����ʾMario�����ӣ�״̬ʲôʱ���ʼ�������ö��󱻴���ʱ������ʱ���Ѿ���ʼ��
	updateStatus();

	/* 034. ������ʱ�������mario�½����κ�ʱ��Ҫ���������Ƿ����½�
		Mario�½���������������������Ȼ���½�����·ʱ�������±ߵ���ȥ���Ⱥ��ԣ���ͷ�����ȿ�jz����
	*/
	/*042. ����*/


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

	/* Mario�ɴ��С */
	if (big == false)
	{
		setGodMode(5.0f);
	}
	else
	{
		// ������
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

//	if (�ڴ���������) return;
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
		return;
	}
}

// �����ƶ�
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
		// ֪ͨModelģ�飬sprite������
		/* ����שͷ */
		Sprite* sprite = getHitBlock();
		if (sprite)
		{
			// �����Զ�����Ϣ
			Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("hitblock", sprite);
		}

		/* ΢��λ�� */
		setPositionY(getPositionY() - yDt);

		int y = getPositionY() + this->getBoundingBox().size.height;
		y = y / 16 * 16+16;
		y -= this->getBoundingBox().size.height;
		setPositionY(y);

		_speedDown = _speedUp; // ����Ч��
		_speedUp = 0;
	}

	// ÿ֡�ƶ�֮�󣬽��ٶȼ�С�������ٶ�
	_speedUp -= _gravity;
}

/*
	Mario���½��������̣�
	1. ���ݶ�ʱ���ļ��ʱ��͵�ǰ���½��ٶȣ���Mario�ƶ���Ŀ��λ��
	2. �ж�Ŀ��λ���Ƿ�Ϸ�
	3. ������Ϸ���˵��mario���±��赲����Mario�ƻ���
	4. Ϊ�˲�����Mario���½�ƫ��Ϊ0���������Ҫ��_speedDown��ʼ��Ϊ��0
*/
void RoleMario::moveDown(float dt)
{
	//  _speedUp�������0��˵��Mario������Ծ״̬
	//      ����������赲��˵���ŵ��ˣ�Ҳ�����½�
	if (_speedUp > 0) return;
	if (_dead)
	{
		// ����Mario����ǰ��
		this->setPositionY(this->getPositionY() - _speedDown*dt);
		_speedDown += _gravity;
	
		return;
	}

	/* ���������Ӳ��������ƶ� */
	if (_ladder)
	{
		_speedDown = _gravity;
		setFlying(false);
		return;
	}

	// ����Mario����ǰ��
	this->setPositionY(this->getPositionY() - _speedDown*dt);

	if (isBlockDown())
	{
		// ���δ�����Ǹ�λ�ã����赲�����˻���
		this->setPositionY(this->getPositionY() + _speedDown*dt);

		//this->moveDownAjust();
		util->moveDownAjust(this);

		// Mario��֡���赲����һ�ε�������������������
		// a.��һ�ε���ʱ���Ѿ����
		// b.��һ�ε��øú���moveDownʱ��û�б��赲
		_speedDown = _gravity;
		setFlying(false);
		return;
	}
	
	// ����flying״̬Ϊtrue
	setFlying(true);

	// �����½��ٶ�
	_speedDown += _gravity;
}

/*
	1.��ֹʱ����øú���
	2.Mario�����ƶ�ʱ���øú���
	3.Mario�����ƶ�ʱ���øú���
	4.Mario�����Ϸ���ʱ���øú���
*/
void RoleMario::moveRight()
{
	/* ����Mario�����ߵ����� */
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
#if 0     //�޵�
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

//  ʵ��Mario����Ծ
//  ��Ծ��Ϊ��ʵ������Ч�������ö�ʱ��������mario����Ծ�˶�
void RoleMario::jump()
{
	if (_autoCtrl1 || _autoCtrl2) 
		return;

	_ladder = nullptr;

	// ���Mario�ڷ���״̬�£���������
	if (_flying)
		return;

	// �ı�Mario�����ԣ����Ҹı�Mario�ı�����ʽ
	setFlying(true);

	// ��Ծ,���������ƶ���Ϊ��ʵ������Ч������Ծʹ�������ٶ�ʵ��
	// �������˶��ٶ����ó�300
	_speedUp = 300;
}

void RoleMario::updateStatus()
{
	stopAnimation();
	
	if (_autoCtrl1)
	{
		if (_big)
			this->setDisplayFrameWithAnimationName(ANI_MARIO_WALK_RIGHT_BIG, 0);
		else
			this->setDisplayFrameWithAnimationName(ANI_MARIO_WALK_RIGHT_BIG, 0);
		return;
	}

	//  ������
	if (_dead)
	{
		runAnimation(ANI_MARIO_DIE_SML);
		this->_speedUp = 250;
		this->_speedDown = _gravity;
		return;
	}

	// ����״̬����Mario����״
	if (_big)
	{
		if (_flying)
		{
			if (_right)
			{
				// С���ӵ�Mario�������ң��ڿ���
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
					this->setDisplayFrameWithAnimationName(ANI_MARIO_WALK_RIGHT_BIG, 0);
				}
				else
				{
					this->setDisplayFrameWithAnimationName(ANI_MARIO_WALK_LEFT_BIG, 0);
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
				// С���ӵ�Mario�������ң��ڿ���
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
					this->setDisplayFrameWithAnimationName(ANI_MARIO_WALK_RIGHT_SML, 0);
				}
				else
				{
					this->setDisplayFrameWithAnimationName(ANI_MARIO_WALK_LEFT_SML, 0);
				}
			}
		}
	}
}

void RoleMario::setGodMode(float duration)
{
	// �ϵ�ģʽһ��ʹ�ð�͸������
	this->setOpacity(128);

	// �����ϵ�ģʽ
	_godMode = true;

	//DelayTime* delay = DelayTime::create(duration);
	// ��durationʱ���ȥ֮��������Ϊ���޵�ģʽ
	Blink* blink = Blink::create(duration, duration * 2);
	CallFunc* callf = CallFunc::create(CC_CALLBACK_0(RoleMario::unsetGodMode, this));
	this->runAction(Sequence::create(blink, callf, NULL));
}

void RoleMario::unsetGodMode()
{
	this->setOpacity(255);
	_godMode = false;
}
