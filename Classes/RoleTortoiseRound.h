#ifndef __RoleTortoiseRound_H__
#define __RoleTortoiseRound_H__

#include "RoleTortoise.h"

class RoleTortoiseRound : public RoleTortoise
{
public:
	virtual bool init(ValueMap& objProperty);

	/* ����Ѳ�߷�Χ����ͼ����������趨����ʼ��Ѳ���ڹ�ʱ��ȡ */
	int _roundDis;
	
	/* Ѳ���ڹ������ƶ����ƣ������ƶ������ɸ��ฺ�� */
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);

	/* ���廯��Ѳ�߷�Χ */
	int _xTurnRight;  /* �ڹ��λ��С�ڸ�ֵ������ĳ����� */
	int _xTurnLeft;  /* �ڹ��λ�ô��ڸ�ֵ������ĳ����� */
};

#endif
