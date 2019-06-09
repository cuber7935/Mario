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
	if (_flying) // �������Ϸ�
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
	else // ���ڷ�
	{
		if (_dropping)  // ���ڽ���
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
		else  // �Ѿ����
		{
			RoleTortoise::updateStatus();
		}
	}
}


void RoleTortoiseFly::moveLeft(float dt)
{
	// ���ݷ����ڹ��״̬��ͬ
	if (_flying) // ��fly״̬ʱ
	{
		if (_right)
			return;

		this->setPositionX(this->getPositionX() - dt*_speed);
		if (this->getPositionX() < _xTurnRight)
		{
			// �����˱�����������updateStatus�ı��˱���״̬
			setRight(true);
		}
	}
	else if (_dropping)
	{
		// ��ƽ���ƶ�
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
		// ��ˮƽ�ƶ�
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
		// ��ֱ�����ƶ�
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

		/* rcMario.getMinY() > rc.getMidY(): ��ʾMario�Ľŵ׳����˷����ڹ����һ��
		   role->_speedUp <= 0: ��ʾMario�����½� */
		if (rcMario.getMinY() > rc.getMidY() && role->_speedUp <= 0)
		{
			/* �����ڹ걻���� */
			_flying = false;
			_dropping = true;
			updateStatus();
			return CollisionResult::Nothing;
		}
		else
		{
			/* mario��ײ�� */
			return CollisionResult::MarioDie;
		}
	}
	else if (_dropping)
	{
		if (!rc.intersectsRect(rcMario))
		{
			return CollisionResult::Nothing;
		}

		/* rcMario.getMinY() > rc.getMidY(): ��ʾMario�Ľŵ׳����˷����ڹ����һ��
		role->_speedUp <= 0: ��ʾMario�����½� */
		if (rcMario.getMinY() > rc.getMidY() && role->_speedUp <= 0)
		{
			/* �����½� */
			this->_speedDown += 50;
			return CollisionResult::Nothing;
		}
		else
		{
			/* mario��ײ�� */
			return CollisionResult::MarioDie;
		}
	}
	else
	{
		return RoleTortoise::collsion(role, rcMario);
	}

	return CollisionResult::Nothing;
}