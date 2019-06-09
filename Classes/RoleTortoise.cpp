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
			1. Mario��minY > �����midY
			2. Mario�����½�
			*/

			if (rcMario.getMinY() < rcRole.getMidY())
				return CollisionResult::MarioDie;

			if (mario->_speedDown <= _gravity)
				return CollisionResult::MarioDie;


			//	this->setDead(false);
			//this->setScared(true);
			this->setCrazy(false);

			/* Mario���� */
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
				// ������
				_right = false;

			}
			else
			{
				// ������
				_right = true;
			}
			setCrazy(true);
		}
	}
	else // ���ڹ�����ͨ״̬ʱ����ײ����Ģ����һ��
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

		
	//	this->setDead(false);
		this->setScared(true);

		/* Mario���� */
		mario->_speedUp = 100;
		mario->_speedDown = _gravity;

		return CollisionResult::Nothing;
	}


	return CollisionResult::Nothing;
}