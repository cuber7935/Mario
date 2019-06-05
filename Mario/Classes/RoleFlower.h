
#ifndef __RoleFlower_H__
#define __RoleFlower_H__


#include "Role.h"

class RoleFlower : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

//	void moveUp(float dt);
//	void moveDown(float dt);

	virtual CollisionResult collsion(Role*, const Rect&);
	bool _bPaused=false;

};


#endif
