#ifndef _ROLE_BOSS_BULLET_H_
#define _ROLE_BOSS_BULLET_H_

#include "Role.h"

// BOSS ×Óµ¯
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

