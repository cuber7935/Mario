
#ifndef __RoleFlagPoint_H__
#define __RoleFlagPoint_H__


#include "Role.h"

class RoleFlagPoint : public Role
{
public:
	virtual bool init(ValueMap& objProperty);
	CollisionResult collsion(Role*, const Rect&);

	bool _bDrop = false; // �Ƿ��Ѿ�������

	void moveDown(float dt);
};



#endif
