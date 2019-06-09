#include "RoleFlagPoint.h"
#include "RoleMario.h"
bool RoleFlagPoint::init(ValueMap& objProperty)
{
	Role::init(objProperty);

	this->setSpriteFrame(FRA_FLAG);
	this->setPositionX(this->getPositionX() - this->getBoundingBox().size.width/2);

	this->setLocalZOrder((int)ZOrder::Flag);

	return true;
}

Role::CollisionResult RoleFlagPoint::collsion(Role* role, const Rect& rcMario)
{
	RoleMario* mario = (RoleMario*)role;
	Rect rcRole = this->getBoundingBox();
	if (_bDrop == false)
	{

		if (rcMario.getMaxX() >= rcRole.getMaxX() - 8)
		{
			this->_bDrop = true;

			// MarioҪ�����Զ�����״̬
			mario->autoCtrl1();

			// ����
			_eventDispatcher->dispatchCustomEvent("breakbridge", NULL);
		}
	}
	else
	{
		Rect rcRole = this->getBoundingBox();
		if (rcRole.intersectsRect(rcMario))
		{
			mario->autoCtrl2();
			return Role::CollisionResult::RoleDie;
		}
	}

	return Role::CollisionResult::Nothing;
}

void RoleFlagPoint::moveDown(float dt)
{
	if (!_bDrop)
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