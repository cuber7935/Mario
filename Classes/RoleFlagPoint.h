#ifndef _ROLE_FLAG_POINT_H_
#define _ROLE_FLAG_POINT_H_

#include "Role.h"

// 旗点
class RoleFlagPoint : public Role
{
public:
	virtual bool init(ValueMap& objProperty);
	CollisionResult collsion(Role*, const Rect&);

	virtual void moveDown(float dt)override;

private:
	bool _bDrop = false;	// 是否已经掉下来
};



#endif
