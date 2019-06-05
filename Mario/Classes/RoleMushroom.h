
#ifndef __RoleMushroom_H__
#define __RoleMushroom_H__


#include "Role.h"

class RoleMushroom : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	void updateStatus();

	void moveLeft(float dt);
	void moveRight(float dt);
	void moveDown(float dt);

	CollisionResult collsion(Role* mario, const Rect& rcMario);
};


#endif
