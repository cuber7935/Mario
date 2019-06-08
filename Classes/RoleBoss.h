#ifndef _ROLE_BOSS_H_
#define _ROLE_BOSS_H_

#include "Role.h"

//boss��
class RoleBoss : public Role
{
public:
	virtual bool init(ValueMap& objProperty)override;

	// �ƶ������������£�
	virtual void moveLeft(float dt)override;
	virtual void moveRight(float dt)override;
	virtual void moveUp(float dt)override;
	virtual void moveDown(float dt)override;

	// ����״̬
	virtual void updateStatus()override;

	// ��ײ���
	virtual CollisionResult collsion(Role*, const Rect&);

	// boss��Ծ
	void jump();
	void jumpEngine();

	// boss�����ӵ�
	void fire();
	void fireEngine();

public:
	int _leftMost;
	int _rightMost;
};

#endif

