#ifndef __RoleLadderLR_H__
#define __RoleLadderLR_H__
#include "Role.h"
class RoleLadderLR : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	int _LorR;
	int _ladderDis;

	int _LL; /* ����ߵ�λ�� */ 
	int _RR; /* ���ұߵ�λ�� */

	void moveLeft(float dt);
	void moveRight(float dt);

	virtual CollisionResult collsion(Role*, const Rect&);

	Role* _mario = nullptr;
};

#endif

