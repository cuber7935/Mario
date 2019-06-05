#ifndef __RoleBoss_H__
#define __RoleBoss_H__

#include "Role.h"
class RoleBoss : public Role
{
public:
	bool init(ValueMap& objProperty);

	void moveLeft(float dt);
	void moveRight(float dt);
	void moveUp(float dt);
	void moveDown(float dt);

	void updateStatus();

	int _leftMost;
	int _rightMost;

	void jump();
	void jumpEngine();

	void fire();
	void fireEngine();

	virtual CollisionResult collsion(Role*, const Rect&);
};

#endif

