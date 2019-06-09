#ifndef _ROLE_FLOWER_H_
#define _ROLE_FLOWER_H_

#include "Role.h"

// »¨¶ä
class RoleFlower : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	virtual CollisionResult collsion(Role*, const Rect&);

private:
	bool _bPaused = false;
};


#endif
