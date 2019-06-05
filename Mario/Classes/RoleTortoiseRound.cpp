#include "RoleTortoiseRound.h"

bool RoleTortoiseRound::init(ValueMap& objProperty)
{
	// �ȵ��ø���ĳ�ʼ������
	RoleTortoise::init(objProperty);

	// ��ȡѲ�߷�Χ����ϸ�����ұ߽�
	_roundDis = objProperty["roundDis"].asInt();
	_xTurnLeft = this->getPositionX();
	_xTurnRight = _xTurnLeft - _roundDis;

	return true;
}

void RoleTortoiseRound::moveLeft(float dt)
{
	// ���ø����move������ʵ��ˮƽ�ƶ�
	RoleTortoise::moveLeft(dt);

	//�ƶ����֮���ж��Ƿ��˱߽磬����ǣ���ͷ
	if (this->_bCrazy == false)
	{
		if (this->getPositionX() < _xTurnRight)
		{
			setRight(true);
		}
	}
}
void RoleTortoiseRound::moveRight(float dt)
{
	RoleTortoise::moveRight(dt);
	if (this->_bCrazy == false)
	{
		if (this->getPositionX() > _xTurnLeft)
		{
			setRight(false);
		}
	}
}