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
		1. Mario��minY > �����midY
		2. Mario�����½�
	*/

	if (rcMario.getMinY() < rcRole.getMidY())
		return CollisionResult::MarioDie;

	if (mario->_speedDown <= _gravity)
		return CollisionResult::MarioDie;
	
	/* Ģ���� */
	this->setDead(false);

	/* Mario���� */
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

	// ����Mario����ǰ��
	this->setPositionY(this->getPositionY() - _speedDown*dt);

	if (isBlockDown())
	{
		// ���δ�����Ǹ�λ�ã����赲�����˻���
		this->setPositionY(this->getPositionY() + _speedDown*dt);
		
		//this->moveDownAjust();
		util->moveDownAjust(this);

		// 044. Mario��֡���赲����һ�ε�������������������
		// a.��һ�ε���ʱ���Ѿ����
		// b.��һ�ε��øú���moveDownʱ��û�б��赲

		_speedDown = _gravity;
		
		return;
	}

	

	// ����Mario��λ��
	//	this->setPositionY(this->getPositionY() - _speedDown*dt);
	// �����½��ٶ�
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
			// ��Mario����
			this->setSpriteFrame(FRA_MUSHROOM_DIE1);

			// ����֮����˳�����
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