#ifndef _ROLE_LADDER_H_
#define _ROLE_LADDER_H_
#include "Role.h"


// ����
class RoleLadderLR : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	void moveLeft(float dt);
	void moveRight(float dt);

	virtual CollisionResult collsion(Role*, const Rect&);

private:
	Role* _mario = nullptr;
	int _LorR;				// ��ʼ���ĸ������ƶ�
	int _ladderDis;			// �ƶ���Χ

	int _LL;				// ����ߵ�λ�� 
	int _RR;				// ���ұߵ�λ�� 
};

#endif

