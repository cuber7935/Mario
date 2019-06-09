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

	/* ���Ӵ���Mario�˶� */
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

	/* ���Ӵ���Mario�˶� */
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

	/* ������Ӻ�Marioû����ײ */
	if (!rc.intersectsRect(rcMario))
	{
		/* ֮ǰMario�ǲ�������������� */
		if (_mario)
		{
			// �����ϵ
			mario->_ladder = nullptr;
			_mario = nullptr;
		}

		return Role::CollisionResult::Nothing;
	}

	/* ���Mario������ڸ������ϣ��Ͳ���Ҫ��ײ��� */
	//if (_mario) return Role::CollisionResult::Nothing;
	if (mario->_ladder) return Role::CollisionResult::Nothing;

	/* Mario�����������ˣ�����Mario���������������ӵ����������ĸ߶����ж�Mario����ײ���� */
	if (rcMario.getMidY() > rc.getMidY())
	{
		// ����½Ų���������
		// ΢��
		role->setPositionY(rc.getMaxY()-0.01);

		// ��¼��Mario
		_mario = role;

		// MarioҲҪ��¼����ĳ��������
		mario->_ladder = this;
	}
	else
	{
		// �����ͷ����������
		role->_speedDown = _speedUp; // ����
		role->_speedUp = 0;
	}

	return Role::CollisionResult::Nothing;
}