#ifndef _ROLE_TORTOISE_FLY_H_
#define _ROLE_TORTOISE_FLY_H_

#include "RoleTortoiseRound.h"

// �����
class RoleTortoiseFly : public RoleTortoiseRound
{
public:
	virtual bool init(ValueMap& objProperty);

	// ����״̬
	void updateStatus();

	// �ƶ�����
	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	CollisionResult collsion(Role*, const Rect&);

protected:
	// �Ƿ��ڷ��к����ڽ��������
	bool _flying	= true;		// Ĭ�Ϸ���
	bool _dropping	= false;	// Ĭ��û�½�
};

#endif

