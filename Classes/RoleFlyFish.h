#ifndef __RoleFlyFish_H__
#define __RoleFlyFish_H__
#include "Role.h"
class RoleFlyFish : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	int _duration;
	int _offsetH;
	int _offsetV;

	Vec2 _ori;
	Vec2 _dst;

	void updateStatus();
	void callback()
	{
		_right = !_right;
		updateStatus();
	}

	virtual CollisionResult collsion(Role*, const Rect&);
};

#endif
