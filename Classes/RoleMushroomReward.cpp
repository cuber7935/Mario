#include "RoleMushroomReward.h"

bool RoleMushroomReward::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	this->setSpriteFrame(FRA_MUSHROOM_REWARD1);

	this->setVisible(false);

	_speed = 80;

	return true;
}

void RoleMushroomReward::growUp()
{
	this->_bGrow = true;
}

void RoleMushroomReward::moveDown(float dt)
{
	if (!_bGrow)
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
void RoleMushroomReward::moveLeft(float dt)
{
	if (!_bGrow)
		return;
	if (_right) return;

	this->setPositionX(this->getPositionX() - dt*_speed);

	if (isBlockLeft())
	{
		this->setPositionX(this->getPositionX() + dt*_speed);
		_right = true;
	}
}

void RoleMushroomReward::moveRight(float dt)
{
	if (!_bGrow)
		return;
	if (!_right) return;

	this->setPositionX(this->getPositionX() + dt*_speed);

	if (isBlockRight())
	{
		this->setPositionX(this->getPositionX() - dt*_speed);
		_right = false;
	}
}

Role::CollisionResult RoleMushroomReward::collsion(Role* mario, const Rect& rcMario)
{
	if (!_bGrow)
		return CollisionResult::Nothing;

	Rect rcRole = this->getBoundingBox();
	if (!rcRole.intersectsRect(rcMario))
		return CollisionResult::Nothing;

	this->removeFromParent();
	return Role::CollisionResult::EAT_MUSHROOM_REWARD;
}
