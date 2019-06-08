
#ifndef __RoleFinalPoint_H__
#define __RoleFinalPoint_H__


#include "Role.h"

class RoleFinalPoint : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	CollisionResult collsion(Role*, const Rect&);
};


#endif
