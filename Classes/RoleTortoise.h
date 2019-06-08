
#ifndef __RoleTortoise_H__
#define __RoleTortoise_H__


#include "Role.h"

class RoleTortoise : public Role
{
public:
	virtual bool init(ValueMap& objProperty);

	bool _bScared = false;
	bool _bCrazy = false;

	void setScared(bool scared)
	{
		if (_bScared != scared)
		{
			_bScared = scared;
			updateStatus();
		}
	}
	void setCrazy(bool crazy)
	{
		if (_bCrazy != crazy)
		{
			_bCrazy = crazy;
			updateStatus();
		}
	}

	void updateStatus();

	virtual void moveLeft(float dt);
	virtual void moveRight(float dt);
	virtual void moveDown(float dt);

	CollisionResult collsion(Role*, const Rect&);
};


#endif
