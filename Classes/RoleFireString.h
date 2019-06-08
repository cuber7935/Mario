#ifndef __RoleFireString_H__
#define __RoleFireString_H__

#include "Role.h"
class RoleFireString : public Role
{
public:
	bool init(ValueMap& objProperty);

	int _begAngle;
	int _time;

	CollisionResult collsion(Role*, const Rect&);
};

#endif
