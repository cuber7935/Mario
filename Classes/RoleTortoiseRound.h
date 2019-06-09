#ifndef _ROLE_TORTOISE_ROUND_H
#define _ROLE_TORTOISE_ROUND_H

#include "RoleTortoise.h"

// Ѳ���ڹ�
class RoleTortoiseRound : public RoleTortoise
{
public:
	virtual bool init(ValueMap& objProperty);

	/* Ѳ���ڹ������ƶ����ƣ������ƶ������ɸ��ฺ�� */
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);

protected:
	/* ����Ѳ�߷�Χ����ͼ����������趨����ʼ��Ѳ���ڹ�ʱ��ȡ */
	int _roundDis;

	/* ���廯��Ѳ�߷�Χ */
	int _xTurnRight;  /* �ڹ��λ��С�ڸ�ֵ������ĳ����� */
	int _xTurnLeft;  /* �ڹ��λ�ô��ڸ�ֵ������ĳ����� */
};

#endif
