#ifndef _ROLE_FIRE_STRING_H_
#define _ROLE_FIRE_STRING_H_

#include "Role.h"

// »ð´®
class RoleFireString : public Role
{
public:
	bool init(ValueMap& objProperty);

	CollisionResult collsion(Role*, const Rect&);

private:
	int _begAngle;
	int _time;
};

#endif
