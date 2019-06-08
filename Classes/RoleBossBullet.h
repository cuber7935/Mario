#ifndef __RoleBossBullet_H__
#define __RoleBossBullet_H__
#include "Role.h"
class RoleBossBullet:public Role
{
public:
	bool init(ValueMap& objProperty);

	void updateStatus();

	void moveLeft(float dt);
	void moveRight(float dt);

	virtual CollisionResult collsion(Role*, const Rect&);
};

#endif

