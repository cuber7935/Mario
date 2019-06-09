#ifndef _ROLE_FINAL_POINT_H_
#define _ROLE_FINAL_POINT_H_

#include "Role.h"


class RoleFinalPoint : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	CollisionResult collsion(Role*, const Rect&);
};


#endif
