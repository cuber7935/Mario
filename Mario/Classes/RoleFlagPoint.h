
#ifndef __RoleFlagPoint_H__
#define __RoleFlagPoint_H__


#include "Role.h"

class RoleFlagPoint : public Role
{
public:
	virtual bool init(ValueMap& objProperty);
	CollisionResult collsion(Role*, const Rect&);

	bool _bDrop = false; // 是否已经掉下来

	void moveDown(float dt);
};



#endif
